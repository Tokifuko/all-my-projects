//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#define CARD_ID_LEN     14
struct myRecord_t
{
        char chCardID[CARD_ID_LEN] ;
        unsigned int iVideoLength;
        char chVideoPach[255];
};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TButton *btAddRecord;
        TButton *btDelRecord;
        TButton *btSaveData;
        TButton *btLoadData;
        TComboBox *cbPort;
        TButton *btOpenPort;
        TButton *btClosePort;
        TLabel *lComChoise;
        TButton *btGetCardID;
        TLabel *lCurCardID;
        TLabel *lCurVideoLength;
        TLabel *lCurCardFilePach;
        TTimer *Timer1;
        TMemo *mLog;
        TTimer *Timer2;
        TCheckBox *cbStartPlay;
        TOpenDialog *odFindBSPlayer;
        TLabel *lBSPlayerPach;
        TButton *bfFindBSPlayer;
        TButton *btFindVideoFile;
        TOpenDialog *odFindVideoFile;
        TLabel *lPshFile;
        TButton *btFindPshFile;
        TOpenDialog *odFindPshFile;
        TTimer *Timer3;
        void __fastcall btAddRecordClick(TObject *Sender);
        void __fastcall btDelRecordClick(TObject *Sender);
        void __fastcall btSaveDataClick(TObject *Sender);
        void __fastcall btLoadDataClick(TObject *Sender);
        void __fastcall cbPortDropDown(TObject *Sender);
        void __fastcall btOpenPortClick(TObject *Sender);
        void __fastcall btClosePortClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall btGetCardIDClick(TObject *Sender);
        void __fastcall bfFindBSPlayerClick(TObject *Sender);
        void __fastcall btFindVideoFileClick(TObject *Sender);
        void __fastcall btFindPshFileClick(TObject *Sender);
        void __fastcall Timer3Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
