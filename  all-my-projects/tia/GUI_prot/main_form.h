//---------------------------------------------------------------------------

#ifndef main_formH
#define main_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TTimer *TestTimer;
        TTimer *SpeedMeterTimer;
        TLabel *LText1;
        TLabel *LTenzoSpeed;
        TTrackBar *TrackBar1;
        TButton *Button2;
        TTimer *ProcessTimer;
        TButton *Button3;
        TLabel *Label1;
        TButton *Button4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall TestTimerTimer(TObject *Sender);
        void __fastcall SpeedMeterTimerTimer(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall ProcessTimerTimer(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
