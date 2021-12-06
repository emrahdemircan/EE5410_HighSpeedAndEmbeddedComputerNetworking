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
/* Ethernet Receiver Process! */
static int rawEtherPackHandler(struct sk_buff *skb, struct net_device *dev, struct packet_type *pt, struct net_device *orig_dev);
static void startEthernetReceiverWakeUpHrTimer(void);
static void stopEthernetReceiverWakeUpHrTimer(void);
static enum hrtimer_restart ethernetReceiverWakeUpHrTimerCallback(struct hrtimer *timer);
int tailEthernetReceiverQueue_MSG_ETHPACK(struct sk_buff *skb,unsigned short ethType);
int tailEthernetReceiverQueue_MSG_IPC(struct sk_buff *skb);
int initEthernetReceiverThread(void);
int killEthernetReceiverThread(void);
static void ethernetReceiverThreadRoutine(T_KTHREAD* wThread);
static int ethernetReceiverThreadHandler_MSG_DATA(struct sk_buff *skb);
static int ethernetReceiverThreadHandler_MSG_IPC(struct sk_buff *skb);
/********************************************************************************/
/* GLOBALS */
/********************************************************************************/
/*thread structures*/
static T_KTHREAD ethernetReceiverThread;
static int ethernetReceiverThread_running = 0;
static struct net_device *inputDevice;
static struct packet_type packetType_ETH_P_ALL;
static struct sk_buff_head ethernetReceiverQueue;
static wait_queue_head_t waitEthernetReceiverQueue;

/********************************************************************************/
/* EXTERNS */
/********************************************************************************/

/********************************************************************************/
/* FUNCTIONS */
/********************************************************************************/

