/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* netlink.c */
/********************************************************************************/

/********************************************************************************/
/* INCLUDES */
/********************************************************************************/
#include "outputQueueModule.x"
#include <net/sock.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <asm/types.h>
#include <linux/netlink.h>

/********************************************************************************/
/* DEFINES */
/********************************************************************************/

/********************************************************************************/
/* FUNCTION PROTOTYPES */
/********************************************************************************/
static void startNlWakeUpHrTimer(void);
static void stopNlWakeUpHrTimer(void);
static enum hrtimer_restart nlWakeUpHrTimerCallback(struct hrtimer *timer);
int headNlQueue(struct sk_buff *skb,T_MESSAGE_TYPE msgType);
int tailNlQueue(struct sk_buff *skb,T_MESSAGE_TYPE msgType);
int initNlThread(void);
int killNlThread(void);
static void nlThreadRoutine(T_KTHREAD* wThread);
static int netlinkCreate(void);
static int netlinkRelease(void);
static void netlinkRecvMsg(struct sk_buff* skb);
int netlinkSendMsg(unsigned short moduleId, void* data, int dataLen);
void netlinkLogMessage(char* str);
void netlinkSendCommand(unsigned short command);
static void netlinkSend(struct sk_buff* skb, int pid);
static int nlThreadHandler_MSG_IPC(struct sk_buff *skb);
static int nlThreadHandler_MSG_NETLINK(struct sk_buff *skb);
static int nlModuleHandler(T_MSG_NL_SHORT *msg, int msgLen, int msgSeq, int pid);
/********************************************************************************/
/* GLOBALS */
/********************************************************************************/
/*thread structures*/
static T_KTHREAD nlThread;
static int nlThread_running = 0;
/*nlQueue*/
static struct sk_buff_head	nlQueue;
/*nl thread wait queue*/
static wait_queue_head_t	waitNlQueue;
/*netlink*/
static struct sock *nl_sk=NULL;
int uspPid;/*user space process pid on the other side of the netlink socket*/

unsigned char rcvdNlMessage[T_MSG_NL_LONG_SIZE];
unsigned char nlMessageToSend[T_MSG_NL_LONG_SIZE];
T_MSG_NL_SHORT nlMsgShort;
T_MSG_NL_LONG nlMsgLong;
/********************************************************************************/
/* EXTERNS */
/********************************************************************************/

/********************************************************************************/
/* FUNCTIONS */
/********************************************************************************/

