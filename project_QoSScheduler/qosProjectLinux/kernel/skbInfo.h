/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* skbInfo.h */
/********************************************************************************/

#ifndef skbInfo_h
#define skbInfo_h
/********************************************************************************/
/* INCLUDES */
/********************************************************************************/

/********************************************************************************/
/* DEFINES */
/********************************************************************************/

/*Message Types for Task Queues*/
typedef enum
{
    MSG_IPC			= 1,	/*Inter process communication, thread to thread commands*/
    MSG_DATA		= 2,	/*ethernet data messages*/
    MSG_NETLINK		= 3,	/*NETLINK messages*/
    MSG_TIMER		= 4		/*timer messages*/
}T_MESSAGE_TYPE;

/*kernel buffer içindeki cb[48] alani kullaniciya acik bir alan.
Bu alani, skb'lerin degisik threadler arasinda gezerken bilgi
saklamasi icin kullaniyoruz. 48 bytelik alanin asagidaki struct
tipine cast edilmesi ile cesitli degerler tasinacak.*/
typedef struct /*Dikkat en fazla 48 byte olacak!*/
{	
	T_MESSAGE_TYPE	msgType;
	unsigned char	priority;
        struct timespec timeStamp;
}T_SKBUFFCB_INFO;

#define SKB_INJECT	0xab

/********************************************************************************/
/* INLINE FUNCTIONS */
/********************************************************************************/

/********************************/
/* setSkbMsgType */
/********************************/
static inline void setSkbMsgType(struct sk_buff *skb, T_MESSAGE_TYPE msgType)
{
    ((T_SKBUFFCB_INFO*)(skb->cb))->msgType = msgType;
}/*setSkbMsgType*/

/********************************/
/* getSkbMsgType */
/********************************/
static inline T_MESSAGE_TYPE getSkbMsgType(struct sk_buff *skb)
{
    return ((T_SKBUFFCB_INFO*)(skb->cb))->msgType;
}/*getSkbMsgType*/

/********************************/
/* setSkbPriority */
/********************************/
static inline void setSkbPriority(struct sk_buff *skb, unsigned char priority)
{
    ((T_SKBUFFCB_INFO*)(skb->cb))->priority = priority;
}/*setSkbPriority*/

/********************************/
/* getSkbPriority */
/********************************/
static inline unsigned char getSkbPriority(struct sk_buff *skb)
{
    return ((T_SKBUFFCB_INFO*)(skb->cb))->priority;
}/*getSkbPriority*/


/********************************/
/* setSkbTimeStamp */
/********************************/
static inline void setSkbTimeStamp(struct sk_buff *skb)
{
    ((T_SKBUFFCB_INFO*)(skb->cb))->timeStamp = current_kernel_time();
}/*setSkbTimeStamp*/

/********************************/
/* getSkbTimeStamp */
/********************************/
static inline struct timespec getSkbTimeStamp(struct sk_buff *skb)
{
    return ((T_SKBUFFCB_INFO*)(skb->cb))->timeStamp;
}/*getSkbTimeStamp*/

#endif
