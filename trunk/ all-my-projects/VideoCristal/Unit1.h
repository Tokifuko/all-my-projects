//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------

struct myRecord_t
{
        unsigned int iCardID ;
        unsigned int iVideoLength;
        char chVideoPach[255];
};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
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
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall btAddRecordClick(TObject *Sender);
        void __fastcall btDelRecordClick(TObject *Sender);
        void __fastcall btSaveDataClick(TObject *Sender);
        void __fastcall btLoadDataClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
