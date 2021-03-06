//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "captureThread.h"
#include "rawEthernetTester.h"
#pragma package(smart_init)

extern void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);
extern pcap_t *adhandle;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall captureThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall captureThread::captureThread(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void captureThread::SetName()
{
        THREADNAME_INFO info;
        info.dwType = 0x1000;
        info.szName = "captureThread";
        info.dwThreadID = -1;
        info.dwFlags = 0;

        __try
        {
                 RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD),(DWORD*)&info );
        }
        __except (EXCEPTION_CONTINUE_EXECUTION)
        {
        }
}
//---------------------------------------------------------------------------
void __fastcall captureThread::Execute()
{
        //---- Place thread code here ----
        SetName();
        //---- Place thread code here ----
        mainForm->recvMemo->Lines->Add("captureThread started.");
        mainForm->recvMemo->Lines->Add("Pcap reception started.");
        pcap_loop(adhandle, 0, packet_handler, NULL);
        mainForm->recvMemo->Lines->Add("Pcap reception ended.");
        pcap_close(adhandle);
        adhandle = 0;
        mainForm->recvMemo->Lines->Add("captureThread ended.");
}
//---------------------------------------------------------------------------
