/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* etherScheduler.c */
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
/* Ethernet Scheduler Process! */
static void startEthernetSchedulerWakeUpHrTimer(void);
static void stopEthernetSchedulerWakeUpHrTimer(void);
static enum hrtimer_restart ethernetSchedulerWakeUpHrTimerCallback(struct hrtimer *timer);
static void startEthernetTransmitWakeUpHrTimer(unsigned int linkRate);
static void stopEthernetTransmitWakeUpHrTimer(void);
static enum hrtimer_restart ethernetTransmitWakeUpHrTimerCallback(struct hrtimer *timer);
int tailEthernetSchedulerQueue_MSG_ETHPACK(struct sk_buff *skb);
int initEthernetSchedulerThread(void);
int killEthernetSchedulerThread(void);
static void ethernetSchedulerThreadRoutine(T_KTHREAD* wThread);
static int ethernetSchedulerThreadHandler_MSG_ETHPACK(struct sk_buff *skb, unsigned short qNumber);
void setSchedulerType(T_SCHEDULER_TYPE_ENUM schedulerType);
void setBacklogTime(unsigned int timeInMsecs);
void setSchedulerQueueLength(unsigned int lengthInBytes);
void setEggressLinkRate(unsigned int rate);
static unsigned int calculateQueueUsage(unsigned int currentSize, unsigned int size);
static void setSchedulerDequeueStats(struct sk_buff *skb, unsigned short qNumber);
/* general enqueue function*/
static int enqueueSkbToPriorityQueue(struct sk_buff *skb,unsigned char priority);
/* FIFO */
static void initFifo(void);
static int fifoSchedulerEnqueue(struct sk_buff *skb);
static void fifoSchedulerDequeue(void);
/*round robin*/
static void initRoundRobin(void);
static int roundRobinSchedulerEnqueue(struct sk_buff *skb);
static void roundRobinSchedulerDequeue(void);
/*weighted round robin*/
static void initWeightedRoundRobin(void);
static int weightedRoundRobinSchedulerEnqueue(struct sk_buff *skb);
static void weightedRoundRobinSchedulerDequeue(void);
/*deficit round robin*/
static void initDeficitRoundRobin(void);
static int deficitRoundRobinSchedulerEnqueue(struct sk_buff *skb);
static void deficitRoundRobinSchedulerDequeue(void);
/*WF2Q*/
static void initWf2q(void);
static int wf2qSchedulerEnqueue(struct sk_buff *skb);
static void wf2qSchedulerDequeue(void);
/*DTable*/
static void initDTable(void);
static int dTableSchedulerEnqueue(struct sk_buff *skb);
static void dTableSchedulerDequeue(void);
/********************************************************************************/
/* GLOBALS */
/********************************************************************************/
/*thread structures*/
static T_KTHREAD ethernetSchedulerThread;
static int ethernetSchedulerThread_running = 0;
static T_SCHEDULER_QUEUE_CB schedulerCb;

/* the scheduler function ptr array */
T_SCHEDULER_ENQUEUEFNCPTR qosSchedulerEnqueue;
T_SCHEDULER_DEQUEUEFNCPTR qosSchedulerDequeue;
T_SCHEDULER_TYPE_ENUM currentScheduler = DEFAULT_SCHEDULER;
unsigned int    backLogTimeInMsecs = DEFAULT_BACKLOGTIME_IN_MSECS;
unsigned int    schedulerQueueLengthInBytes = DEFAULT_SCHEDULERQUEUELENGTH_IN_BYTES;
unsigned int    schedulerEggressLinkRateInMBits = DEFAULT_EGGRESSLINK_RATE;
/*FIFO*/
static T_FIFO_CB fifoCb;
/*round robin*/
static T_ROUNDROBIN_CB roundRobinCb;
/*weighted round robin*/
static T_WEIGHTED_ROUNDROBIN_CB weightedRoundRobinCb;
/*deficit round robin*/
static T_DEFICIT_ROUNDROBIN_CB deficitRoundRobinCb;
/*WF2Q*/
static T_WF2Q_CB wf2qCb;
/*DTABLE*/
static T_DEFICIT_TABLE_CB dTableCb;

/********************************************************************************/
/* EXTERNS */
/********************************************************************************/

/********************************************************************************/
/* FUNCTIONS */
/********************************************************************************/

