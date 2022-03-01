/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* netlink.h */
/********************************************************************************/

#ifndef netlink_h
#define netlink_h
/********************************************************************************/
/* INCLUDES */
/********************************************************************************/

/********************************************************************************/
/* DEFINES */
/********************************************************************************/
#define NL_THREAD_NAME "netlink"
#define NETLINK_USER 31 /*#define MAX_LINKS 32 degeri'ne dikkat! bkz. netlink.h*/
#define MAX_PAYLOAD_LEN 9998
#define ACK_PAYLOAD_LEN 0

typedef struct
{
    unsigned short msgType;
} T_MSG_NL_SHORT;
#define T_MSG_NL_SHORT_SIZE sizeof(T_MSG_NL_SHORT)

typedef struct
{
    unsigned short msgType;
    unsigned char payload[MAX_PAYLOAD_LEN];
} T_MSG_NL_LONG;
#define T_MSG_NL_LONG_SIZE sizeof(T_MSG_NL_LONG)

#define NL_MSGTYPE_ECHO_REQ                     1
#define NL_MSGTYPE_ECHO_REP                     2
#define NL_MSGTYPE_MODULESTART                  3
#define NL_MSGTYPE_MODULESTOP                   4
#define NL_MSGTYPE_STATS_REQ                    5
#define NL_MSGTYPE_STATS_REP                    6
#define NL_MSGTYPE_LOG                          7
#define NL_MSGTYPE_CHANGE_SCHEDULER             8
#define NL_MSGTYPE_SET_BACKLOG_TIME             9
#define NL_MSGTYPE_SET_SCHEDULERQUEUE_LENGTH    10
#define NL_MSGTYPE_SET_EGRESS_LINK_RATE         11
#define NL_MSGTYPE_MODULESTARTED                12
#define NL_MSGTYPE_MODULESTOPPED                13

#define NL_MSGTYPE_KILL                         254
#define NL_MSGTYPE_ACK                          255

/*NETLINK MESSAGE TYPES FOR MODULES USING NETLINK INTERFACE*/
#define NL_NLMODULE                     1

#endif
