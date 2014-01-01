//---------------------------------------------------------------------------

#ifndef com_formH
#define com_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
typedef void(*ftVoid_Void)(DWORD);
//---------------------------------------------------------------------------
class TComForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TSpeedButton *SpeedButton1;
        TComboBox *ComboBox1;
        TComboBox *ComboBox2;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TGroupBox *GroupBox2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit1;
        TMemo *Memo1;
        TButton *Button1;
        TButton *Button3;
        TStatusBar *StatusBar1;
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        ftVoid_Void CallBack;
        __fastcall TComForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TComForm *ComForm;
//---------------------------------------------------------------------------
#endif
