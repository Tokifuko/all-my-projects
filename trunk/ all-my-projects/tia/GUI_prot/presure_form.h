//---------------------------------------------------------------------------

#ifndef presure_formH
#define presure_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TPresureForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *LabelCoef_0;
        TLabel *LabelCoef_2;
        TLabel *LabelCoef_1;
        TLabel *LabelCoef_3;
        TLabel *LabelCoef_4;
        TLabel *LabelCoef_5;
        TLabel *LabelCoef_6;
        TLabel *LabelCoef_7;
        TLabel *LabelAdc_1;
        TLabel *LabelAdc_2;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *LabeldT;
        TLabel *LabelTemp;
        TLabel *LabelOff;
        TLabel *LabelSens;
        TLabel *LabelPres;
        TButton *Button1;
        TLabel *LableStatus;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        void Calculation (void);
        __fastcall TPresureForm(TComponent* Owner);
};

         void PushCoef_0 (DWORD dData);
         void PushCoef_1 (DWORD dData);
         void PushCoef_2 (DWORD dData);
         void PushCoef_3 (DWORD dData);
         void PushCoef_4 (DWORD dData);
         void PushCoef_5 (DWORD dData);
         void PushCoef_6 (DWORD dData);
         void PushCoef_7 (DWORD dData);
         void PushAdc_1 (DWORD dData);
         void PushAdc_2 (DWORD dData);
//---------------------------------------------------------------------------
extern PACKAGE TPresureForm *PresureForm;
//---------------------------------------------------------------------------
#endif