/********************************/
/* startEthernetSchedulerWakeUpHrTimer */
/********************************/
static void startEthernetSchedulerWakeUpHrTimer(void)
{
        LOG_INFO((logInfoBuf,"\n"))
        ethernetSchedulerThread.wakeUpAbsKtime = ktime_set(0,WAKEUPTIMER_NSEC/1000);
        hrtimer_init(&ethernetSchedulerThread.wakeUpHrTimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
        ethernetSchedulerThread.wakeUpHrTimer.function = &ethernetSchedulerWakeUpHrTimerCallback;
        LOG_INFO((logInfoBuf,"starting wakeUpHrTimer.\n"))
        hrtimer_start(&ethernetSchedulerThread.wakeUpHrTimer, ethernetSchedulerThread.wakeUpAbsKtime, HRTIMER_MODE_REL);
}/*startEthernetSchedulerWakeUpHrTimer*/

/********************************/
/* stopEthernetSchedulerWakeUpHrTimer */
/********************************/
static void stopEthernetSchedulerWakeUpHrTimer(void)
{
        LOG_INFO((logInfoBuf,"\n"))
        hrtimer_cancel(&ethernetSchedulerThread.wakeUpHrTimer);
}/*stopEthernetSchedulerWakeUpHrTimer*/

/********************************/
/* ethernetSchedulerWakeUpHrTimerCallback */
/********************************/
static enum hrtimer_restart ethernetSchedulerWakeUpHrTimerCallback(struct hrtimer *timer)
{
        hrtimer_forward_now(timer,ethernetSchedulerThread.wakeUpAbsKtime);
        wake_up_interruptible(&schedulerCb.waitEthernetSchedulerQueue);
        return HRTIMER_RESTART;
}/*ethernetSchedulerWakeUpHrTimerCallback*/

/********************************/
/* startEthernetTransmitWakeUpHrTimer */
/********************************/
static void startEthernetTransmitWakeUpHrTimer(unsigned int linkRateInMBits)
{
        unsigned int timeoutValue;
        LOG_INFO((logInfoBuf,"linkRate:%d MBits/sec\n",linkRateInMBits))
        timeoutValue = (ONEMBIT_ONEBYTE_TRANSMIT_WAKEUPTIMER_NSEC*TRANSMISSION_WAIT_UNIT_LENGTH_IN_BITS)/linkRateInMBits;
        timeoutValue = timeoutValue/14; /*this is a refactoring division by inspecting cpu performance*/
        schedulerCb.transmitWakeUpAbsKtime = ktime_set(0,timeoutValue);
        LOG_INFO((logInfoBuf,"timeoutValue:%d nsecs\n",timeoutValue))
        hrtimer_init(&schedulerCb.transmitWakeUpHrTimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
        schedulerCb.transmitWakeUpHrTimer.function = &ethernetTransmitWakeUpHrTimerCallback;
        LOG_INFO((logInfoBuf,"starting wakeUpHrTimer.\n"))
        hrtimer_start(&schedulerCb.transmitWakeUpHrTimer, schedulerCb.transmitWakeUpAbsKtime, HRTIMER_MODE_REL);
}/*startEthernetTransmitWakeUpHrTimer*/

/********************************/
/* stopEthernetTransmitWakeUpHrTimer */
/********************************/
static void stopEthernetTransmitWakeUpHrTimer(void)
{
        LOG_INFO((logInfoBuf,"\n"))
        hrtimer_cancel(&schedulerCb.transmitWakeUpHrTimer);
}/*stopEthernetTransmitWakeUpHrTimer*/

/********************************/
/* ethernetTransmitWakeUpHrTimerCallback */
/********************************/
static enum hrtimer_restart ethernetTransmitWakeUpHrTimerCallback(struct hrtimer *timer)
{
        hrtimer_forward_now(timer,schedulerCb.transmitWakeUpAbsKtime);
        wake_up_interruptible(&schedulerCb.waitEthernetTransmitQueue);
        return HRTIMER_RESTART;
}/*ethernetTransmitWakeUpHrTimerCallback*/

/********************************/
/* tailEthernetSchedulerQueue_MSG_ETHPACK */
/********************************/
int tailEthernetSchedulerQueue_MSG_ETHPACK(struct sk_buff *skb)
{
    outputQueueModuleCb.stats.ethernetSch.ethernetPacketIn++;
    /*stamp the time for reception of the packet*/
    setSkbTimeStamp(skb);
    /* enqueue the packet!*/
    qosSchedulerEnqueue(skb);
    wake_up_interruptible(&schedulerCb.waitEthernetSchedulerQueue);
    return 1;
}/*tailEthernetSchedulerQueue_MSG_ETHPACK*/

/********************************/
/* initEthernetSchedulerThread */
/********************************/
int initEthernetSchedulerThread(void)
{
        /*initialize and start initEthernetSchedulerThread*/
        if(ethernetSchedulerThread_running == 1)
        {
                LOG_INFO((logInfoBuf,"already running.\n"))
                return -1;
        }
        LOG_INFO((logInfoBuf,"initializing:\n"))
        memset(&ethernetSchedulerThread, 0, sizeof(T_KTHREAD));
        ethernetSchedulerThread.thread = kthread_run((void *)ethernetSchedulerThreadRoutine, &ethernetSchedulerThread,ETHERNETSCHEDULER_THREAD_NAME);
        if (IS_ERR(ethernetSchedulerThread.thread))
        {
                LOG_INFO((logInfoBuf,"unable to start.\n"))
                return 0;
        }
        while (ethernetSchedulerThread_running != 1)
        {
                msleep(10);
                THREAD_YIELD
        }
        return 1;
}/*initEthernetSchedulerThread*/

/********************************/
/* killEthernetSchedulerThread */
/********************************/
int killEthernetSchedulerThread(void)
{
        int err;

        /*stop killEthernetSchedulerThreadRoutine*/
        if(ethernetSchedulerThread_running != 1)
        {
                LOG_INFO((logInfoBuf,"already not running.\n"))
                return -1;
        }

        LOG_INFO((logInfoBuf,"stopping...\n"))
        lock_kernel();
        err = kill_pid(ethernetSchedulerThread.thread->pids[PIDTYPE_PID].pid, SIGKILL, 1);
        unlock_kernel();
        /*oldurmek istedigimiz thread waitQueue'da duruyor olabilir. Uyandiralim ki SIG_KILL'i islesin*/
        wake_up_interruptible(&schedulerCb.waitEthernetSchedulerQueue);
        if (err < 0)
        {
                LOG_INFO((logInfoBuf,"unknown error %d while terminating.\n",err))
                return 0;
        }
        else
        {
                while (ethernetSchedulerThread_running == 1)
                {
                        msleep(10);
                        THREAD_YIELD
                }
                LOG_INFO((logInfoBuf,"succesfully killed.\n"))
        }
        return 1;
}/*killEthernetSchedulerThread*/

/********************************/
/* ethernetSchedulerThreadRoutine */
/********************************/
static void ethernetSchedulerThreadRoutine(T_KTHREAD* wThread)
{
        unsigned short i;

        LOG_INFO((logInfoBuf,"initializing.\n"))
        /* kernel thread initialization */
        lock_kernel();
        current->flags |= PF_NOFREEZE;
        /* daemonize (take care with signals, after daemonize() they are disabled) */
        daemonize(MODULE_NAME);
        allow_signal(SIGKILL);
        unlock_kernel();

        /*initialize the scheduler queues*/
        for(i=0; i<NUM_OF_ETHERNET_PRIORITY_CLASSES; i++)
        {
            LOG_INFO((logInfoBuf,"initializing queue[%d].qHead\n",i))
            skb_queue_head_init(&schedulerCb.queue[i].qHead);
            schedulerCb.queue[i].size = schedulerQueueLengthInBytes;
            schedulerCb.queue[i].currentSize = 0;
        }

        /*initialize schedulerCb.waitEthernetSchedulerQueue*/
        LOG_INFO((logInfoBuf,"initializing schedulerCb.waitEthernetSchedulerQueue.\n"))
        init_waitqueue_head(&schedulerCb.waitEthernetSchedulerQueue);

        /*initialize schedulerCb.waitEthernetTransmitQueue*/
        LOG_INFO((logInfoBuf,"initializing schedulerCb.waitEthernetTransmitQueue.\n"))
        init_waitqueue_head(&schedulerCb.waitEthernetTransmitQueue);

        /*initialize the schedulers array*/
        LOG_INFO((logInfoBuf,"initializing scheduler functions list.\n"))

        /*initialize the selected scheduler*/
        switch(currentScheduler)
        {
            case FIFO:
                LOG_INFO((logInfoBuf,"currentScheduler: FIFO \n"))
                initFifo();
                schedulerCb.queue[DEFAULT_FIFO_QUEUE].size = NUM_OF_ETHERNET_PRIORITY_CLASSES*schedulerQueueLengthInBytes;
                qosSchedulerEnqueue = fifoSchedulerEnqueue;
                qosSchedulerDequeue = fifoSchedulerDequeue;
            break;
            case ROUND_ROBIN:
                LOG_INFO((logInfoBuf,"currentScheduler: ROUND_ROBIN \n"))
                initRoundRobin();
                qosSchedulerEnqueue = roundRobinSchedulerEnqueue;
                qosSchedulerDequeue = roundRobinSchedulerDequeue;
            break;
            case WEIGHTED_ROUND_ROBIN:
                LOG_INFO((logInfoBuf,"currentScheduler: WEIGHTED_ROUND_ROBIN \n"))
                initWeightedRoundRobin();
                qosSchedulerEnqueue = weightedRoundRobinSchedulerEnqueue;
                qosSchedulerDequeue = weightedRoundRobinSchedulerDequeue;
            break;
            case DEFICIT_ROUND_ROBIN:
                LOG_INFO((logInfoBuf,"currentScheduler: DEFICIT_ROUND_ROBIN \n"))
                initDeficitRoundRobin();
                qosSchedulerEnqueue = deficitRoundRobinSchedulerEnqueue;
                qosSchedulerDequeue = deficitRoundRobinSchedulerDequeue;
            break;
            case WF2Q:
                LOG_INFO((logInfoBuf,"currentScheduler: WF2Q \n"))
                initWf2q();
                qosSchedulerEnqueue = wf2qSchedulerEnqueue;
                qosSchedulerDequeue = wf2qSchedulerDequeue;
            break;
            case DTABLE:
                LOG_INFO((logInfoBuf,"currentScheduler: DTABLE \n"))
                initDTable();
                qosSchedulerEnqueue = dTableSchedulerEnqueue;
                qosSchedulerDequeue = dTableSchedulerDequeue;
            break;
            default:
                LOG_INFO((logInfoBuf,"currentScheduler: %d HATA!",currentScheduler))
                return;
            break;
        }

        /*initialize and start scheduler wake up hr timer...*/
        startEthernetSchedulerWakeUpHrTimer();

        /*initialize and start transmit wake up hr timer...*/
        startEthernetTransmitWakeUpHrTimer(schedulerEggressLinkRateInMBits);

        LOG_INFO((logInfoBuf,"initialized.\n"))
        ethernetSchedulerThread_running = 1;
        /* let task sleep for backLogTimeInMsecs duration to backlog packets to be scheduled.*/
        msleep(backLogTimeInMsecs);/**/
        /*enter the loop for scheduling*/
        while(1)
        {
            if (signal_pending(current))
            {
                    break;
            }
            qosSchedulerDequeue();
            THREAD_YIELD
        }

        /*stop scheduler wake up hr timer...*/
        stopEthernetSchedulerWakeUpHrTimer();

        /*stop transmit wake up hr timer...*/
        stopEthernetTransmitWakeUpHrTimer();

        /*clean the skb queues*/
        for(i=0; i<NUM_OF_ETHERNET_PRIORITY_CLASSES; i++)
        {
            LOG_INFO((logInfoBuf,"skb_queue_purge ->qHead[%d](%d).\n",i,skb_queue_len(&schedulerCb.queue[i].qHead)))
            skb_queue_purge(&schedulerCb.queue[i].qHead);
        }

        LOG_INFO((logInfoBuf,"exiting.\n"))

        ethernetSchedulerThread_running = 0;

}/*ethernetSchedulerThreadRoutine*/

/*******************DEFAULT_EGGRESSLINKRATE*************/
/* ethernetSchedulerThreadHandler_MSG_ETHPACK */
/********************************/
static int ethernetSchedulerThreadHandler_MSG_ETHPACK(struct sk_buff *skb, unsigned short qNumber)
{
    short packetLengthInBytes;
    outputQueueModuleCb.stats.ethernetSch.dataProcessed++;
    if(skb->dev == NULL)
    {
        LOG_INFO((logInfoBuf,"skb->dev=NULL!\n"))
        outputQueueModuleCb.stats.ethernetSch.sndFailed++;
        return -1;
    }
    packetLengthInBytes = skb->len;
    while( packetLengthInBytes > 0)
    {
        /*sleep until someone wakes up!*/
        interruptible_sleep_on(&schedulerCb.waitEthernetTransmitQueue);
        packetLengthInBytes-=TRANSMISSION_WAIT_UNIT_LENGTH_IN_BYTES;
    }
    /*sleep until someone wakes up!*/
    interruptible_sleep_on(&schedulerCb.waitEthernetTransmitQueue);
    /*send this ethernet packet to the corresponding kernel thread.*/
    tailEthernetSenderQueue_MSG_ETHPACK(skb);
    /* set the statistics*/
    setSchedulerDequeueStats(skb,qNumber);
    outputQueueModuleCb.stats.ethernetSch.sndSucceeded++;
    return 1;
}/*ethernetSchedulerThreadHandler_MSG_ETHPACK*/

/********************************/
/* setSchedulerType */
/********************************/
void setSchedulerType(T_SCHEDULER_TYPE_ENUM schedulerType)
{
    LOG_INFO((logInfoBuf,": schedulerType:%d \n",schedulerType))
    if( schedulerType >= NUM_OF_SCHEDULERS )
    {
        LOG_INFO((logInfoBuf,": schedulerType:%d >= NUM_OF_SCHEDULERS(%d)\n",schedulerType,NUM_OF_SCHEDULERS))
        currentScheduler = DEFAULT_SCHEDULER;
    }
    else
    {
        currentScheduler = schedulerType;
    }
    LOG_INFO((logInfoBuf,": currentScheduler:%d \n",currentScheduler))
    return;
}/*setSchedulerType*/

/********************************/
/* setBacklogTime */
/********************************/
void setBacklogTime(unsigned int timeInMsecs)
{
    LOG_INFO((logInfoBuf,": timeInMsecs:%d \n",timeInMsecs))

    if( timeInMsecs < MIN_BACKLOGTIME_IN_MSECS )
    {
        LOG_INFO((logInfoBuf,": timeInMsecs:%d < MIN_BACKLOGTIME_IN_MSECS(%d)\n",timeInMsecs,MIN_BACKLOGTIME_IN_MSECS))
        timeInMsecs = DEFAULT_BACKLOGTIME_IN_MSECS;
    }

    if( timeInMsecs > MAX_BACKLOGTIME_IN_MSECS )
    {
        LOG_INFO((logInfoBuf,": timeInMsecs:%d > MAX_BACKLOGTIME_IN_MSECS(%d)\n",timeInMsecs,MAX_BACKLOGTIME_IN_MSECS))
        timeInMsecs = DEFAULT_BACKLOGTIME_IN_MSECS;
    }

    backLogTimeInMsecs = timeInMsecs;
    LOG_INFO((logInfoBuf,": backLogTimeInMsecs:%d \n",backLogTimeInMsecs))
    return;
}/*setBacklogTime*/

/********************************/
/* setSchedulerQueueLength */
/********************************/
void setSchedulerQueueLength(unsigned int lengthInBytes)
{
    LOG_INFO((logInfoBuf,": lengthInBytes:%d \n",lengthInBytes))

    if( lengthInBytes < MIN_SCHEDULERQUEUELENGTH_IN_BYTES )
    {
        LOG_INFO((logInfoBuf,": lengthInBytes:%d < MIN_SCHEDULERQUEUELENGTH_IN_BYTES(%d)\n",lengthInBytes,MIN_SCHEDULERQUEUELENGTH_IN_BYTES))
        lengthInBytes = DEFAULT_SCHEDULERQUEUELENGTH_IN_BYTES;
    }

    if( lengthInBytes > MAX_SCHEDULERQUEUELENGTH_IN_BYTES )
    {
        LOG_INFO((logInfoBuf,": lengthInBytes:%d > MAX_SCHEDULERQUEUELENGTH_IN_BYTES(%d)\n",lengthInBytes,MAX_SCHEDULERQUEUELENGTH_IN_BYTES))
        lengthInBytes = DEFAULT_SCHEDULERQUEUELENGTH_IN_BYTES;
    }

    schedulerQueueLengthInBytes = lengthInBytes;
    LOG_INFO((logInfoBuf,": schedulerQueueLengthInBytes:%d \n",schedulerQueueLengthInBytes))
    return;
}/*setSchedulerQueueLength*/

/********************************/
/* setEggressLinkRate */
/********************************/
void setEggressLinkRate(unsigned int rate)
{
    LOG_INFO((logInfoBuf,": rate:%d \n",rate))

    if( rate < MIN_EGGRESSLINK_RATE )
    {
        LOG_INFO((logInfoBuf,": rate:%d < MIN_EGGRESSLINK_RATE(%d)\n",rate,MIN_EGGRESSLINK_RATE))
        rate = DEFAULT_EGGRESSLINK_RATE;
    }

    if( rate > MAX_EGGRESSLINK_RATE )
    {
        LOG_INFO((logInfoBuf,": rate:%d > MAX_EGGRESSLINK_RATE(%d)\n",rate,MAX_EGGRESSLINK_RATE))
        rate = DEFAULT_EGGRESSLINK_RATE;
    }

    schedulerEggressLinkRateInMBits = rate;
    LOG_INFO((logInfoBuf,": schedulerEggressLinkRateInMBits:%d MBits/sec\n",schedulerEggressLinkRateInMBits))
    return;
}/*setEggressLinkRate*/

/********************************/
/* calculateQueueUsage */
/********************************/
static unsigned int calculateQueueUsage(unsigned int currentSize, unsigned int size)
{
    return currentSize/(size/100);
}

/********************************/
/* setSchedulerDequeueStats */
/********************************/
static void setSchedulerDequeueStats(struct sk_buff *skb, unsigned short qNumber)
{
    struct timespec     currentTime;
    struct timespec     captureTime;
    struct timespec     delay;

    /*increment dequeue counter stat*/
    outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].dequeued++;
    /*update queue usage stat*/
    outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].qCurrentSize= schedulerCb.queue[qNumber].currentSize;
    outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].qUsage= calculateQueueUsage(schedulerCb.queue[qNumber].currentSize,schedulerCb.queue[qNumber].size);
    /*update delay related stats*/
    currentTime =  current_kernel_time(); /* this function may return bad-grained result!*/
    captureTime = getSkbTimeStamp(skb);
    /* if current time is bigger than capture time delay into account */
    /* current time may not be fine grained */
    if( timespec_compare(&currentTime, &captureTime)>=0 )
    {
        /* calculate the delay for the packet to be scheduled. */
        delay = timespec_sub(currentTime,captureTime);
        /* add the delay nsec to total delay nsec*/
        timespec_add_ns(&outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].delayStats.totalQueueDelay,delay.tv_nsec);
        /* add the delay sec to total sec */
        outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].delayStats.totalQueueDelay.tv_sec += delay.tv_sec;
        /* now check for minQueue delay*/
        if( timespec_compare(&delay, &outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].delayStats.minQueueDelay)<0 )
        {
            outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].delayStats.minQueueDelay.tv_sec = delay.tv_sec;
            outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].delayStats.minQueueDelay.tv_nsec = delay.tv_nsec;
        }
        /* now check for maxQueue delay*/
        if( timespec_compare(&delay, &outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].delayStats.maxQueueDelay)>0 )
        {
            outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].delayStats.maxQueueDelay.tv_sec = delay.tv_sec;
            outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].delayStats.maxQueueDelay.tv_nsec = delay.tv_nsec;
        }
        outputQueueModuleCb.stats.ethernetSch.queueStats[qNumber].delayStats.queueDelayProcessed++;
    }
}/*setSchedulerDequeueStats*//*calculateQueueUsage*/

