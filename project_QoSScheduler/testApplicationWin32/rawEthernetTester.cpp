//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "rawEthernetTester.h"
#include "captureThread.h"
#include "sendThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TmainForm *mainForm;
/********************** FUNCTION PROTOTYPES ********************************/
int show_interfaces(void);
int startPacketCapture(void);
int stopPacketCapture(void);
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
int sendEtherPack(char* dest, char* data, int dataLength, unsigned short ethertype);
bool parse_incoming_packet(char* buffer, int NumberBytes, AnsiString FromIP);

/* flows will be defined on this variable*/
T_FLOW ethernetFlows[MAX_NUMOF_FLOWS];
unsigned short numberOfFlowsAdded = 0;
unsigned short recurrenceLeft = 0;

captureThread* capture_thread;
sendThread* send_thread;
pcap_t *adhandle;
u_char packet[1500];
TCriticalSection *lockEtherSend;
pcap_if_t *alldevs;
pcap_if_t *d;
int selected_interface_number;
char logBuf[1024];
u_int netmask;
struct bpf_program fcode;
int nRawReceived;

//---------------------------------------------------------------------------
int show_interfaces(void)
{
        int i=0;
        char errbuf[PCAP_ERRBUF_SIZE];
        
	mainForm->recvMemo->Lines->Add("Showing interfaces...");

	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
                mainForm->recvMemo->Lines->Add("Error in pcap_findalldevs: " + AnsiString(errbuf));
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}
	
	/* Print the list */
	for(d=alldevs; d; d=d->next)
	{
                if (d->description)
                {
			mainForm->recvMemo->Lines->Add(AnsiString(++i)+". :"+AnsiString(d->name)+": "+AnsiString(d->description));
                        mainForm->interfaceListBox->Items->Add(AnsiString(d->description));
                }
		else
                {
                        mainForm->recvMemo->Lines->Add(AnsiString(++i)+". :"+AnsiString(d->name)+": No description available");
                }
	}

	if(i==0)
	{
                mainForm->recvMemo->Lines->Add("No interfaces found! Make sure WinPcap is installed.");
		return -1;
	}
        return 1;
}

