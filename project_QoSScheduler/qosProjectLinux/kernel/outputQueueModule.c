/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* outputQueueModule.c */
/********************************************************************************/

/********************************************************************************/
/* INCLUDES */
/********************************************************************************/
#define ALLOCATE
#include "outputQueueModule.x"

/********************************************************************************/
/* DEFINES */
/********************************************************************************/

/********************************************************************************/
/* FUNCTION PROTOTYPES */
/********************************************************************************/
static void printSystemRelatedInfo(void);
void initStartWorkingThreads(void);
void stopDestroyWorkingThreads(void);
static int __init outputQueueModuleInit(void);
static void __exit outputQueueModuleCleanup(void);

/********************************************************************************/
/* GLOBALS */
/********************************************************************************/
/*local configuration*/
T_OUTPUTQUEUEMODULE_CONTROL_BLOCK	outputQueueModuleCb;
/********************************************************************************/
/* EXTERNS */
/********************************************************************************/

/********************************************************************************/
/* FUNCTIONS */
/********************************************************************************/

/********************************/
/* printSystemRelatedInfo */
/********************************/
static void printSystemRelatedInfo(void)
{
    ktime_t t;

    LOG_INFO((logInfoBuf,"\n"))
    LOG_INFO((logInfoBuf,": sizeof(u64):%d\n",sizeof(u64)))
    LOG_INFO((logInfoBuf,": sizeof(s64):%d\n",sizeof(s64)))
    LOG_INFO((logInfoBuf,": sizeof(int):%d\n",sizeof(int)))
    LOG_INFO((logInfoBuf,": sizeof(unsigned int):%d\n",sizeof(unsigned int)))
    LOG_INFO((logInfoBuf,": sizeof(short int):%d\n",sizeof(short int)))
    LOG_INFO((logInfoBuf,": sizeof(unsigned short int):%d\n",sizeof(unsigned short int)))
    LOG_INFO((logInfoBuf,": BITS_PER_LONG:%d\n",sizeof(BITS_PER_LONG)))
    LOG_INFO((logInfoBuf,": sizeof(ktime_t):%d\n",sizeof(t)))
    LOG_INFO((logInfoBuf,": sizeof(ktime_t):%d\n",sizeof(t.tv64)))

}/*printSystemRelatedInfo*/

/********************************/
/* initStartWorkingThreads */
/********************************/
void initStartWorkingThreads(void)
{
    LOG_INFO((logInfoBuf,"\n"))
    /*init all statistics...*/
    initStats();
    /*init ethernet sender thread*/
    initEthernetSenderThread();
    /* init ethernet scheduler thread*/
    initEthernetSchedulerThread();
    /*init ethernet receiver thread*/
    initEthernetReceiverThread();
    /*send indication to user space*/
    netlinkSendCommand(NL_MSGTYPE_MODULESTARTED);
}/*initStartWorkingThreads*/

/********************************/
/* stopDestroyWorkingThreads */
/********************************/
void stopDestroyWorkingThreads(void)
{
    LOG_INFO((logInfoBuf,"\n"))
    /*print all statistics...*/
    printStats();
    /* kill ethernet receiver thread */
    killEthernetReceiverThread();
    /* kill ethernet scheduler thread*/
    killEthernetSchedulerThread();
    /* kill ethernet sender thread */
    killEthernetSenderThread();
    /*send indication to user space*/
    netlinkSendCommand(NL_MSGTYPE_MODULESTOPPED);
}/*stopDestroyWorkingThreads*/

/********************************/
/* outputQueueModuleInit */
/********************************/
static int __init outputQueueModuleInit(void)
{
    LOG_INFO((logInfoBuf,"\n"))
    printSystemRelatedInfo();
    #if 0
    /*enable skb timeStamping...*/
    LOG_INFO((logInfoBuf,"net_enable_timestamp.\n"))
    net_enable_timestamp();
    #endif
    /*init netlink thread for userspace communication.*/
    initNlThread();

    LOG_INFO((logInfoBuf,"finished.\n"))
    return 0;
}/*outputQueueModuleInit*/

/********************************/
/* outputQueueModuleCleanup */
/********************************/
static void __exit outputQueueModuleCleanup(void)
{
    LOG_INFO((logInfoBuf,"\n"))

    /* kill all working threads */
    stopDestroyWorkingThreads();
    /* kill netlink thread */
    killNlThread();

    LOG_INFO((logInfoBuf,"finished.\n"))
}/*outputQueueModuleCleanup*/

/* Module stuff */
module_init(outputQueueModuleInit);
module_exit(outputQueueModuleCleanup);

MODULE_AUTHOR("AHMET EMRAH DEMIRCAN (EE5410:1123413)");
MODULE_DESCRIPTION("EE5410 TERM PROJECT");
MODULE_LICENSE("GPL");
