//---------------------------------------------------------------------------

#ifndef chart_formH
#define chart_formH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class TChartForm : public TForm
{
__published:	// IDE-managed Components
        TChart *Chart1;
        TFastLineSeries *Series1;
        TLabel *Label1;
        TFastLineSeries *SlideMedSeries;
        TButton *btClear;
        TFastLineSeries *PseudoSlideMedSeries;
        TLabel *Label2;
        void __fastcall btClearClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        void DataChart (DWORD dData);
        __fastcall TChartForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChartForm *ChartForm;
//---------------------------------------------------------------------------
#endif
