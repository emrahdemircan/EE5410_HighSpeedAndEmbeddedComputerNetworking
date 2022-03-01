/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* etherSender.c */
/********************************************************************************/

/********************************************************************************/
/* INCLUDES */
/********************************************************************************/
#include "outputQueueModule.x"

/********************************************************************************/
/* DEFINES */
/********************************************************************************/

/********************************************************************************/
/* FUNCTION PROTOTYPES */
/********************************************************************************/
/* Ethernet Sender Process! */
static void startEthernetSenderWakeUpHrTimer(void);
static void stopEthernetSenderWakeUpHrTimer(void);
static enum hrtimer_restart ethernetSenderWakeUpHrTimerCallback(struct hrtimer *timer);
int tailEthernetSenderQueue_MSG_ETHPACK(struct sk_buff *skb);
int tailEthernetSenderQueue_MSG_IPC(struct sk_buff *skb);
int initEthernetSenderThread(void);
int killEthernetSenderThread(void);
static void ethernetSenderThreadRoutine(T_KTHREAD* wThread);
static int ethernetSenderThreadHandler_MSG_DATA(struct sk_buff *skb);
static int ethernetSenderThreadHandler_MSG_IPC(struct sk_buff *skb);
/********************************************************************************/
/* GLOBALS */
/********************************************************************************/
/*thread structures*/
static T_KTHREAD            ethernetSenderThread;
static int                  ethernetSenderThread_running = 0;
static struct net_device*   outputDevice;
static struct sk_buff_head  ethernetSenderQueue;
static wait_queue_head_t    waitEthernetSenderQueue;
static int                  waitEthernetSenderQueueFlag = 0;

/********************************************************************************/
/* EXTERNS */
/********************************************************************************/

/********************************************************************************/
/* FUNCTIONS */
/********************************************************************************/

