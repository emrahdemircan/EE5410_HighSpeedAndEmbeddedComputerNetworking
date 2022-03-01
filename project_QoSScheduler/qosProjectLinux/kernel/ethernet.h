/********************************************************************************/
/* EE5410 TERM PROJECT */
/* EMRAH DEMiRCAN */
/* 112341-3 */
/* ethernet.h */
/********************************************************************************/

#ifndef ethernet_h
#define ethernet_h
/********************************************************************************/
/* INCLUDES */
/********************************************************************************/

/********************************************************************************/
/* DEFINES */
/********************************************************************************/
#define ETHERNETSENDER_THREAD_NAME	"ethernetTx"
#define ETHERNETSCHEDULER_THREAD_NAME   "ethernetSch"
#define ETHERNETRECEIVER_THREAD_NAME	"ethernetRx"

#define ETHERNET_INPUT_SIDE_NAME		"enp2s0"
#define ETHERNET_OUTPUT_SIDE_NAME		"enp2s0"

#define ETHERTYPE_TOBESTOLEN_BEGIN    		0x8800
#define ETHERTYPE_TOBESTOLEN_END    		0x8807

#define NUM_OF_ETHERNET_PRIORITY_CLASSES        8

#ifndef ETH_HLEN
    #define ETH_HLEN 14
#endif

#ifndef ETH_ALEN
    #define ETH_ALEN 6
#endif

#ifndef ETH_DATA_LEN
    #define ETH_DATA_LEN 1500
#endif

#ifdef __KERNEL__

/********************************************************************************/
/* INLINE FUNCTIONS */
/********************************************************************************/

/********************************/
/* determinePriority */
/********************************/
/*priority of an ethernet packet is determined from the etherType of it by using the formula: */
/* priority = (ethertype - ETHERTYPE_TOBESTOLEN_BEGIN)%NUM_OF_ETHERNET_PRIORITY_CLASSES */
static inline unsigned char determinePriority(unsigned short etherType)
{
    return (unsigned char)( (etherType-ETHERTYPE_TOBESTOLEN_BEGIN)%NUM_OF_ETHERNET_PRIORITY_CLASSES );
}/*determinePriority*/

/********************************/
/* createEthernetPacketSkb */
/********************************/
/*Bu fonksiyon ethernet paketi oluşturmak isteyenin */
static inline struct sk_buff* createEthernetPacketSkb(unsigned short etherType,unsigned short etherPayloadLen,unsigned char* src,unsigned char* dest)
{
    struct ethhdr *eh;
    struct sk_buff* currentSkb;

    if( etherPayloadLen > ETH_DATA_LEN ) /*ETH_DATA_LEN = 1500 -> if_ether.h*/
    {
        return NULL;
    }
    currentSkb = alloc_skb(ETH_HLEN+2+etherPayloadLen, GFP_KERNEL);
    if(currentSkb == NULL)
    {
        return NULL;
    }
    /*gelen paket  tipi ne olursa olsun 4 bayt alignmentli en azindan ETH_HLEN
    kadar (14 bayttan -> 16 bayta alignment) daha fazla bir alani tutmamiz lazim.
    Boylece bir IP paketi geldiginde ethernet basligi icin kullanilacak bir alanimiz
    olacak...*/

    skb_reserve(currentSkb, ETH_HLEN + 2); /*reserve islemini yapinca skb data ptr ilerliyor, head ayni kaliyor.*/
    /*headroomdan ethernet basligi icin yer aciyoruz.headroom da 2 bayt yer kaldi*/
    eh = (struct ethhdr*)skb_push(currentSkb,ETH_HLEN);
    currentSkb->mac_header = (unsigned char*)eh - (unsigned char*)(currentSkb->head);
    memcpy(eh->h_dest, (void *)dest, ETH_ALEN);
    memcpy(eh->h_source, (void *)src, ETH_ALEN);
    eh->h_proto = htons(etherType);
    return currentSkb;
}/*createEthernetPacketSkb*/

/********************************/
/* dumpMemory */
/********************************/
static inline void dumpMemory(unsigned char* memPtr, unsigned short memLen)
{
    unsigned short index;
    unsigned char* data;

    data = memPtr;
    for(index = 0; index<memLen; index+=16)
    {
        LOG_INFO((logInfoBuf,"%02x %02x %02x %02x %02x %02x %02x %02x - %02x %02x %02x %02x %02x %02x %02x %02x \n",
                 *(data),*(data+1),*(data+2),*(data+3),*(data+4),*(data+5),*(data+6),*(data+7),
                 *(data+8),*(data+9),*(data+10),*(data+11),*(data+12),*(data+13),*(data+14),*(data+15)));
        data += 16;
    }
    LOG_INFO((logInfoBuf,"\n"))
}/*dumpMemory*/
#endif /*ifdef __KERNEL_*/

#endif
