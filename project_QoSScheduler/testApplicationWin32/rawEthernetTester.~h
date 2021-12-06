//---------------------------------------------------------------------------

#ifndef rawEthernetTesterH
#define rawEthernetTesterH
//---------------------------------------------------------------------------
#include <pcap.h>

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ScktComp.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TmainForm : public TForm
{
__published:	// IDE-managed Components
        TMemo *recvMemo;
        TPanel *Panel1;
        TProgressBar *sendProgressBar;
        TButton *quitButton;
        TTrackBar *numOfMsgsTrackBar;
        TEdit *numOfMsgsEdit;
        TButton *sendButton;
        TLabeledEdit *rawRcvdEdit;
        TListBox *interfaceListBox;
        TPanel *Panel2;
        TCSpinEdit *rawMaxLenSpinEdit;
        TStaticText *lengthLabel;
        TCSpinEdit *rawMinLenSpinEdit;
        TStaticText *StaticText1;
        TButton *addFlowButton;
        TComboBox *etherTypeComboBox;
        TStaticText *StaticText2;
        TComboBox *flowsComboBox;
        TStaticText *StaticText3;
        TButton *removeFlowButton;
        TCSpinEdit *recurrenceSpinEdit;
        TStaticText *StaticText4;
        void __fastcall sendButtonClick(TObject *Sender);
        void __fastcall interfaceListBoxDblClick(TObject *Sender);
        void __fastcall quitButtonClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall numOfMsgsTrackBarChange(TObject *Sender);
        void __fastcall addFlowButtonClick(TObject *Sender);
        void __fastcall removeFlowButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TmainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
//---------------------------------------------------------------------------

#define MAX_NUMOF_FLOWS 8
#define MIN_ETHERTYPE   0x8800
#define MAX_ETHERTYPE   0x8807
#define MAX_RECURRENCE  64
typedef struct
{
        unsigned short ethType;
        unsigned short minLen;
        unsigned short maxLen;
        unsigned short recurrence;
} T_FLOW;

#define PADDED_ETHER_PACKET_LENGTH      60
#define ETHER_HEADER_LENGTH             14

#endif