/********************************/
/* enqueueSkbToPriorityQueue */
/********************************/
static int enqueueSkbToPriorityQueue(struct sk_buff *skb,unsigned char priority)
{
    /* Do the enqueueing! */
    if(ethernetSchedulerThread_running == 0)
    {
        /*update the necessary statistics.*/
        outputQueueModuleCb.stats.ethernetSch.queueStats[priority].notQueued++;
        kfree_skb(skb);
        return -1;
    }
    /*insert the ethernet packet into the appropriate prioritized queue*/
    if( (schedulerCb.queue[priority].currentSize + skb->len) <= schedulerCb.queue[priority].size )
    {
        skb_queue_tail(&schedulerCb.queue[priority].qHead, skb);
        schedulerCb.queue[priority].currentSize+=skb->len;
        /*update the necessary statistics.*/
        outputQueueModuleCb.stats.ethernetSch.queueStats[priority].queued++;
        outputQueueModuleCb.stats.ethernetSch.queueStats[priority].qCurrentSize = schedulerCb.queue[priority].currentSize;
        outputQueueModuleCb.stats.ethernetSch.queueStats[priority].qUsage = calculateQueueUsage(schedulerCb.queue[priority].currentSize,schedulerCb.queue[priority].size);
        return 1;
    }
    else
    {
        /*update the necessary statistics.*/
        outputQueueModuleCb.stats.ethernetSch.queueStats[priority].notQueued++;
        outputQueueModuleCb.stats.ethernetSch.queueStats[priority].qOverflowBytes+=skb->len;
        kfree_skb(skb);
        return -1;
    }
}/*enqueueSkbToPriorityQueue*/

