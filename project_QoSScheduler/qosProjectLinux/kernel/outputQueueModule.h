/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* outputQueueModule.h */
/********************************************************************************/
#ifndef outputQueueModule_h
#define outputQueueModule_h
/********************************************************************************/
/* INCLUDES */
/********************************************************************************/
#include <linux/kernel.h>	/* KERN_ALERT */
#include <linux/module.h>	/* all modules */
#include <linux/init.h>		/* __init and __exit macros? */
#include <linux/etherdevice.h>
#include <linux/netdevice.h>	/* struct packet_type */
#include <linux/if_ether.h>	/* struct ethhdr */
#include <net/ip.h>
#include <linux/ip.h>		/* struct iphdr */
#include <linux/socket.h>
#include <linux/mroute.h>
#include <linux/in.h>
#include <linux/wait.h>		/*interruptible sleep icin...*/

#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>

#include <linux/kthread.h>
//#include <linux/smp_lock.h> /*lock UNLOCK_KERNEL icin ekledim...*/
#include <linux/sched/signal.h>/*kill_proc icin ekledim...*/

#include <linux/errno.h>
#include <linux/types.h>

#include <linux/ktime.h> /*sbuff icerisinde ktime_t tstamp var ...*/

#include <linux/timer.h>
#include <linux/string.h>
#include <linux/hrtimer.h> /*high resolution timer icin ekledim...*/
#include <config/x86/msr.h>

/********************************************************************************/
/* DEFINES */
/********************************************************************************/
#define MODULE_NAME "module_5410"

typedef struct kthread_t
{
        struct task_struct  *thread;
        struct hrtimer      wakeUpHrTimer;
        ktime_t             wakeUpAbsKtime;
        int running;

}T_KTHREAD;

typedef struct
{
    unsigned short  src; /* ipc mesajinin kaynagidir */
    unsigned short  dst; /* ipc mesajinin hedefidir */
    unsigned int    ipcTag; /* ipc mesajini tanimlayan etikettir */
    unsigned int    payloadLen; /* ipc mesaji yuk uzunlugudur */
} __attribute__((packed)) T_IPC_MSGHEADER;
#define T_IPC_MSGHEADER_LEN sizeof(T_IPC_MSGHEADER)
#define MAX_IPCMSG_PAYLEN   1000
#define MAX_IPCMSG_LEN   (T_IPC_MSGHEADER_LEN + MAX_IPCMSG_PAYLEN)

#define LOG_PAYLOAD_LEN 1000
#ifdef ALLOCATE
char logInfoBuf[LOG_PAYLOAD_LEN];
char tempLogInfoBuf[LOG_PAYLOAD_LEN];
#undef ALLOCATE
#else
extern char logInfoBuf[LOG_PAYLOAD_LEN];
extern char tempLogInfoBuf[LOG_PAYLOAD_LEN];
#endif
extern void netlinkLogMessage(char* str);
#define LOG_INFO(_args)								\
{										\
	sprintf(tempLogInfoBuf, "[%s:%s] ", MODULE_NAME, __FUNCTION__);		\
	sprintf _args;								\
	sprintf(&tempLogInfoBuf[strlen(tempLogInfoBuf)],logInfoBuf);		\
        printk(tempLogInfoBuf);                                                 \
        netlinkLogMessage(tempLogInfoBuf);                                                    \
}

/*all related includes here...*/
#include "ethernet.h"
#include "scheduler.h"
#include "stats.h"
#include "skbInfo.h"
#include "netlink.h"

#define SEC_TO_MSEC(x)	((x)*1000)
#define SEC_TO_USEC(x)	((x)*1000000)
#define SEC_TO_NSEC(x)	((x)*1000000000)
#define MSEC_TO_USEC(x)	((x)*1000)
#define MSEC_TO_NSEC(x)	((x)*1000000)
#define USEC_TO_NSEC(x)	((x)*1000)
#define NSEC_TO_MSEC(x)	((x)/1000000)
#define USEC_TO_MSEC(x) ((x)/1000)

#define THREAD_YIELD		yield();		/*sched();*/

#define WAKEUPTIMER_NSEC                100000

/* configuration information held here... */
typedef struct
{

}T_CONFIG;

/* Main control block including all runtime information needed */
typedef struct
{
    T_CONFIG            config; /*configuration data*/
    T_STATS             stats;/*all statistics...*/
}T_OUTPUTQUEUEMODULE_CONTROL_BLOCK;

#endif
