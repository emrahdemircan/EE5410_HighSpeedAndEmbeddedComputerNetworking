/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* stats.h */
/********************************************************************************/

#ifndef stats_h
#define stats_h
/********************************************************************************/
/* INCLUDES */
/********************************************************************************/

/********************************************************************************/
/* DEFINES */
/********************************************************************************/

/*****************************************/
/* STATISTICS' TYPEDEFS*/
/*****************************************/
typedef struct
{
	unsigned int ethernetPacketIn;
	unsigned int queued;
	unsigned int notQueued;
	unsigned int dequeued;
	unsigned int processed;
	unsigned int dataProcessed;
	unsigned int ipcProcessed;
} T_ETHERNETRX_STATS;

typedef struct
{
    unsigned int    queueDelayProcessed;
    unsigned int    gap_1[4];
    struct timespec minQueueDelay;
    unsigned int    gap_2[4];
    struct timespec maxQueueDelay;
    unsigned int    gap_3[4];
    struct timespec totalQueueDelay;
    unsigned int    gap_4[4];
} T_QDELAYSTATS;

typedef struct
{
    unsigned int    queued;
    unsigned int    notQueued;
    unsigned int    qCurrentSize;
    unsigned int    qUsage;
    unsigned int    qOverflowBytes;
    unsigned int    dequeued;
    T_QDELAYSTATS   delayStats;
} T_QUEUE_STATS;

typedef struct
{
        unsigned int    ethernetPacketIn;
        T_QUEUE_STATS   queueStats[NUM_OF_ETHERNET_PRIORITY_CLASSES];
        unsigned int    processed;
        unsigned int    dataProcessed;
        unsigned int    sndSucceeded;
        unsigned int    sndFailed;
} T_ETHERNETSCHEDULER_STATS;

typedef struct
{
	unsigned int ethernetPacketIn;
	unsigned int queued;
	unsigned int notQueued;
	unsigned int dequeued;
	unsigned int processed;
        unsigned int dataProcessed;
	unsigned int ipcProcessed;
	unsigned int ethernetPacketOut;
	unsigned int sndSucceeded;
	unsigned int sndFailed;
} T_ETHERNETTX_STATS;

/*NL*/
typedef struct
{
	unsigned int queued;
	unsigned int notQueued;
	unsigned int dequeued;
	unsigned int processed;
	unsigned int ipcProcessed; /*number of IPC messages received*/
	unsigned int nlSent;
	unsigned int nlRcvd;
} T_NL_STATS;

/*ALL STATS*/
typedef struct
{
	T_ETHERNETRX_STATS ethernetRx;
        T_ETHERNETSCHEDULER_STATS ethernetSch;
	T_ETHERNETTX_STATS ethernetTx;
	T_NL_STATS nl;
}	T_STATS;

#endif