/********************************/
/* initFifo */
/********************************/
static void initFifo(void)
{
    LOG_INFO((logInfoBuf,":\n"))
    /*this function fills in queue pointer for FIFO*/
    fifoCb.queue = &schedulerCb.queue[DEFAULT_FIFO_QUEUE].qHead;
}/*initFifo*/

/********************************/
/* fifoSchedulerEnqueue */
/********************************/
static int fifoSchedulerEnqueue(struct sk_buff *skb)
{
    return enqueueSkbToPriorityQueue(skb,DEFAULT_FIFO_QUEUE);
}/*fifoSchedulerEnqueue*/

/********************************/
/* fifoSchedulerDequeue */
/********************************/
static void fifoSchedulerDequeue(void)
{
    struct sk_buff *skb;

    /*sleep until someone wakes up!*/
    /*interruptible_sleep_on(&schedulerCb.waitEthernetSchedulerQueue);*/
    /*go through the FIFO queue to pick messages*/
    if( (skb = skb_dequeue(fifoCb.queue) ) != NULL )
    {
        /* update the current queue size */
        if(schedulerCb.queue[DEFAULT_FIFO_QUEUE].currentSize > skb->len)
        {
            schedulerCb.queue[DEFAULT_FIFO_QUEUE].currentSize-=skb->len;
        }
        else
        {
            /*LOG_INFO((logInfoBuf,"currentSize(%d) < skb->len(%d) \n",(unsigned int)schedulerCb.queue[DEFAULT_FIFO_QUEUE].currentSize,skb->len))*/
            schedulerCb.queue[DEFAULT_FIFO_QUEUE].currentSize = 0;
        }
        /* send the ethernet packet out */
        ethernetSchedulerThreadHandler_MSG_ETHPACK(skb,DEFAULT_FIFO_QUEUE);
        outputQueueModuleCb.stats.ethernetSch.processed++;
    }
}/*fifoSchedulerDequeue*/