/********************************/
/* startEthernetSenderWakeUpHrTimer */
/********************************/
static void startEthernetSenderWakeUpHrTimer(void)
{
	LOG_INFO((logInfoBuf,"\n"))
	ethernetSenderThread.wakeUpAbsKtime = ktime_set(0,WAKEUPTIMER_NSEC);
	hrtimer_init(&ethernetSenderThread.wakeUpHrTimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	ethernetSenderThread.wakeUpHrTimer.function = &ethernetSenderWakeUpHrTimerCallback;
	LOG_INFO((logInfoBuf,"starting wakeUpHrTimer.\n"))
	hrtimer_start(&ethernetSenderThread.wakeUpHrTimer, ethernetSenderThread.wakeUpAbsKtime, HRTIMER_MODE_REL);
}/*startEthernetSenderWakeUpHrTimer*/

/********************************/
/* stopEthernetSenderWakeUpHrTimer */
/********************************/
static void stopEthernetSenderWakeUpHrTimer(void)
{
	LOG_INFO((logInfoBuf,"\n"))
	hrtimer_cancel(&ethernetSenderThread.wakeUpHrTimer);
}/*stopEthernetSenderWakeUpHrTimer*/

/********************************/
/* ethernetSenderWakeUpHrTimerCallback */
/********************************/
static enum hrtimer_restart ethernetSenderWakeUpHrTimerCallback(struct hrtimer *timer)
{
	hrtimer_forward_now(timer,ethernetSenderThread.wakeUpAbsKtime);
    waitEthernetSenderQueueFlag = 1;
	wake_up_interruptible(&waitEthernetSenderQueue);
	return HRTIMER_RESTART;
}/*ethernetSenderWakeUpHrTimerCallback*/

/********************************/
/* tailEthernetSenderQueue_MSG_ETHPACK */
/********************************/
int tailEthernetSenderQueue_MSG_ETHPACK(struct sk_buff *skb)
{
    outputQueueModuleCb.stats.ethernetTx.ethernetPacketIn++;
    if(ethernetSenderThread_running == 0)
    {
                outputQueueModuleCb.stats.ethernetTx.notQueued++;
		kfree_skb(skb);
		return -1;
    }
    setSkbMsgType(skb,MSG_DATA);
    /*paketin cikacagi ethernet arayuzunu isaretleyelim!*/
    skb->dev = outputDevice;
    skb_queue_tail(&ethernetSenderQueue, skb);
    outputQueueModuleCb.stats.ethernetTx.queued++;
    waitEthernetSenderQueueFlag = 1;
    wake_up_interruptible(&waitEthernetSenderQueue);
    return 1;
}/*tailEthernetSenderQueue_MSG_ETHPACK*/

/********************************/
/* tailEthernetSenderQueue_MSG_IPC */
/********************************/
int tailEthernetSenderQueue_MSG_IPC(struct sk_buff *skb)
{
    if(ethernetSenderThread_running == 0)
    {
                outputQueueModuleCb.stats.ethernetTx.notQueued++;
		kfree_skb(skb);
		return -1;
    }
    setSkbMsgType(skb,MSG_IPC);
    skb_queue_tail(&ethernetSenderQueue, skb);
    outputQueueModuleCb.stats.ethernetTx.queued++;
    waitEthernetSenderQueueFlag = 1;
    wake_up_interruptible(&waitEthernetSenderQueue);
    return 1;
}/*tailEthernetSenderQueue_MSG_IPC*/

/********************************/
/* initEthernetSenderThread */
/********************************/
int initEthernetSenderThread(void)
{	
	/*initialize and start initEthernetSenderThread*/
	if(ethernetSenderThread_running == 1)
	{
		LOG_INFO((logInfoBuf,"already running.\n"))
		return -1;
	}

    /* start thread */
    LOG_INFO((logInfoBuf,"initializing:\n"))
	memset(&ethernetSenderThread, 0, sizeof(T_KTHREAD));
    ethernetSenderThread.thread = kthread_run((void *)ethernetSenderThreadRoutine, &ethernetSenderThread,ETHERNETSENDER_THREAD_NAME);
    if(IS_ERR(ethernetSenderThread.thread))
	{
		LOG_INFO((logInfoBuf,"unable to start.\n"))
		return 0;
	}

    /* wait until thread start by checking thread running flag */
    while(ethernetSenderThread_running != 1)
	{
		msleep(10);
		THREAD_YIELD
	}
	return 1;
}/*initEthernetSenderThread*/

/********************************/
/* killEthernetSenderThread */
/********************************/
int killEthernetSenderThread(void)
{
    struct pid* pidPtr;
    int err;

	/*stop killEthernetSenderThreadRoutine*/
	if(ethernetSenderThread_running != 1)
	{
		LOG_INFO((logInfoBuf,"already not running.\n"))
		return -1;
	}

	LOG_INFO((logInfoBuf,"stopping...\n"))
    LOCK_KERNEL();
    pidPtr = task_pid(ethernetSenderThread.thread);
    err = kill_pid(pidPtr, SIGKILL, 1);
    UNLOCK_KERNEL();
    /* wakeup thread to process SIGKILL */
    waitEthernetSenderQueueFlag = 1;
	wake_up_interruptible(&waitEthernetSenderQueue);
    /* check if kill_pid succeeded */
    if(err < 0)
	{
		LOG_INFO((logInfoBuf,"unknown error %d while terminating.\n",err))
		return 0;
	}
	else 
	{
        /* kill_pid succeeded, wait for thread exit by checking thread running flag */
        while(ethernetSenderThread_running == 1)
		{
            LOG_INFO((logInfoBuf,"waiting...\n"))
            msleep(1000);
			THREAD_YIELD
		}
		LOG_INFO((logInfoBuf,"succesfully killed.\n"))
	}
	return 1;
}/*killEthernetSenderThread*/

/********************************/
/* ethernetSenderThreadRoutine */
/********************************/
static void ethernetSenderThreadRoutine(T_KTHREAD* wThread)
{
	struct sk_buff *skb;
    DEFINE_WAIT(wait);
	
	LOG_INFO((logInfoBuf,"initializing.\n"))
	/* kernel thread initialization */
    LOCK_KERNEL();
	current->flags |= PF_NOFREEZE;
    /*daemonize(MODULE_NAME);*/
    allow_signal(SIGKILL);
    UNLOCK_KERNEL();

	/*initialize output device*/
    LOG_INFO((logInfoBuf,"initializing output device %s.\n",ETHERNET_OUTPUT_SIDE_NAME))
	outputDevice = NULL;
	outputDevice = dev_get_by_name(&init_net,ETHERNET_OUTPUT_SIDE_NAME);
	if(outputDevice == NULL)
	{
		LOG_INFO((logInfoBuf,"outputDevice = NULL!\n"))
		return;
	}

	/*initialize the skb queue*/
	LOG_INFO((logInfoBuf,"initializing ethernetSenderQueue.\n"))
	skb_queue_head_init(&ethernetSenderQueue);

    /*initialize waitEthernetSenderQueue*/
	LOG_INFO((logInfoBuf,"initializing waitEthernetSenderQueue.\n"))
	init_waitqueue_head(&waitEthernetSenderQueue);
    waitEthernetSenderQueueFlag = 0;

	/*initialize and start wake up hr timer...*/
	startEthernetSenderWakeUpHrTimer();

	LOG_INFO((logInfoBuf,"initialized.\n"))
	ethernetSenderThread_running = 1;

    while(1)
    {
        if(signal_pending(current))
        {
                break;
        }

        /*sleep until someone wakes up!*/
        wait_event_interruptible(waitEthernetSenderQueue, waitEthernetSenderQueueFlag != 0 );

        while( (skb = skb_dequeue(&ethernetSenderQueue)) != NULL )
        {
            outputQueueModuleCb.stats.ethernetTx.dequeued++;
            switch(getSkbMsgType(skb))
            {
                case MSG_IPC:
                    ethernetSenderThreadHandler_MSG_IPC(skb);
                break;/*MSG_IPC*/
                case MSG_DATA:
                    ethernetSenderThreadHandler_MSG_DATA(skb);
                break;/*MSG_DATA*/
                default:
                        kfree_skb(skb);
                break;
            }/*switch(getSkbMsgType(skb))*/
            outputQueueModuleCb.stats.ethernetTx.processed++;
            waitEthernetSenderQueueFlag = 0;
        }
        THREAD_YIELD
    }

    /*stop wakeup hr timer...*/
    stopEthernetSenderWakeUpHrTimer();

    /*clean the skb queue*/
    LOG_INFO((logInfoBuf,"skb_queue_purge ->ethernetSenderQueue(%d).\n",skb_queue_len(&ethernetSenderQueue)))
    skb_queue_purge(&ethernetSenderQueue);

    /*clean output devices...*/
    LOG_INFO((logInfoBuf,"removing output device %s.\n",ETHERNET_OUTPUT_SIDE_NAME))
    dev_put(outputDevice);

    LOG_INFO((logInfoBuf,"exiting.\n"))

    ethernetSenderThread_running = 0;
		
}/*ethernetSenderThreadRoutine*/

/********************************/
/* ethernetSenderThreadHandler_MSG_DATA */
/********************************/
static int ethernetSenderThreadHandler_MSG_DATA(struct sk_buff *skb)
{
    struct ethhdr *eh;
    unsigned short ethType;

    outputQueueModuleCb.stats.ethernetTx.dataProcessed++;
    outputQueueModuleCb.stats.ethernetTx.ethernetPacketOut++;
    if(skb->dev == NULL)
    {
        LOG_INFO((logInfoBuf,"skb->dev=NULL!\n"))
        outputQueueModuleCb.stats.ethernetTx.sndFailed++;
        return -1;
    }
    /*this packet is for sending.*/
    skb->pkt_type = PACKET_OUTGOING;
    /*over the output device!*/
    skb->dev = outputDevice;
    /* access to the ethernet header and change the ether type */
    eh  = (struct ethhdr*)skb_mac_header(skb);
    ethType = ntohs(eh->h_proto);
    eh->h_proto = htons(ethType+0x1000);
    /*change source address*/
    memset(eh->h_source,0xaa,6);
    /*now send it!*/
    if(dev_queue_xmit(skb)!=0)
    {
        outputQueueModuleCb.stats.ethernetTx.sndFailed++;
        msleep(1);
        return -1;
    }
    outputQueueModuleCb.stats.ethernetTx.sndSucceeded++;
    return 1;
}/*ethernetSenderThreadHandler_MSG_DATA*/

/********************************/
/* ethernetSenderThreadHandler_MSG_IPC */
/********************************/
static int ethernetSenderThreadHandler_MSG_IPC(struct sk_buff *skb)
{
    /*static T_IPC_MSGHEADER ipcHdr;*/
    /*static unsigned char ipcMsg[MAX_IPCMSG_PAYLEN];*/
    outputQueueModuleCb.stats.ethernetTx.ipcProcessed++;
    kfree_skb(skb);
    return 1;
}/*ethernetSenderThreadHandler_MSG_IPC*/