/********************************/
/* startNlWakeUpHrTimer */
/********************************/
static void startNlWakeUpHrTimer(void)
{
    LOG_INFO((logInfoBuf,"\n"))
    nlThread.wakeUpAbsKtime = ktime_set(0,WAKEUPTIMER_NSEC);
    hrtimer_init(&nlThread.wakeUpHrTimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    nlThread.wakeUpHrTimer.function = &nlWakeUpHrTimerCallback;
    LOG_INFO((logInfoBuf,"starting wakeUpHrTimer.\n"))
    hrtimer_start(&nlThread.wakeUpHrTimer, nlThread.wakeUpAbsKtime, HRTIMER_MODE_REL);
}/*startNlWakeUpHrTimer*/

/********************************/
/* stopNlWakeUpHrTimer */
/********************************/
static void stopNlWakeUpHrTimer(void)
{
    LOG_INFO((logInfoBuf,"\n"))
    hrtimer_cancel(&nlThread.wakeUpHrTimer);
}/*stopNlWakeUpHrTimer*/

/********************************/
/* nlWakeUpHrTimerCallback */
/********************************/
static enum hrtimer_restart nlWakeUpHrTimerCallback(struct hrtimer *timer)
{
    hrtimer_forward_now(timer,nlThread.wakeUpAbsKtime);
    wake_up_interruptible(&waitNlQueue);
    return HRTIMER_RESTART;
}/*nlWakeUpHrTimerCallback*/

/********************************/
/* headNlQueue */
/********************************/
int headNlQueue(struct sk_buff *skb,T_MESSAGE_TYPE msgType)
{
    if(nlThread_running == 0)
    {
        outputQueueModuleCb.stats.nl.notQueued++;
        kfree_skb(skb);
        return -1;
    }
    setSkbMsgType(skb,msgType);
    skb_queue_head(&nlQueue, skb);
    outputQueueModuleCb.stats.nl.queued++;
    wake_up_interruptible(&waitNlQueue);
    return 1;
}/*headNlQueue*/

/********************************/
/* tailNlQueue */
/********************************/
int tailNlQueue(struct sk_buff *skb,T_MESSAGE_TYPE msgType)
{
    if(nlThread_running == 0)
    {
        outputQueueModuleCb.stats.nl.notQueued++;
        kfree_skb(skb);
        return -1;
    }
    setSkbMsgType(skb,msgType);
    skb_queue_tail(&nlQueue, skb);
    outputQueueModuleCb.stats.nl.queued++;
    wake_up_interruptible(&waitNlQueue);
    return 1;
}/*tailNlQueue*/

/********************************/
/* initNlThread */
/********************************/
int initNlThread(void)
{
    /*initialize and start nlThreadRoutine*/
    if(nlThread_running == 1)
    {
        LOG_INFO((logInfoBuf,"already running.\n"))
        return -1;
    }
    LOG_INFO((logInfoBuf,"initializing.\n"))

    /*set user process id to 0*/
    uspPid = 0;

    memset(&nlThread, 0, sizeof(T_KTHREAD));
    nlThread.thread = kthread_run((void *)nlThreadRoutine, &nlThread, NL_THREAD_NAME);
    if (IS_ERR(nlThread.thread))
    {
        LOG_INFO((logInfoBuf,"unable to start!\n"))
        return 0;
    }
    while (nlThread_running != 1)
    {
        msleep(10);
    }
    return 1;
}/*initNlThread*/

/********************************/
/* killNlThread */
/********************************/
int killNlThread(void)
{
    int err;
    /*stop nlThreadRoutine*/
    if(nlThread_running != 1)
    {
        LOG_INFO((logInfoBuf,"already not running!\n"))
        return -1;
    }
    LOG_INFO((logInfoBuf,"stopping.\n"))
    lock_kernel();
    err = kill_pid(nlThread.thread->pids[PIDTYPE_PID].pid, SIGKILL, 1);
    unlock_kernel();
    /*oldurmek istedigimiz thread waitQueue'da duruyor olabilir. Uyandiralim ki SIG_KILL'i islesin*/
    wake_up_interruptible(&waitNlQueue);
    if (err < 0)
    {
        LOG_INFO((logInfoBuf,"unknown error %d while terminating.\n",err))
        return 0;
    }
    else
    {
        while (nlThread_running == 1)
        {
            msleep(10);
            THREAD_YIELD
        }
        LOG_INFO((logInfoBuf,"successfully killed.\n"))
    }
    return 1;
}/*killNlThread*/

/********************************/
/* nlThreadRoutine */
/********************************/
static void nlThreadRoutine(T_KTHREAD* wThread)
{
    struct sk_buff *skb;
    /*struct sched_param param;*/
    LOG_INFO((logInfoBuf,"initializing.\n"))
    /* kernel thread initialization */
    lock_kernel();
    current->flags |= PF_NOFREEZE;
    /* daemonize (take care with signals, after daemonize() they are disabled) */
    daemonize(MODULE_NAME);
    allow_signal(SIGKILL);

    /*param.sched_priority = 90;
    sched_setscheduler(0,SCHED_FIFO,&param);*/
    unlock_kernel();

    /*initialize nlQueue...*/
    LOG_INFO((logInfoBuf,"initializing nlQueue.\n"))
    skb_queue_head_init(&nlQueue);
    /*initialize waitNlQueue*/
    LOG_INFO((logInfoBuf,"initializing waitNlQueue.\n"))
    init_waitqueue_head(&waitNlQueue);

    /*initialize netlink*/
    netlinkCreate();

    /*initialize and start wake up hr timer...*/
    startNlWakeUpHrTimer();

    LOG_INFO((logInfoBuf,"initialized.\n"))
    nlThread_running = 1;

    while(1)
    {
        if (signal_pending(current))
        {
            break;
        }

        /*sleep until someone wakes up!*/
        /*someone is nlNetlinkPackHandler*/
        interruptible_sleep_on(&waitNlQueue);

        while( (skb = skb_dequeue(&nlQueue)) != NULL)
        {
            outputQueueModuleCb.stats.nl.dequeued++;
            switch(getSkbMsgType(skb))
            {
                case MSG_IPC:
                    nlThreadHandler_MSG_IPC(skb);
                break;/*MSG_IPC*/
                case MSG_NETLINK:
                    nlThreadHandler_MSG_NETLINK(skb);
                break;/*MSG_NETLINK*/
                default:
                    kfree_skb(skb);
                break;
            }/*switch(getMsgTypeSkb(skb))*/

            outputQueueModuleCb.stats.nl.processed++;
            THREAD_YIELD
        }
    }

    /*stop wakeup hr timer...*/
    stopNlWakeUpHrTimer();

    /*release netlink...*/
    netlinkRelease();

    /*clean the skb queues*/
    LOG_INFO((logInfoBuf,"skb_queue_purge ->nlQueue(%d).\n",skb_queue_len(&nlQueue)))
    skb_queue_purge(&nlQueue);

    LOG_INFO((logInfoBuf,"exiting.\n"))

    nlThread_running = 0;

}/*nlThreadRoutine*/

/********************************/
/* nlThreadHandler_MSG_IPC */
/********************************/
static int nlThreadHandler_MSG_IPC(struct sk_buff *skb)
{
    /*static T_IPC_MSGHEADER ipcHdr;*/
    /*static unsigned char ipcMsg[MAX_IPCMSG_PAYLEN];*/
    outputQueueModuleCb.stats.nl.ipcProcessed++;
    kfree_skb(skb);
    return 1;
}/*nlThreadHandler_MSG_IPC*/

/********************************/
/* nlThreadHandler_MSG_NETLINK */
/********************************/
static int nlThreadHandler_MSG_NETLINK(struct sk_buff *skb)
{
    struct nlmsghdr *nlh;
    int pid;
    unsigned short msgType;
    int msgLen;
    int msgSeq;

    nlh = (struct nlmsghdr*)(skb->data);
    pid = nlh->nlmsg_pid;
    msgType = nlh->nlmsg_type;
    msgLen = nlh->nlmsg_len;
    msgSeq = nlh->nlmsg_seq;
    /*LOG_INFO((logInfoBuf,"pid:%d msgType:%d msgLen:%d msgSeq:%d.\n", pid, msgType, msgLen,msgSeq))*/

    /*copy received message to a temporary place*/
    memset(rcvdNlMessage,0,T_MSG_NL_LONG_SIZE);
    memcpy(rcvdNlMessage,NLMSG_DATA(nlh), (msgLen>T_MSG_NL_LONG_SIZE ? T_MSG_NL_LONG_SIZE:msgLen));

    switch(msgType)
    {
        case NL_NLMODULE:
            /*LOG_INFO((logInfoBuf,"%s: NL_NLMODULE\n",__FUNCTION__))*/
            nlModuleHandler((T_MSG_NL_SHORT*)rcvdNlMessage,msgLen,msgSeq,pid);
        break;
        default:
            LOG_INFO((logInfoBuf,"%s: Unknown module(0x%04x)!\n",__FUNCTION__,msgType))
        break;
    }
    /*free the skb!*/
    kfree_skb(skb);
    return 1;
}/*nlThreadHandler_MSG_NETLINK*/

/********************************/
/* netlinkCreate */
/********************************/
static int netlinkCreate(void)
{
    LOG_INFO((logInfoBuf,"creating socket.\n"))
    nl_sk = netlink_kernel_create(&init_net,NETLINK_USER,0,netlinkRecvMsg,NULL,THIS_MODULE);
    if(nl_sk == NULL)
    {
        LOG_INFO((logInfoBuf,"error creating socket.\n"))
        return -1;
    }
    return 1;
}/*netlinkCreate*/

/********************************/
/* netlinkRelease */
/********************************/
static int netlinkRelease(void)
{
    LOG_INFO((logInfoBuf,"releasing socket.\n"))
    /*release_sock(nl_sk);*/
    netlink_kernel_release(nl_sk);
    nl_sk = NULL;
    /*bundan sonra loglar netlink ile basilmasin diye uspPid = 0 yapildi...*/
    uspPid = 0;
    return 1;
}/*netlinkRelease*/

/********************************/
/* netlinkRecvMsg */
/********************************/
static void netlinkRecvMsg(struct sk_buff* skb)
{
    struct sk_buff* skb_t;
    outputQueueModuleCb.stats.nl.nlRcvd++;
    skb_t = skb_get(skb);/*increment usage count of skb by 1 and return a pointer to it...*/
    /*write skb to nlQueue and wake nlThread up*/
    tailNlQueue(skb_t,MSG_NETLINK);
}/*netlinkRecvMsg*/

/********************************/
/* netlinkSendMsg */
/********************************/
int netlinkSendMsg(unsigned short moduleId, void* data, int dataLen)
{
    struct nlmsghdr *nlh_out;
    struct sk_buff *skb_out;

    skb_out = nlmsg_new(dataLen,GFP_ATOMIC);
    if(!skb_out)
    {
        LOG_INFO((logInfoBuf,"skb_out alloc failed.\n"))
        return -1;
    }
    nlh_out = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, dataLen, 0);
    nlh_out->nlmsg_type = moduleId;
    memcpy(NLMSG_DATA(nlh_out),data,dataLen);
    nlh_out->nlmsg_seq = outputQueueModuleCb.stats.nl.nlSent;
    NETLINK_CB(skb_out).dst_group = 0; /*NETLINK_CB(skb)		(*(struct netlink_skb_parms*)&((skb)->cb))*/
    netlinkSend(skb_out, uspPid);
	return 1;
}/*netlinkSendMsg*/