/********************************/
/* startEthernetReceiverWakeUpHrTimer */
/********************************/
static void startEthernetReceiverWakeUpHrTimer(void)
{
	LOG_INFO((logInfoBuf,"\n"))
	ethernetReceiverThread.wakeUpAbsKtime = ktime_set(0,WAKEUPTIMER_NSEC);
	hrtimer_init(&ethernetReceiverThread.wakeUpHrTimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	ethernetReceiverThread.wakeUpHrTimer.function = &ethernetReceiverWakeUpHrTimerCallback;
	LOG_INFO((logInfoBuf,"starting wakeUpHrTimer.\n"))
	hrtimer_start(&ethernetReceiverThread.wakeUpHrTimer, ethernetReceiverThread.wakeUpAbsKtime, HRTIMER_MODE_REL);
}/*startEthernetReceiverWakeUpHrTimer*/

/********************************/
/* stopEthernetReceiverWakeUpHrTimer */
/********************************/
static void stopEthernetReceiverWakeUpHrTimer(void)
{
	LOG_INFO((logInfoBuf,"\n"))
	hrtimer_cancel(&ethernetReceiverThread.wakeUpHrTimer);
}/*stopEthernetReceiverWakeUpHrTimer*/

/********************************/
/* ethernetReceiverWakeUpHrTimerCallback */
/********************************/
static enum hrtimer_restart ethernetReceiverWakeUpHrTimerCallback(struct hrtimer *timer)
{
	hrtimer_forward_now(timer,ethernetReceiverThread.wakeUpAbsKtime);
	wake_up_interruptible(&waitEthernetReceiverQueue);
	return HRTIMER_RESTART;
}/*ethernetReceiverWakeUpHrTimerCallback*/

/********************************/
/* tailEthernetReceiverQueue_MSG_ETHPACK */
/********************************/
int tailEthernetReceiverQueue_MSG_ETHPACK(struct sk_buff *skb, unsigned short ethType)
{
    outputQueueModuleCb.stats.ethernetRx.ethernetPacketIn++;
    if(ethernetReceiverThread_running == 0)
    {
		outputQueueModuleCb.stats.ethernetRx.notQueued++;
		kfree_skb(skb);
		return -1;
    }
    setSkbMsgType(skb,MSG_DATA);
    /*label each incoming ethernet frame skb with its corresponding priority*/
    setSkbPriority(skb,determinePriority(ethType));
    skb_queue_tail(&ethernetReceiverQueue, skb);
    outputQueueModuleCb.stats.ethernetRx.queued++;
    wake_up_interruptible(&waitEthernetReceiverQueue);
    return 1;
}/*tailEthernetReceiverQueue_MSG_ETHPACK*/


/********************************/
/* tailEthernetReceiverQueue_MSG_IPC */
/********************************/
int tailEthernetReceiverQueue_MSG_IPC(struct sk_buff *skb)
{
    if(ethernetReceiverThread_running == 0)
    {
		outputQueueModuleCb.stats.ethernetRx.notQueued++;
		kfree_skb(skb);
		return -1;
    }
    setSkbMsgType(skb,MSG_IPC);
    skb_queue_tail(&ethernetReceiverQueue, skb);
    outputQueueModuleCb.stats.ethernetRx.queued++;
    wake_up_interruptible(&waitEthernetReceiverQueue);
    return 1;
}/*tailEthernetReceiverQueue_MSG_IPC*/

/********************************/
/* initEthernetReceiverThread */
/********************************/
int initEthernetReceiverThread(void)
{	
	/*initialize and start initEthernetReceiverThread*/
	if(ethernetReceiverThread_running == 1)
	{
		LOG_INFO((logInfoBuf,"already running.\n"))
		return -1;
	}
	LOG_INFO((logInfoBuf,"initializing\n"))
	memset(&ethernetReceiverThread, 0, sizeof(T_KTHREAD));
        ethernetReceiverThread.thread = kthread_run((void *)ethernetReceiverThreadRoutine, &ethernetReceiverThread,ETHERNETRECEIVER_THREAD_NAME);
	if (IS_ERR(ethernetReceiverThread.thread)) 
	{
		LOG_INFO((logInfoBuf,"unable to start.\n"))
		return 0;
	}
	while (ethernetReceiverThread_running != 1)
	{
		msleep(10);
		THREAD_YIELD
	}
	return 1;
}/*initEthernetReceiverThread*/

/********************************/
/* killEthernetReceiverThread */
/********************************/
int killEthernetReceiverThread(void)
{
	int err;

	/*stop killEthernetReceiverThreadRoutine*/
	if(ethernetReceiverThread_running != 1)
	{
		LOG_INFO((logInfoBuf,"already not running.\n"))
		return -1;
	}

	LOG_INFO((logInfoBuf,"stopping...\n"))
	lock_kernel();
	err = kill_pid(ethernetReceiverThread.thread->pids[PIDTYPE_PID].pid, SIGKILL, 1);
	unlock_kernel();
	/*oldurmek istedigimiz thread waitQueue'da duruyor olabilir. Uyandiralim ki SIG_KILL'i islesin*/
	wake_up_interruptible(&waitEthernetReceiverQueue);
	if (err < 0)
	{
		LOG_INFO((logInfoBuf,"unknown error %d while terminating.\n",err))
		return 0;
	}
	else 
	{
		while (ethernetReceiverThread_running == 1)
		{
			msleep(10);
			THREAD_YIELD
		}
		LOG_INFO((logInfoBuf,"succesfully killed.\n"))
	}
	return 1;
}/*killEthernetReceiverThread*/

/******************************************************************************/
/*if_ether.h*/
/*
struct ethhdr *eh;
unsigned short ethType;	
eh  = (struct ethhdr*)skb_mac_header(skb);
ethType = ntohs(eh->h_proto);
*/
/*IP -> ETH_P_IP (0x0800)*/
/*ARP -> ETH_P_ARP (0x0806)*/
/*bu asamaya gelen bir skb'nin data kismindan ethernet header kadar kisim skb->mac_header'a yazilip,
data kismi mac header kadar otelenmistir. Bu nedenle alinan skb'yi tekrar ethernete basmadan once
yeterli headroom varsa (14 byte) skb_push ile yer acip, o noktaya ethernet headeri yazmaliyiz!*/
/******************************************************************************/

/********************************/
/* rawEtherPackHandler */
/********************************/
static int rawEtherPackHandler(struct sk_buff *skb, struct net_device *dev, struct packet_type *pt, struct net_device *orig_dev)
{
	struct ethhdr *eh;
	unsigned short ethType;
	/* access to the ethernet header and proceed according to the the ether type */
	eh  = (struct ethhdr*)skb_mac_header(skb);
	ethType = ntohs(eh->h_proto);
        /* only the ethernet packets with type similar to ETHERTYPE_TOBESTOLEN are processed further in this module*/
        if( (ethType>=ETHERTYPE_TOBESTOLEN_BEGIN) && (ethType<=ETHERTYPE_TOBESTOLEN_END) )
	{
		/*write skb to ethernet receive queue and wake ethernetReceiverThread up*/
		tailEthernetReceiverQueue_MSG_ETHPACK(skb,ethType);
                return NET_RX_DROP;
	}
	/* kfree_skb is used just to decrement the usage count of the kernel buffer until end of life. */
        kfree_skb(skb);
        /* as this callback is registered by ETH_P_ALL, return type does not matter actually. */
        /* Linux kernel will pass this packet to other specific handlers registered, thus returning */
        /* NET_RX_DROP does not make sense! */
        return NET_RX_SUCCESS;
}/*rawEtherPackHandler*/


/********************************/
/* ethernetReceiverThreadRoutine */
/********************************/
static void ethernetReceiverThreadRoutine(T_KTHREAD* wThread)
{
	struct sk_buff *skb;
	
	LOG_INFO((logInfoBuf,"initializing.\n"))
	/* kernel thread initialization */
	lock_kernel();
	current->flags |= PF_NOFREEZE;
	/* daemonize (take care with signals, after daemonize() they are disabled) */
	daemonize(MODULE_NAME);
	allow_signal(SIGKILL);
	unlock_kernel();

        /*initialize input device*/
        LOG_INFO((logInfoBuf,"initializing input device %s.\n",ETHERNET_INPUT_SIDE_NAME))
        inputDevice = NULL;
        inputDevice = dev_get_by_name(&init_net,ETHERNET_INPUT_SIDE_NAME);
        if(inputDevice == NULL)
        {
                LOG_INFO((logInfoBuf,"inputDevice = NULL!\n"))
                return;
        }

	/*ETH_P_ALL icin kaydolunca gidip gelen tum ethernet paketlerine erisim saglaniyor.*/
	/*Ozellikle baska bir ETH tipi icin kaydolunca sadece o tipteki gelen paketlere erisim saglaniyor.*/
        LOG_INFO((logInfoBuf,"dev_add_pack for ETH_P_ALL.\n"))
        packetType_ETH_P_ALL.type = htons(ETH_P_ALL);
	packetType_ETH_P_ALL.func = rawEtherPackHandler;
        packetType_ETH_P_ALL.dev = inputDevice;
	dev_add_pack(&packetType_ETH_P_ALL);

	/*initialize the skb queue*/
	LOG_INFO((logInfoBuf,"initializing ethernetReceiverQueue.\n"))
	skb_queue_head_init(&ethernetReceiverQueue);
	/*initialize waitEthernetReceiverQueue*/
	LOG_INFO((logInfoBuf,"initializing waitEthernetReceiverQueue.\n"))
	init_waitqueue_head(&waitEthernetReceiverQueue);

	/*initialize and start wake up hr timer...*/
	startEthernetReceiverWakeUpHrTimer();

	LOG_INFO((logInfoBuf,"initialized.\n"))
	ethernetReceiverThread_running = 1;
	
	while(1)
	{
            if (signal_pending(current))
            {
                    break;
            }

            /*sleep until someone wakes up!*/
            interruptible_sleep_on(&waitEthernetReceiverQueue);
            while( (skb = skb_dequeue(&ethernetReceiverQueue)) != NULL )
            {
                outputQueueModuleCb.stats.ethernetRx.dequeued++;
                switch(getSkbMsgType(skb))
                {
                    case MSG_IPC:
                            ethernetReceiverThreadHandler_MSG_IPC(skb);
                    break;/*MSG_IPC*/
                    case MSG_DATA:
                            ethernetReceiverThreadHandler_MSG_DATA(skb);
                    break;/*MSG_DATA*/
                    default:
                    kfree_skb(skb);
                    break;
                }/*switch(getSkbMsgType(skb))*/
                outputQueueModuleCb.stats.ethernetRx.processed++;
            }
            THREAD_YIELD
	}

	/*stop wakeup hr timer...*/
	stopEthernetReceiverWakeUpHrTimer();

	/*stop ethernet ethernet interfaces...*/
        LOG_INFO((logInfoBuf,"dev_remove_pack for ETH_P_ALL\n"))
	dev_remove_pack(&packetType_ETH_P_ALL);

	/*clean the skb queue*/
        LOG_INFO((logInfoBuf,"skb_queue_purge ->ethernetReceiverQueue(%d).\n",skb_queue_len(&ethernetReceiverQueue)))
	skb_queue_purge(&ethernetReceiverQueue);

        /*clean input devices...*/
        LOG_INFO((logInfoBuf,"removing input device %s.\n",ETHERNET_INPUT_SIDE_NAME))
        dev_put(inputDevice);

	LOG_INFO((logInfoBuf,"exiting.\n"))

	ethernetReceiverThread_running = 0;
		
}/*ethernetReceiverThreadRoutine*/

/********************************/
/* ethernetReceiverThreadHandler_MSG_DATA */
/********************************/
static int ethernetReceiverThreadHandler_MSG_DATA(struct sk_buff *skb)
{
    outputQueueModuleCb.stats.ethernetRx.dataProcessed++;
    if(skb->dev == NULL)
    {
        LOG_INFO((logInfoBuf,"skb->dev=NULL!\n"))
        return -1;
    }
    /*the data pointer is shifted left at this point*/
    /* we should fix it ETH_LEN bytes right and put resultant pointer to mac_header field. */
    skb->mac_header = skb_push(skb,ETH_HLEN);
    /*send this ethernet packet to the corresponding kernel thread.*/
    tailEthernetSchedulerQueue_MSG_ETHPACK(skb);
    return 1;
}/*ethernetReceiverThreadHandler_MSG_DATA*/

/********************************/
/* ethernetReceiverThreadHandler_MSG_IPC */
/********************************/
static int ethernetReceiverThreadHandler_MSG_IPC(struct sk_buff *skb)
{
    /*static T_IPC_MSGHEADER ipcHdr;*/
    /*static unsigned char ipcMsg[MAX_IPCMSG_PAYLEN];*/
    outputQueueModuleCb.stats.ethernetRx.ipcProcessed++;
    kfree_skb(skb);
    return 1;
}/*ethernetReceiverThreadHandler_MSG_IPC*/