int startPacketCapture(void)
{
        int i=0;
        char packet_filter[] = "ether proto 0x9800";
        char errbuf[PCAP_ERRBUF_SIZE];

        /*alinan ve gonderilen sayisini sifirlayalim...*/
        nRawReceived = 0;

	/* Jump to the selected adapter */
	for(d=alldevs, i=0; i< selected_interface_number-1 ;d=d->next, i++);
	
	/* Open the adapter */
	if ((adhandle= pcap_open_live(d->name,	// name of the device
							 65536,			// portion of the packet to capture.
											// 65536 grants that the whole packet will be captured on all the MACs.
							 1,				// promiscuous mode (nonzero means promiscuous)
							 -1,			// read timeout -1 immediate 0 no return
							 errbuf			// error buffer
							 )) == NULL)
	{
                mainForm->recvMemo->Lines->Add("Unable to open the adapter. " + AnsiString(d->name) + " is not supported by WinPcap");
		pcap_freealldevs(alldevs);
		return -1;
	}
	mainForm->recvMemo->Lines->Add("pcap_open_live: OK");

	/* Check the link layer. We support only Ethernet for simplicity. */
	if(pcap_datalink(adhandle) != DLT_EN10MB)
	{
                mainForm->recvMemo->Lines->Add("This program works only on Ethernet networks.");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}
	mainForm->recvMemo->Lines->Add("pcap_datalink: OK");

	if(d->addresses != NULL)
		/* Retrieve the mask of the first address of the interface */
		netmask=((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* If the interface is without addresses we suppose to be in a C class network */
		netmask=0xffffff;

	//compile the filter
	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) <0 )
	{
		fprintf(stderr,"\nUnable to compile the packet filter. Check the syntax.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}
        mainForm->recvMemo->Lines->Add("packet_filter: OK");

	//set the filter
	if (pcap_setfilter(adhandle, &fcode)<0)
	{
		fprintf(stderr,"\nError setting the filter.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}
	mainForm->recvMemo->Lines->Add("pcap_setfilter: OK");

	mainForm->recvMemo->Lines->Add("Listening on: " + AnsiString(d->description));
	/* start the capture */
	/*pcap_loop(adhandle, 0, packet_handler, NULL);*/

        capture_thread=new captureThread(TRUE);
        capture_thread->Priority = tpIdle;
        capture_thread->Resume();
	
	return 0;
}

int stopPacketCapture(void)
{
        if(adhandle)
        {
                pcap_breakloop(adhandle);
                capture_thread->WaitFor();
        }
}
//---------------------------------------------------------------------------
/* Callback function invoked by libpcap for every incoming packet */
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
        struct tm *ltime;
	char timestr[16];
	time_t local_tv_sec;
        nRawReceived ++ ;
        mainForm->rawRcvdEdit->Text = AnsiString(nRawReceived);
}


int sendEtherPack(char* dest, char* data, int dataLength, unsigned short ethertype)
{

	int i;
        if(adhandle==0)
        {
                return -1;
        }
        lockEtherSend->Acquire();
        
        /*set mac destination*/
        if(dest == NULL)
        {
                packet[0]=0xff;
	        packet[1]=0xff;
	        packet[2]=0xff;
	        packet[3]=0xff;
	        packet[4]=0xff;
	        packet[5]=0xff;
        }
        else
        {
                memcpy(packet,dest,6);
        }
	/*set mac source*/
	/*PC*/
	packet[6]=0x00;
	packet[7]=0x01;
	packet[8]=0x22;
	packet[9]=0x33;
	packet[10]=0x44;
	packet[11]=0x55;

	packet[12]=(unsigned char)(ethertype>>8);
	packet[13]=(unsigned char)(ethertype&0x00FF);

	/* Fill the rest of the packet */
        memcpy(packet+ETHER_HEADER_LENGTH,data,dataLength);

        if( (dataLength+ETHER_HEADER_LENGTH) < PADDED_ETHER_PACKET_LENGTH )
        {
                for(i=0;i<(PADDED_ETHER_PACKET_LENGTH-dataLength-ETHER_HEADER_LENGTH);i++)
                {
                        packet[dataLength+ETHER_HEADER_LENGTH+i]=0x00;
                }
                dataLength=PADDED_ETHER_PACKET_LENGTH-ETHER_HEADER_LENGTH;
        }

	/* Send down the packet */
	if (pcap_sendpacket(adhandle,	// Adapter
		packet,				// buffer with the packet
		dataLength+ETHER_HEADER_LENGTH			// size
		) != 0)
	{
		fprintf(stderr,"\nError sending the packet: \n", pcap_geterr(adhandle));
                lockEtherSend->Release();
		return -1;
	}
        lockEtherSend->Release();
        return 1;
}
//---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner)
        : TForm(Owner)
{
        lockEtherSend = new TCriticalSection();
        adhandle = 0;
        show_interfaces();
        numOfMsgsEdit->Text = numOfMsgsTrackBar->Position;
        nRawReceived = 0;
        mainForm->rawRcvdEdit->Text = 0;
        memset(ethernetFlows,0,MAX_NUMOF_FLOWS*sizeof(T_FLOW));
        numberOfFlowsAdded = 0;
        recurrenceLeft = MAX_RECURRENCE;
        recurrenceSpinEdit->MaxValue = recurrenceLeft;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::sendButtonClick(TObject *Sender)
{
        sendButton->Enabled = false;
        send_thread=new sendThread(TRUE);
        send_thread->Priority = tpIdle;
        send_thread->Resume();
        quitButton->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::interfaceListBoxDblClick(TObject *Sender)
{
        recvMemo->Lines->Add("arayuz_listDblClick: ItemIndex: "+AnsiString(interfaceListBox->ItemIndex));
        selected_interface_number=interfaceListBox->ItemIndex+1;
        recvMemo->Lines->Add("selected_interface_number: "+AnsiString(selected_interface_number));
        /*interfaceListBox->Enabled=false;*/
        stopPacketCapture();
        startPacketCapture();
}
//--------------------------------------------------------------------------- 
void __fastcall TmainForm::quitButtonClick(TObject *Sender)
{
        send_thread->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        delete lockEtherSend;
        if(quitButton->Enabled == true)
        {
                this->quitButtonClick(this);
                send_thread->WaitFor();
        }
        stopPacketCapture();
        Sleep(2000);
        /* At this point, we don't need any more the device list. Free it */
	pcap_freealldevs(alldevs);
        Sleep(500);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::numOfMsgsTrackBarChange(TObject *Sender)
{
        numOfMsgsEdit->Text = numOfMsgsTrackBar->Position;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::addFlowButtonClick(TObject *Sender)
{
        T_FLOW f;
        /* check if number of flows exceeds or not! */
        if(numberOfFlowsAdded == MAX_NUMOF_FLOWS)
        {
                recvMemo->Lines->Add("Can not add another flow, maximum flows have been added already!");
                return;
        }
        f.ethType = etherTypeComboBox->ItemIndex + MIN_ETHERTYPE;
        f.minLen = rawMinLenSpinEdit->Text.ToInt();
        f.maxLen = rawMaxLenSpinEdit->Text.ToInt();
        f.recurrence = recurrenceSpinEdit->Text.ToInt();
        /* check if recurrence is 0 */
        if( (f.recurrence <= 0) || ( f.recurrence > recurrenceLeft ) )
        {
                recvMemo->Lines->Add("Minimum recurrence is 1!");
                return;
        }
        /* check if minimum and maximum length are consistent*/
        if(f.minLen > f.maxLen)
        {
                recvMemo->Lines->Add("Minimum length can not be bigger than maximum length!");
                return;
        }
        /* search for a flow with the same etherType value!*/
        for(int i=0; i<numberOfFlowsAdded; i++)
        {
                if(ethernetFlows[i].ethType == f.ethType)
                {
                        recvMemo->Lines->Add("There is a flow with the same etherType!");
                        return;
                }
        }
        memcpy(&ethernetFlows[numberOfFlowsAdded],&f,sizeof(T_FLOW));
        numberOfFlowsAdded++;
        flowsComboBox->Clear();
        for(int i=0; i<numberOfFlowsAdded; i++)
        {
                flowsComboBox->AddItem("0x"+AnsiString("0x").IntToHex(ethernetFlows[i].ethType,4)+"/"+
                                                                AnsiString(ethernetFlows[i].minLen)+"/"+
                                                                AnsiString(ethernetFlows[i].maxLen)+"/"+
                                                                AnsiString(ethernetFlows[i].recurrence),NULL);
        }
        flowsComboBox->ItemIndex = numberOfFlowsAdded-1;
        recurrenceLeft -= f.recurrence;
        if(recurrenceLeft == 0)
        {
                recurrenceSpinEdit->MinValue = -1;
        }
        else
        {
                recurrenceSpinEdit->MinValue = 0;
        }
        recurrenceSpinEdit->MaxValue = recurrenceLeft;
        recurrenceSpinEdit->Value = 0;
        recvMemo->Lines->Add("Flow added!");
        return;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::removeFlowButtonClick(TObject *Sender)
{
        unsigned short flowToBeDeleted;

        flowToBeDeleted = flowsComboBox->ItemIndex;
        recurrenceLeft += ethernetFlows[flowToBeDeleted].recurrence;
        recurrenceSpinEdit->MaxValue = recurrenceLeft;
        //recurrenceSpinEdit->Value = 1;
        /* go on, delete the flow!*/
        for(int i=flowToBeDeleted; i<MAX_NUMOF_FLOWS-1; i++)
        {
                memcpy(&ethernetFlows[i],&ethernetFlows[i+1],sizeof(T_FLOW));
        }
        memset(&ethernetFlows[MAX_NUMOF_FLOWS-1],0,sizeof(T_FLOW));
        numberOfFlowsAdded--;
        flowsComboBox->Clear();
        for(int i=0; i<numberOfFlowsAdded; i++)
        {
                flowsComboBox->AddItem("0x"+AnsiString("0x").IntToHex(ethernetFlows[i].ethType,4)+"/"+
                                                                AnsiString(ethernetFlows[i].minLen)+"/"+
                                                                AnsiString(ethernetFlows[i].maxLen)+"/"+
                                                                AnsiString(ethernetFlows[i].recurrence),NULL);
        }
        flowsComboBox->ItemIndex = 0;
        recvMemo->Lines->Add("Flow removed!");
        return;
}
//---------------------------------------------------------------------------