/********************************/
/* initRoundRobin */
/********************************/
static void initRoundRobin(void)
{
    unsigned short i;

    LOG_INFO((logInfoBuf,":\n"))
    /*this function fills in an array of queue pointers according to the priorities of each ethernet*/
    for(i=0; i<ROUNDROBIN_SCHEDULERQUEUE_LEN;i++)
    {
        roundRobinCb.queue[i] = &schedulerCb.queue[i].qHead;
        LOG_INFO((logInfoBuf,"ROUND ROBIN: queue[%d] = 0x%08x prio:%d\n",i,(unsigned int)roundRobinCb.queue[i],i))
    }
}/*initRoundRobin*/

/********************************/
/* roundRobinSchedulerEnqueue */
/********************************/
static int roundRobinSchedulerEnqueue(struct sk_buff *skb)
{
    unsigned char priority;

    /* Do the enqueueing! */
    /*learn the priority of the packet*/
    priority = getSkbPriority(skb);
    /*insert the ethernet packet into the appropriate prioritized queue*/
    return enqueueSkbToPriorityQueue(skb,priority);
}/*roundRobinSchedulerEnqueue*/

/********************************/
/* roundRobinSchedulerDequeue */
/********************************/
static void roundRobinSchedulerDequeue(void)
{
    struct sk_buff *skb;
    unsigned short i;

    /*sleep until someone wakes up!*/
    /*interruptible_sleep_on(&schedulerCb.waitEthernetSchedulerQueue);*/
    /*go through the weighted round robin queue to pick messages from differen ethernet queues*/
    for(i=0; i<ROUNDROBIN_SCHEDULERQUEUE_LEN; i++)
    {
        if( (skb = skb_dequeue(roundRobinCb.queue[i]) ) != NULL )
        {
            /* update the current queue size */
            if(schedulerCb.queue[i].currentSize > skb->len)
            {
                schedulerCb.queue[i].currentSize-=skb->len;
            }
            else
            {
                /*LOG_INFO((logInfoBuf,"currentSize(%d) < skb->len(%d) \n",(unsigned int)schedulerCb.queue[i].currentSize,skb->len))*/
                schedulerCb.queue[i].currentSize = 0;
            }
            /* send the ethernet packet out */
            ethernetSchedulerThreadHandler_MSG_ETHPACK(skb,i);
            outputQueueModuleCb.stats.ethernetSch.processed++;
        }
    }
}/*roundRobinSchedulerDequeue*/

