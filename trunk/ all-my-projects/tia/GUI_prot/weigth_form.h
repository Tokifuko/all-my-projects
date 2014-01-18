//---------------------------------------------------------------------------

#ifndef weigth_formH
#define weigth_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MyPoint.hpp"
#include <Chart.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "TeeSeriesTextEd.hpp"
#include "TeeURL.hpp"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TWeightForm : public TForm
{
__published:	// IDE-managed Components
        TChart *Chart1;
        TMyPointSeries *CurrentPointSeries;
        TLabel *Label1;
        TLabel *Label2;
        TButton *btChWeigth;
        TTrackBar *TrackBar1;
        TTrackBar *TrackBar2;
        TLabel *Label3;
        TLabel *Label4;
        TButton *Button1;
        TEdit *Edit1;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TFastLineSeries *CurrentDataSeries;
        THorizLineSeries *CalibrSeries;
        TButton *btsaveToFile;
        TOpenDialog *OpenDialog1;
        TEdit *eFileNameEdit;
        TButton *btOpenDialog;
        TButton *btLoadFromFile;
        TMemo *Memo1;
        TLabel *Label10;
        TButton *btApply;
        TButton *btCancel;
        TStatusBar *StatusBar1;
        TMyPointSeries *CurrentAveragePoint;
        TLabel *Label11;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall btChWeigthClick(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall TrackBar2Change(TObject *Sender);
        void __fastcall Edit1Exit(TObject *Sender);
        void __fastcall btOpenDialogClick(TObject *Sender);
        void __fastcall btApplyClick(TObject *Sender);
        void __fastcall btsaveToFileClick(TObject *Sender);
        void __fastcall btLoadFromFileClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        void __fastcall DisplayCalibrData (void);
        void PushData (DWORD dData);
        __fastcall TWeightForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWeightForm *WeightForm;
//---------------------------------------------------------------------------
#endif
