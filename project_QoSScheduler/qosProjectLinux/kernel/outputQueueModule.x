/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* outputQueueModule.x */
/********************************************************************************/

#ifndef outputQueueModule_x
#define outputQueueModule_x
/********************************************************************************/
/* INCLUDES */
/********************************************************************************/
#include "outputQueueModule.h"

/********************************************************************************/
/* DEFINES */
/********************************************************************************/
#define LOCK_KERNEL()
#define UNLOCK_KERNEL()
/********************************************************************************/
/* EXTERNS */
/********************************************************************************/
/*outputQueueModule.c*/
extern T_OUTPUTQUEUEMODULE_CONTROL_BLOCK outputQueueModuleCb;
extern void initStartWorkingThreads(void);
extern void stopDestroyWorkingThreads(void);
/*ethernetReceiver.c*/
extern int initEthernetReceiverThread(void);
extern int killEthernetReceiverThread(void);
extern int tailEthernetReceiverQueue_MSG_IPC(struct sk_buff *skb);
/*ethernetScheduler.c*/
extern int initEthernetSchedulerThread(void);
extern int killEthernetSchedulerThread(void);
extern int tailEthernetSchedulerQueue_MSG_ETHPACK(struct sk_buff *skb);
extern void setSchedulerType(T_SCHEDULER_TYPE_ENUM schedulerType);
extern void setBacklogTime(unsigned int timeInMsecs);
extern void setSchedulerQueueLength(unsigned int lengthInBytes);
extern void setEggressLinkRate(unsigned int rate);
/*ethernetSender.c*/
extern int initEthernetSenderThread(void);
extern int killEthernetSenderThread(void);
extern int tailEthernetSenderQueue_MSG_ETHPACK(struct sk_buff *skb);
extern int tailEthernetSenderQueue_MSG_IPC(struct sk_buff *skb);
/*netlink.c*/
extern int initNlThread(void);
extern int killNlThread(void);
extern void netlinkLogMessage(char* str);
extern void netlinkSendCommand(unsigned short command);
/*stats.c*/
extern void initStats(void);
extern void printStats(void);
#endif
