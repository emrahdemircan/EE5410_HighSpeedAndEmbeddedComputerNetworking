/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* scheduler.h */
/********************************************************************************/

#ifndef scheduler_h
#define scheduler_h
/********************************************************************************/
/* INCLUDES */
/********************************************************************************/

/********************************************************************************/
/* DEFINES */
/********************************************************************************/

#ifdef __KERNEL__
typedef struct
{
    unsigned int size;
    unsigned int currentSize;
    struct sk_buff_head qHead;
} T_SCHEDULER_QUEUE;

typedef struct
{
    T_SCHEDULER_QUEUE   queue[NUM_OF_ETHERNET_PRIORITY_CLASSES];
    wait_queue_head_t   waitEthernetSchedulerQueue;
    int                 waitEthernetSchedulerQueueFlag;
    struct hrtimer      transmitWakeUpHrTimer;
    ktime_t             transmitWakeUpAbsKtime;
    wait_queue_head_t   waitEthernetTransmitQueue;
    int                 waitEthernetTransmitQueueFlag;
} T_SCHEDULER_QUEUE_CB;

typedef int (*T_SCHEDULER_ENQUEUEFNCPTR)(struct sk_buff *skb);
typedef void (*T_SCHEDULER_DEQUEUEFNCPTR)(void);
#endif

typedef enum
{
    FIFO =0,
    ROUND_ROBIN,
    WEIGHTED_ROUND_ROBIN,
    DEFICIT_ROUND_ROBIN,
    WF2Q,
    DTABLE,
    NUM_OF_SCHEDULERS,
} T_SCHEDULER_TYPE_ENUM;

#define DEFAULT_SCHEDULER FIFO

#define MIN_BACKLOGTIME_IN_MSECS        0       /* 0 */
#define MAX_BACKLOGTIME_IN_MSECS        5000    /*5 seconds*/
#define DEFAULT_BACKLOGTIME_IN_MSECS    MIN_BACKLOGTIME_IN_MSECS

#define ONEKILOBYTES                            1000
#define ONEMEGABYTES                            1000000
#define MIN_SCHEDULERQUEUELENGTH_IN_BYTES       ( 10 * ONEKILOBYTES )
#define MAX_SCHEDULERQUEUELENGTH_IN_BYTES       ( 1  * ONEMEGABYTES )
#define DEFAULT_SCHEDULERQUEUELENGTH_IN_BYTES   ( 20 * ONEKILOBYTES )

#define MIN_EGGRESSLINK_RATE        1
#define DEFAULT_EGGRESSLINK_RATE    2
#define MAX_EGGRESSLINK_RATE        10

/*each packet transmission is delayed by this timeout value to simulate xmission delay*/
#define TRANSMIT_WAKEUPTIMER_NSEC                      8000
#define ONEMBIT_ONEBYTE_TRANSMIT_WAKEUPTIMER_NSEC      8000
#define TRANSMISSION_WAIT_UNIT_LENGTH_IN_BYTES         100
#define TRANSMISSION_WAIT_UNIT_LENGTH_IN_BITS          (8*TRANSMISSION_WAIT_UNIT_LENGTH_IN_BYTES)

/* finding a maximum or minimum is also needed */
#define MAX(x,y) ((x)<(y))?(y):(x)
#define MIN(x,y) ((x)>(y))?(y):(x)

/*#ifdef __KERNEL__*/

/*****************************/
/*FIFO*/
/*****************************/
typedef struct
{
    struct sk_buff_head* queue;
} T_FIFO_CB;
#define DEFAULT_FIFO_QUEUE 0

/*****************************/
/*round robin*/
/*****************************/
#define ROUNDROBIN_SCHEDULERQUEUE_LEN               NUM_OF_ETHERNET_PRIORITY_CLASSES
typedef struct
{
    struct sk_buff_head* queue[ROUNDROBIN_SCHEDULERQUEUE_LEN];
} T_ROUNDROBIN_CB;

/*****************************/
/*weighted round robin*/
/*****************************/
#define WEIGHTED_ROUNDROBIN_SCHEDULERQUEUE_LEN          (NUM_OF_ETHERNET_PRIORITY_CLASSES*(NUM_OF_ETHERNET_PRIORITY_CLASSES+1))/2
typedef struct
{
    struct sk_buff_head* queue[WEIGHTED_ROUNDROBIN_SCHEDULERQUEUE_LEN];
} T_WEIGHTED_ROUNDROBIN_CB;

/*****************************/
/*deficit round robin*/
/*****************************/
#define DEFICIT_ROUNDROBIN_NUMBEROFFLOWS                NUM_OF_ETHERNET_PRIORITY_CLASSES
typedef struct
{
    struct sk_buff_head* queue;
    unsigned short credit;
} T_DEFICIT_ROUNDROBIN_FLOW;
typedef struct
{
    T_DEFICIT_ROUNDROBIN_FLOW flow[DEFICIT_ROUNDROBIN_NUMBEROFFLOWS];
} T_DEFICIT_ROUNDROBIN_CB;
#define DEFICIT_ROUNDROBIN_BASECREDIT 50

/*****************************/
/* WF2Q */
/*****************************/
#define WF2Q_NUMBEROFFLOWS                              NUM_OF_ETHERNET_PRIORITY_CLASSES
typedef struct
{
    struct sk_buff_head* queue;
    unsigned int prio;
    unsigned int weight;
    unsigned int startTime;
    unsigned int finishTime;
} T_WF2Q_FLOW;
typedef struct
{
    T_WF2Q_FLOW flow[WF2Q_NUMBEROFFLOWS];
    unsigned int virtualTime;
} T_WF2Q_CB;

/*****************************/
/*deficit table*/
/*****************************/
#define DEFICIT_TABLE_NUMBEROFFLOWS                     NUM_OF_ETHERNET_PRIORITY_CLASSES
#define DEFICIT_TABLE_SIZE                              (DEFICIT_TABLE_NUMBEROFFLOWS*(DEFICIT_TABLE_NUMBEROFFLOWS+1))/2
typedef struct
{
    struct sk_buff_head* queue;
    unsigned short credit;
    unsigned int prio;
} T_DEFICIT_TABLE_FLOW;

typedef struct
{
    T_DEFICIT_TABLE_FLOW*   correspondingFlow;
} T_DEFICIT_TABLE_ELEMENT;

typedef struct
{
    T_DEFICIT_TABLE_FLOW flow[DEFICIT_TABLE_NUMBEROFFLOWS];
    T_DEFICIT_TABLE_ELEMENT table[DEFICIT_TABLE_SIZE];
} T_DEFICIT_TABLE_CB;
#define DTABLE_BASECREDIT 50

/*#endif*/ /*__KERNEL__*/
/********************************************************************************/
/* INLINE FUNCTIONS */
/********************************************************************************/



#endif