/********************************/
/* netlinkLogMessage */
/********************************/
void netlinkLogMessage(char* str)
{
    int len;
    len = strlen(str);
    if( len >= LOG_PAYLOAD_LEN )
    {
        len = LOG_PAYLOAD_LEN;
    }
    if(uspPid!=0)
    {
        nlMsgLong.msgType = NL_MSGTYPE_LOG;
        memcpy(nlMsgLong.payload,str,len);
        netlinkSendMsg(NL_NLMODULE, &nlMsgLong, len+2);
    }
}/*netlinkLogMessage*/


/********************************/
/* netlinkSendCommand */
/********************************/
void netlinkSendCommand(unsigned short command)
{
    nlMsgShort.msgType = command;
    netlinkSendMsg(NL_NLMODULE,&nlMsgShort,T_MSG_NL_SHORT_SIZE);
}/*netlinkSendCommand*/

/********************************/
/* netlinkSend */
/********************************/
static void netlinkSend(struct sk_buff* skb, int pid)
    {
    outputQueueModuleCb.stats.nl.nlSent++;
    /*LOG_INFO((logInfoBuf,"(#%d)(pid:%d)\n",outputQueueModuleCb.stats.nl.nlSent, pid))*/
    if(nl_sk != NULL)
    {
        nlmsg_unicast(nl_sk, skb, pid);
    }
    else
    {
        kfree_skb(skb);
    }
}/*netlinkSend*/

