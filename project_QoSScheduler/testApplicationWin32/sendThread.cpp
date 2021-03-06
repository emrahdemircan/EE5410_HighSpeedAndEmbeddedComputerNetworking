//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "sendThread.h"
#include "rawEthernetTester.h"

#pragma package(smart_init)

extern int sendEtherPack(char* dest, char* data, int dataLength, unsigned short ethertype);
extern T_FLOW ethernetFlows[MAX_NUMOF_FLOWS];
extern unsigned short numberOfFlowsAdded;


//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall sendThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall sendThread::sendThread(bool CreateSuspended)
        : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall sendThread::Execute()
{
        //---- Place thread code here ----
        int totalNumberOfCycles;
        int numberOfCyclesPassed;
        char ethPayload[1500];
        T_FLOW sendThreadEthernetFlows[MAX_NUMOF_FLOWS];
        unsigned short numberOfFlowsLeft;
        unsigned char cycle[MAX_RECURRENCE];
        unsigned short currentCycleLength;
        unsigned short randomFlow;
        unsigned int rawLength;

        totalNumberOfCycles = mainForm->numOfMsgsTrackBar->Position;
        mainForm->sendProgressBar->Max = totalNumberOfCycles;
        numberOfCyclesPassed = 0;
        mainForm->sendProgressBar->Position = numberOfCyclesPassed;
        memset(ethPayload,0x55,1500);

        memcpy(sendThreadEthernetFlows,ethernetFlows,sizeof(T_FLOW)*MAX_NUMOF_FLOWS);
        numberOfFlowsLeft = numberOfFlowsAdded;
        memset(cycle,MAX_NUMOF_FLOWS+1,MAX_RECURRENCE);
        currentCycleLength = 0;
        /* let's fill in the send cycle with the given flows. */
        for(int i=0; i<MAX_RECURRENCE;i++)
        {
                /* pick a random flow from the available ones. */
                randomFlow = random(numberOfFlowsLeft);
                /* grab the flow number from the flow array */
                for(int j=0; j<numberOfFlowsAdded; j++)
                {
                        /* randomly picked flow number is matched with the flows array*/
                        if(sendThreadEthernetFlows[randomFlow].ethType == ethernetFlows[j].ethType)
                        {
                                cycle[i] = j;
                                currentCycleLength++;
                                break;
                        }
                }
                /* update the recurrence on the local copy of the flows array*/
                sendThreadEthernetFlows[randomFlow].recurrence--;
                /* if recurrence of the flow is 0 on the local copy, delete the local flow!*/
                if(sendThreadEthernetFlows[randomFlow].recurrence == 0)
                {
                        for(int k=randomFlow; k<MAX_NUMOF_FLOWS-1; k++)
                        {
                                memcpy(&sendThreadEthernetFlows[k],&sendThreadEthernetFlows[k+1],sizeof(T_FLOW));
                        }
                        memset(&sendThreadEthernetFlows[MAX_NUMOF_FLOWS-1],0,sizeof(T_FLOW));
                        numberOfFlowsLeft--;
                }
        }

        mainForm->recvMemo->Lines->Add("Started sending.");
        while(!Terminated && (numberOfCyclesPassed < totalNumberOfCycles))
        {
                for(int cycleEntry=0; cycleEntry<currentCycleLength; cycleEntry++)
                {
                        rawLength = ethernetFlows[cycle[cycleEntry]].minLen+
                                        random(ethernetFlows[cycle[cycleEntry]].minLen - ethernetFlows[cycle[cycleEntry]].maxLen);
                        sendEtherPack(NULL,&ethPayload[0],rawLength,ethernetFlows[cycle[cycleEntry]].ethType);
                }
                numberOfCyclesPassed++;
                mainForm->sendProgressBar->Position = numberOfCyclesPassed;
                mainForm->numOfMsgsEdit->Text = numberOfCyclesPassed;
                Sleep(1);
        }
        mainForm->recvMemo->Lines->Add("Sending ended.");
        mainForm->sendButton->Enabled = true;
        mainForm->quitButton->Enabled = false;
        mainForm->sendProgressBar->Position = 0;
        mainForm->numOfMsgsEdit->Text = mainForm->numOfMsgsTrackBar->Position;
}
//---------------------------------------------------------------------------