/********************************/
/* initWeightedRoundRobin */
/********************************/
static void initWeightedRoundRobin(void)
{
    unsigned short i;
    unsigned short leastPrior;
    unsigned short count;

    LOG_INFO((logInfoBuf,":\n"))
    /*this function fills in an array of queue pointers according to the priorities of each ethernet*/
    leastPrior = 0;
    count = NUM_OF_ETHERNET_PRIORITY_CLASSES-leastPrior;
    for(i=0; i<WEIGHTED_ROUNDROBIN_SCHEDULERQUEUE_LEN;i++)
    {
        count--;
        weightedRoundRobinCb.queue[i] = &schedulerCb.queue[count].qHead;
        LOG_INFO((logInfoBuf,"WEIGHTED ROUND ROBIN: queue[%d] = 0x%08x prio:%d\n",i,(unsigned int)weightedRoundRobinCb.queue[i],count))
        if(count == leastPrior)
        {
            leastPrior++;
            count = NUM_OF_ETHERNET_PRIORITY_CLASSES;
        }
    }
}/*initWeightedRoundRobin*/

/********************************/
/* weightedRoundRobinSchedulerEnqueue */
/********************************/
static int weightedRoundRobinSchedulerEnqueue(struct sk_buff *skb)
{
    unsigned char priority;

    /* Do the enqueueing! */
    /*learn the priority of the packet*/
    priority = getSkbPriority(skb);
    /*insert the ethernet packet into the appropriate prioritized queue*/
    return enqueueSkbToPriorityQueue(skb,priority);
}/*weightedRoundRobinSchedulerEnqueue*/

/********************************/
/* weightedRoundRobinSchedulerDequeue */
/********************************/
static void weightedRoundRobinSchedulerDequeue(void)
{
    struct sk_buff *skb;
    unsigned short i;
    unsigned char priority;

    /*sleep until someone wakes up!*/
    /*interruptible_sleep_on(&schedulerCb.waitEthernetSchedulerQueue);*/
    /*go through the weighted round robin queue to pick messages from differen ethernet queues*/
    for(i=0; i<WEIGHTED_ROUNDROBIN_SCHEDULERQUEUE_LEN; i++)
    {
        if( (skb = skb_dequeue(weightedRoundRobinCb.queue[i]) ) != NULL )
        {
            /*learn the priority of the packet*/
            priority = getSkbPriority(skb);
            /* update the current queue size */
            if(schedulerCb.queue[priority].currentSize > skb->len)
            {
                schedulerCb.queue[priority].currentSize-=skb->len;
            }
            else
            {
                /*LOG_INFO((logInfoBuf,"currentSize(%d) < skb->len(%d) \n",(unsigned int)schedulerCb.queue[priority].currentSize,skb->len))*/
                schedulerCb.queue[priority].currentSize = 0;
            }
            /* send the ethernet packet out */
            ethernetSchedulerThreadHandler_MSG_ETHPACK(skb,priority);
            outputQueueModuleCb.stats.ethernetSch.processed++;
        }
    }
}/*weightedRoundRobinSchedulerDequeue*/

/********************************/
/* initDeficitRoundRobin */
/********************************/
static void initDeficitRoundRobin(void)
{
    unsigned short i;

    LOG_INFO((logInfoBuf,":\n"))
    /*this function fills in an array of queue pointers according to the priorities of each ethernet*/
    for(i=0; i<DEFICIT_ROUNDROBIN_NUMBEROFFLOWS;i++)
    {
        deficitRoundRobinCb.flow[i].queue = &schedulerCb.queue[i].qHead;
        deficitRoundRobinCb.flow[i].credit = 0/*(i+1)*DEFICIT_ROUNDROBIN_BASECREDIT*/;
        LOG_INFO((logInfoBuf,"DEFICIT ROUND ROBIN: queue[%d] = 0x%08x prio:%d\n",i,(unsigned int)deficitRoundRobinCb.flow[i].queue,i))
    }
}/*initDeficitRoundRobin*/


/********************************/
/* deficitRoundRobinSchedulerEnqueue */
/********************************/
static int deficitRoundRobinSchedulerEnqueue(struct sk_buff *skb)
{
    unsigned char priority;

    /* Do the enqueueing! */
    /*learn the priority of the packet*/
    priority = getSkbPriority(skb);
    /*insert the ethernet packet into the appropriate prioritized queue*/
    return enqueueSkbToPriorityQueue(skb,priority);
}/*deficitRoundRobinSchedulerEnqueue*/

/********************************/
/* deficitRoundRobinSchedulerDequeue */
/********************************/
static void deficitRoundRobinSchedulerDequeue(void)
{
    struct sk_buff *skb;
    unsigned short skbDataLen;
    unsigned short i;
    unsigned char priority;

    /*sleep until someone wakes up!*/
    /*interruptible_sleep_on(&schedulerCb.waitEthernetSchedulerQueue);*/
    /*go through the weighted round robin queue to pick messages from differen ethernet queues*/
    for(i=0; i<DEFICIT_ROUNDROBIN_NUMBEROFFLOWS; i++)
    {
        /*get the pointer to the first skb on the list but don't remove it'*/
        skb = skb_peek(deficitRoundRobinCb.flow[i].queue);
        if(skb != NULL)
        {
            /*first increase the credit*/
            deficitRoundRobinCb.flow[i].credit += (i+1)*DEFICIT_ROUNDROBIN_BASECREDIT;
            while(skb!=NULL)
            {
                /*get skb data length!*/
                skbDataLen = skb->len;
                /*if we have enough credits to send the data*/
                if(skbDataLen<=deficitRoundRobinCb.flow[i].credit)
                {
                    /*remove the skb from the queue and process it*/
                    skb = skb_dequeue(deficitRoundRobinCb.flow[i].queue);
                    /*decrease the credit by skb length!*/
                    deficitRoundRobinCb.flow[i].credit -= skbDataLen;
                    /*go on*/
                    /*learn the priority of the packet*/
                    priority = getSkbPriority(skb);
                    /* update the current queue size */
                    if(schedulerCb.queue[priority].currentSize > skb->len)
                    {
                        schedulerCb.queue[priority].currentSize-=skb->len;
                    }
                    else
                    {
                        /*LOG_INFO((logInfoBuf,"currentSize(%d) < skb->len(%d) \n",(unsigned int)schedulerCb.queue[priority].currentSize,skb->len))*/
                        schedulerCb.queue[priority].currentSize = 0;
                    }
                    /* send the ethernet packet out */
                    ethernetSchedulerThreadHandler_MSG_ETHPACK(skb,priority);
                    outputQueueModuleCb.stats.ethernetSch.processed++;
                }
                else
                {
                    /*credits is not enough for another xmission. Break the while loop.*/
                    break;
                }
                /*we'll look if another packet is in the queue and eligible to send.*/
                skb = skb_peek(deficitRoundRobinCb.flow[i].queue);
            }
        }
        else
        {
            /*nothing in the queue!*/
            /*set credit to zero*/
            deficitRoundRobinCb.flow[i].credit = 0;
        }
    }
}/*deficitRoundRobinSchedulerDequeue*/