/********************************/
/* nlModuleHandler */
/********************************/
static int nlModuleHandler(T_MSG_NL_SHORT *msg, int msgLen, int msgSeq, int pid)
{
    if( (msg->msgType != NL_MSGTYPE_ECHO_REQ) && (uspPid == 0) )
    {
        LOG_INFO((logInfoBuf,"islenmedi.\n"))
        return 0;
    }
    switch(msg->msgType)
    {
        case NL_MSGTYPE_ECHO_REQ:
            LOG_INFO((logInfoBuf,"msgType: NL_MSGTYPE_ECHO_REQ.\n"))
            uspPid = pid;
            nlMsgShort.msgType = NL_MSGTYPE_ECHO_REP;
            netlinkSendMsg(NL_NLMODULE,&nlMsgShort,T_MSG_NL_SHORT_SIZE);
        break;
        case NL_MSGTYPE_ECHO_REP:
            LOG_INFO((logInfoBuf,"msgType: NL_MSGTYPE_ECHO_REP.\n"))
        break;
        case NL_MSGTYPE_ACK:
            LOG_INFO((logInfoBuf,"msgType: NL_MSGTYPE_ACK.\n"))
        break;
        case NL_MSGTYPE_MODULESTART:
            LOG_INFO((logInfoBuf,"msgType: NL_MSGTYPE_MODULESTART.\n"))
            /* start all working threads */
            initStartWorkingThreads();
            /* send ack to the user module */
            nlMsgShort.msgType = NL_MSGTYPE_ACK;
            netlinkSendMsg(NL_NLMODULE, &nlMsgShort, T_MSG_NL_SHORT_SIZE);
        break;
        case NL_MSGTYPE_MODULESTOP:
            LOG_INFO((logInfoBuf,"msgType: NL_MSGTYPE_MODULESTOP.\n"))
            /* stop all working threads. */
            stopDestroyWorkingThreads();
            /* send ack to the user module */
            nlMsgShort.msgType = NL_MSGTYPE_ACK;
            netlinkSendMsg(NL_NLMODULE, &nlMsgShort, T_MSG_NL_SHORT_SIZE);
        break;
        case NL_MSGTYPE_STATS_REQ:
            /*LOG_INFO((logInfoBuf,"msgType: NL_MSGTYPE_STATS_REQ.\n"))*/
            nlMsgLong.msgType = NL_MSGTYPE_STATS_REP;
            memcpy(nlMsgLong.payload,&outputQueueModuleCb.stats,sizeof(T_STATS));
            netlinkSendMsg(NL_NLMODULE, &nlMsgLong, sizeof(T_STATS)+2);
        break;
        case NL_MSGTYPE_CHANGE_SCHEDULER:
            LOG_INFO((logInfoBuf,"msgType: NL_MSGTYPE_CHANGE_SCHEDULER.\n"))
            setSchedulerType( *((int*)(((T_MSG_NL_LONG*)msg)->payload)) );
        break;
        case NL_MSGTYPE_SET_BACKLOG_TIME:
            LOG_INFO((logInfoBuf,"msgType: NL_MSGTYPE_SET_BACKLOG_TIME.\n"))
            setBacklogTime( *((int*)(((T_MSG_NL_LONG*)msg)->payload)) );
        break;        
        case NL_MSGTYPE_SET_SCHEDULERQUEUE_LENGTH:
            LOG_INFO((logInfoBuf,"msgType: NL_MSGTYPE_SET_SCHEDULERQUEUE_LENGTH.\n"))
            setSchedulerQueueLength( *((int*)(((T_MSG_NL_LONG*)msg)->payload)) );
        break;
        case NL_MSGTYPE_SET_EGRESS_LINK_RATE:
            LOG_INFO((logInfoBuf,"msgType: NL_MSGTYPE_SET_EGRESS_LINK_RATE.\n"))
            setEggressLinkRate( *((int*)(((T_MSG_NL_LONG*)msg)->payload)) );
        break;
        default:
            LOG_INFO((logInfoBuf,"msgType: default(%d)!\n",msg->msgType))
        break;
    }
    return 1;
}/*nlModuleHandler*/



