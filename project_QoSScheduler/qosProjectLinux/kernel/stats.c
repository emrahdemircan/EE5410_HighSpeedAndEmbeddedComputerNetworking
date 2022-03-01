/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* stats.c */
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
void initStats(void);
void printStats(void);
/********************************************************************************/
/* GLOBALS */
/********************************************************************************/

/********************************************************************************/
/* EXTERNS */
/********************************************************************************/

/********************************************************************************/
/* FUNCTIONS */
/********************************************************************************/

/********************************/
/* initStats */
/********************************/ 
void initStats(void)
{
	LOG_INFO((logInfoBuf,"\n"))
	memset(&outputQueueModuleCb.stats,0,sizeof(T_STATS));
}/*initStats*/

/********************************/
/* printStats */
/********************************/ 
void printStats(void)
{
        unsigned short i;
        LOG_INFO((logInfoBuf,"***********************************************************************************\n"))
	/*ethernetRx stats*/	
        LOG_INFO((logInfoBuf,"ETHERNET RX  -> ethernetPacketIn:%u\n",outputQueueModuleCb.stats.ethernetRx.ethernetPacketIn))
        LOG_INFO((logInfoBuf,"ETHERNET RX  -> queued:%u\n",outputQueueModuleCb.stats.ethernetRx.queued))
        LOG_INFO((logInfoBuf,"ETHERNET RX  -> notQueued:%u\n",outputQueueModuleCb.stats.ethernetRx.notQueued))
        LOG_INFO((logInfoBuf,"ETHERNET RX  -> dequeued:%u\n",outputQueueModuleCb.stats.ethernetRx.dequeued))
        LOG_INFO((logInfoBuf,"ETHERNET RX  -> processed:%u\n",outputQueueModuleCb.stats.ethernetRx.processed))
        LOG_INFO((logInfoBuf,"ETHERNET RX  -> dataProcessed:%u\n",outputQueueModuleCb.stats.ethernetRx.dataProcessed))
        LOG_INFO((logInfoBuf,"ETHERNET RX  -> ipcProcessed:%u\n",outputQueueModuleCb.stats.ethernetRx.ipcProcessed))
        /*ethernetSch stats*/
        LOG_INFO((logInfoBuf,"ETHERNET SCH -> ethernetPacketIn:%u\n",outputQueueModuleCb.stats.ethernetSch.ethernetPacketIn))
        LOG_INFO((logInfoBuf,"ETHERNET SCH ->\n"))
        for(i=0; i<NUM_OF_ETHERNET_PRIORITY_CLASSES; i++)
        {
            LOG_INFO((logInfoBuf," Prio(%u): Qd:%012u notQd:%012u deQd:%012u currentSize:%012u qUsage:%02u qOFlow:%012u\n",i,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].queued,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].notQueued,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].dequeued,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].qCurrentSize,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].qUsage,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].qOverflowBytes))
            LOG_INFO((logInfoBuf," Prio(%u): QDelayProcessed:%d MinQDelay:%ld.%ld MaxQDelay:%ld.%ld TotQDelay:%ld.%ld \n",i,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].delayStats.queueDelayProcessed,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].delayStats.minQueueDelay.tv_sec,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].delayStats.minQueueDelay.tv_nsec,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].delayStats.maxQueueDelay.tv_sec,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].delayStats.maxQueueDelay.tv_nsec,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].delayStats.totalQueueDelay.tv_sec,
                                                            outputQueueModuleCb.stats.ethernetSch.queueStats[i].delayStats.totalQueueDelay.tv_nsec))
        }
        LOG_INFO((logInfoBuf,"ETHERNET SCH -> processed:%u\n",outputQueueModuleCb.stats.ethernetSch.processed))
        LOG_INFO((logInfoBuf,"ETHERNET SCH -> dataProcessed:%u\n",outputQueueModuleCb.stats.ethernetSch.dataProcessed))
        LOG_INFO((logInfoBuf,"ETHERNET SCH -> sndSucceeded:%u\n",outputQueueModuleCb.stats.ethernetSch.sndSucceeded))
        LOG_INFO((logInfoBuf,"ETHERNET SCH -> sndFailed:%u\n",outputQueueModuleCb.stats.ethernetSch.sndFailed))
        /*ethernetTx stats*/
        LOG_INFO((logInfoBuf,"ETHERNET TX  -> ethernetPacketIn:%u\n",outputQueueModuleCb.stats.ethernetTx.ethernetPacketIn))
        LOG_INFO((logInfoBuf,"ETHERNET TX  -> queued:%u\n",outputQueueModuleCb.stats.ethernetTx.queued))
        LOG_INFO((logInfoBuf,"ETHERNET TX  -> notQueued:%u\n",outputQueueModuleCb.stats.ethernetTx.notQueued))
        LOG_INFO((logInfoBuf,"ETHERNET TX  -> dequeued:%u\n",outputQueueModuleCb.stats.ethernetTx.dequeued))
        LOG_INFO((logInfoBuf,"ETHERNET TX  -> processed:%u\n",outputQueueModuleCb.stats.ethernetTx.processed))
        LOG_INFO((logInfoBuf,"ETHERNET TX  -> dataProcessed:%u\n",outputQueueModuleCb.stats.ethernetTx.dataProcessed))
        LOG_INFO((logInfoBuf,"ETHERNET TX  -> ipcProcessed:%u\n",outputQueueModuleCb.stats.ethernetTx.ipcProcessed))
        LOG_INFO((logInfoBuf,"ETHERNET TX  -> ethernetPacketOut:%u\n",outputQueueModuleCb.stats.ethernetTx.ethernetPacketOut))
        LOG_INFO((logInfoBuf,"ETHERNET TX  -> sndSucceeded:%u\n",outputQueueModuleCb.stats.ethernetTx.sndSucceeded))
        LOG_INFO((logInfoBuf,"ETHERNET TX  -> sndFailed:%u\n",outputQueueModuleCb.stats.ethernetTx.sndFailed))
	/*netlink stats*/
        LOG_INFO((logInfoBuf,"NETLINK      -> queued:%u\n",outputQueueModuleCb.stats.nl.queued))
        LOG_INFO((logInfoBuf,"NETLINK      -> notQueued:%u\n",outputQueueModuleCb.stats.nl.notQueued))
        LOG_INFO((logInfoBuf,"NETLINK      -> dequeued:%u\n",outputQueueModuleCb.stats.nl.dequeued))
        LOG_INFO((logInfoBuf,"NETLINK      -> processed:%u\n",outputQueueModuleCb.stats.nl.processed))
        LOG_INFO((logInfoBuf,"NETLINK      -> ipcProcessed:%u\n",outputQueueModuleCb.stats.nl.ipcProcessed))
        LOG_INFO((logInfoBuf,"NETLINK      -> nlSent:%u\n",outputQueueModuleCb.stats.nl.nlSent))
        LOG_INFO((logInfoBuf,"NETLINK      -> nlRcvd:%u\n",outputQueueModuleCb.stats.nl.nlRcvd))
        LOG_INFO((logInfoBuf,"***********************************************************************************\n"))

}/*printStats*/