/********************************/
/* initWf2q */
/********************************/
static void initWf2q(void)
{
    unsigned short i;

    LOG_INFO((logInfoBuf,":\n"))
    /*this function fills in an array of queue pointers according to the priorities of each ethernet*/
    for(i=0; i<WF2Q_NUMBEROFFLOWS;i++)
    {
        wf2qCb.flow[i].queue = &schedulerCb.queue[i].qHead;
        wf2qCb.flow[i].prio = i;
        /* Let weight be something different than 0 */
        wf2qCb.flow[i].weight = i+1;
        wf2qCb.flow[i].startTime = 0.0;
        wf2qCb.flow[i].finishTime = 0.0;
        LOG_INFO((logInfoBuf,"WF2Q: queue[%d] = 0x%08x weight:%d startTime:%d finishTime:%d\n",i,
                                    (unsigned int)wf2qCb.flow[i].queue,
                                    wf2qCb.flow[i].weight,
                                    wf2qCb.flow[i].startTime,
                                    wf2qCb.flow[i].finishTime))
    }
    /* set the virtual time to 0 */
    wf2qCb.virtualTime = 0;

}/*initWf2q*/

/********************************/
/* wf2qSchedulerEnqueue */
/********************************/
static int wf2qSchedulerEnqueue(struct sk_buff *skb)
{
    unsigned short i;
    unsigned int minStartTime;
    unsigned char priority;

    /* Do the enqueueing! */
    /*learn the priority of the packet*/
    priority = getSkbPriority(skb);

    /* is queue empty?*/
    if( 0 == skb_queue_len(wf2qCb.flow[priority].queue) )
    {
        wf2qCb.flow[priority].startTime = MAX( wf2qCb.virtualTime, wf2qCb.flow[priority].finishTime  );
        wf2qCb.flow[priority].finishTime = wf2qCb.flow[priority].startTime + (skb->len/wf2qCb.flow[priority].weight);
    }

    /* The virtual time needs to be updated */
    /* update the virtual clock */
    minStartTime = wf2qCb.flow[priority].startTime;
    for(i=0; i<WF2Q_NUMBEROFFLOWS; i++)
    {
        /* look if a packet exists in the flow, if not continue to the other flow */
        if ( 0 != skb_queue_len(wf2qCb.flow[i].queue) )
        {
            if( wf2qCb.flow[i].startTime < minStartTime )
            {
                minStartTime = wf2qCb.flow[i].startTime;
            }
        }
    }
    wf2qCb.virtualTime = MAX (minStartTime, wf2qCb.virtualTime );

    /*insert the ethernet packet into the appropriate prioritized queue*/
    return enqueueSkbToPriorityQueue(skb,priority);
}/*wf2qSchedulerEnqueue*/

/********************************/
/* wf2qSchedulerDequeue */
/********************************/
static void wf2qSchedulerDequeue(void)
{
    struct sk_buff *currentSkb;
    struct sk_buff *nextSkb;
    unsigned short i;
    unsigned char priority;
    unsigned int ethPacketLen;
    unsigned int minFinishTime;
    unsigned int minStartTime;
    int selectedFlow;
    unsigned int weightSum;

    /*sleep until someone wakes up!*/
    /*interruptible_sleep_on(&schedulerCb.waitEthernetSchedulerQueue);*/
    /* go through the WF2Q flows to pick messages from different queues */
    /* the flow with the smallest finish time will be used for transmission */
    minFinishTime = 0xFFFFFFFF;
    selectedFlow = -1;
    for(i=0; i<WF2Q_NUMBEROFFLOWS; i++)
    {
        /* look if a packet exists in the flow, if not continue to the other flow */
        if ( 0 == skb_queue_len(wf2qCb.flow[i].queue) )
        {
            continue;
        }

        /* if start time for the flow is less than the virtual time */
        if( wf2qCb.flow[i].startTime <= wf2qCb.virtualTime )
        {
            /* if finish time for the current flow is smaller than the other flows,
                take it as a candidate for transmission */
            if( wf2qCb.flow[i].finishTime < minFinishTime )
            {
                selectedFlow = i;
                minFinishTime = wf2qCb.flow[i].finishTime;
            }
        }
    }

    /* do we have a selected flow? */
    /* if not do nothing right now! */
    if( selectedFlow == -1 )
    {
        return;
    }

    /* until now we have not grabbed any packet from any queue! */
    /* the selected flow will be the source for the next transmission */
    /* get the skb out of the queue */
    currentSkb = skb_dequeue(wf2qCb.flow[selectedFlow].queue);
    ethPacketLen =  currentSkb->len;

    /* is there another packet in the sama flow queue? Check it!*/
    nextSkb = skb_peek(wf2qCb.flow[selectedFlow].queue);
    /* if there is another packet set the start and finish time accordingly */
    if( NULL != nextSkb )
    {
        /* start time now is the finish time */
        wf2qCb.flow[selectedFlow].startTime = wf2qCb.flow[selectedFlow].finishTime;
        /* calculate the finish time */
        wf2qCb.flow[selectedFlow].finishTime += (nextSkb->len / wf2qCb.flow[selectedFlow].weight);
    }
    /* The virtual time needs to be updated */
    /* update the virtual clock */
    minStartTime = 0xFFFFFFFF;
    weightSum = 0;
    for(i=0; i<WF2Q_NUMBEROFFLOWS; i++)
    {
        weightSum += wf2qCb.flow[i].weight;
        /* look if a packet exists in the flow, if not continue to the other flow */
        if ( 0 != skb_queue_len(wf2qCb.flow[i].queue) )
        {
            if( wf2qCb.flow[i].startTime < minStartTime )
            {
                minStartTime = wf2qCb.flow[i].startTime;
            }
        }
    }
    wf2qCb.virtualTime = MAX (minStartTime, ( wf2qCb.virtualTime + (ethPacketLen/weightSum) ) );


    /*learn the priority of the packet*/
    priority = getSkbPriority(currentSkb);
    /* update the current queue size */
    if(schedulerCb.queue[priority].currentSize > currentSkb->len)
    {
        schedulerCb.queue[priority].currentSize-=currentSkb->len;
    }
    else
    {
        /*LOG_INFO((logInfoBuf,"currentSize(%d) < currentSkb->len(%d) \n",(unsigned int)schedulerCb.queue[priority].currentSize,skb->len))*/
        schedulerCb.queue[priority].currentSize = 0;
    }
    /* send the ethernet packet out */
    ethernetSchedulerThreadHandler_MSG_ETHPACK(currentSkb,priority);
    outputQueueModuleCb.stats.ethernetSch.processed++;
}/*wf2qSchedulerDequeue*/

