//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include "PERFGRAP.h"
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TComboBox *ComboBox1;
        TLabel *Label2;
        TComboBox *ComboBox2;
        TGroupBox *GroupBox2;
        TEdit *Edit1;
        TMemo *Memo1;
        TLabel *Label3;
        TLabel *Label4;
        TSpeedButton *SpeedButton1;
        TStatusBar *StatusBar1;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TButton *Button1;
        TGroupBox *GroupBox3;
        TCheckBox *CheckBox3;
        TLabel *Label5;
        TLabel *Label6;
	TButton *Button3;
        TChart *Chart1;
        TLineSeries *Series1;
        TPointSeries *Series2;
        TPointSeries *Series3;
        TLabel *lCalipersData;
        TButton *Button2;
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CheckBox3Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