/********************************/
/* initDTable */
/********************************/
static void initDTable(void)
{
    unsigned short i;
    unsigned short leastPrior;
    unsigned short count;

    LOG_INFO((logInfoBuf,":\n"))
    /*this function fills in an array of queue pointers according to the priorities of each ethernet flow*/
    for(i=0; i<DEFICIT_TABLE_NUMBEROFFLOWS;i++)
    {
        dTableCb.flow[i].queue = &schedulerCb.queue[i].qHead;
        dTableCb.flow[i].prio = i;
        LOG_INFO((logInfoBuf,"DEFICIT TABLE: flow[%d](0x%08x) = 0x%08x prio:%d\n",i,
                                        (unsigned int)&dTableCb.flow[i],(unsigned int)dTableCb.flow[i].queue,dTableCb.flow[i].prio))
    }

    /*now initialize the deficit table*/
    leastPrior = 0;
    count = DEFICIT_TABLE_NUMBEROFFLOWS-leastPrior;
    for(i=0; i<DEFICIT_TABLE_SIZE;i++)
    {
        count--;
        dTableCb.table[i].correspondingFlow = &dTableCb.flow[count];
        LOG_INFO((logInfoBuf,"DEFICIT TABLE[%d].correspondingFlow = 0x%08x\n",i,(unsigned int)dTableCb.table[i].correspondingFlow))
        if(count == leastPrior)
        {
            leastPrior++;
            count = NUM_OF_ETHERNET_PRIORITY_CLASSES;
        }
    }
}/*initDTable*/

/********************************/
/* dTableSchedulerEnqueue */
/********************************/
static int dTableSchedulerEnqueue(struct sk_buff *skb)
{
    unsigned char priority;

    /* Do the enqueueing! */
    /*learn the priority of the packet*/
    priority = getSkbPriority(skb);
    /*insert the ethernet packet into the appropriate prioritized queue*/
    return enqueueSkbToPriorityQueue(skb,priority);
}/*dTableSchedulerEnqueue*/

/********************************/
/* dTableSchedulerDequeue */
/********************************/
static void dTableSchedulerDequeue(void)
{
    struct sk_buff *skb;
    unsigned short skbDataLen;
    unsigned short i;
    unsigned char priority;

    /*sleep until someone wakes up!*/
    /*interruptible_sleep_on(&schedulerCb.waitEthernetSchedulerQueue);*/
    /*go through the weighted round robin queue to pick messages from differen ethernet queues*/
    for(i=0; i<DEFICIT_TABLE_SIZE; i++)
    {
        /*get the pointer to the first skb on the list but don't remove it'*/
        skb = skb_peek(dTableCb.table[i].correspondingFlow->queue);
        if(skb != NULL)
        {
            /*first increase the credit*/
            dTableCb.table[i].correspondingFlow->credit += DTABLE_BASECREDIT;
            while(skb!=NULL)
            {
                /*get skb data length!*/
                skbDataLen = skb->len;
                /*if we have enough credits to send the data*/
                if(skbDataLen<=dTableCb.table[i].correspondingFlow->credit)
                {
                    /*remove the skb from the queue and process it*/
                    skb = skb_dequeue(dTableCb.table[i].correspondingFlow->queue);
                    /*decrease the credit by skb length!*/
                    dTableCb.table[i].correspondingFlow->credit -= skbDataLen;
                    /*go on*/
                    /*learn the priority of the packet*/
                    priority = getSkbPriority(skb);
                    /* update the current queue size */
                    if(schedulerCb.queue[priority].currentSize > skb->len)
                    {
                        schedulerCb.queue[priority].currentSize-=skb->len;
                    }
                    else
                    {
                        /*LOG_INFO((logInfoBuf,"currentSize(%d) < skb->len(%d) \n",(unsigned int)schedulerCb.queue[priority].currentSize,skb->len))*/
                        schedulerCb.queue[priority].currentSize = 0;
                    }
                    /* send the ethernet packet out */
                    ethernetSchedulerThreadHandler_MSG_ETHPACK(skb,priority);
                    outputQueueModuleCb.stats.ethernetSch.processed++;
                }
                else
                {
                    /*credits is not enough for another xmission. Break the while loop.*/
                    break;
                }
                /*we'll look if another packet is in the queue and eligible to send.*/
                skb = skb_peek(dTableCb.table[i].correspondingFlow->queue);
            }
        }
        else
        {
            /*nothing in the queue!*/
            /*set credit to zero*/
            dTableCb.table[i].correspondingFlow->credit = 0;
        }
    }
}/*dTableSchedulerDequeue*/
