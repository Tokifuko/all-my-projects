//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "chart_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define SLIDE_MED_N             32
#define PSEUDO_SLIDE_MED_N      32
#define CHART_LEN     500
TChartForm *ChartForm;
DWORD dPseudoSlideMed=0;
DWORD dSlideMed[SLIDE_MED_N];
unsigned int iSlideMedCounter=0;
//---------------------------------------------------------------------------
__fastcall TChartForm::TChartForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TChartForm::DataChart (DWORD dData)
{
      unsigned int i=0;
      AnsiString s;
      s.sprintf("%d",Series1->Count());
      Label1->Caption=s;
      Series1->AddY(dData) ;
      if (Series1->Count()>CHART_LEN) Series1->Delete(0,1,true);

      // вычисление псевдо_скользящего среднего (на самом деле это БИК фильтр получился)
       if (PseudoSlideMedSeries->Count()==0) dPseudoSlideMed=dData;
      dPseudoSlideMed=dPseudoSlideMed-(dPseudoSlideMed/PSEUDO_SLIDE_MED_N)+(dData/PSEUDO_SLIDE_MED_N);
      PseudoSlideMedSeries->AddY(dPseudoSlideMed) ;
      if (PseudoSlideMedSeries->Count()>CHART_LEN) PseudoSlideMedSeries->Delete(0,1,true);

      // И скользящее среднее
      if (SlideMedSeries->Count()==0)  // заполнеение начального массива
        {
                while (i<SLIDE_MED_N)
                {
                        dSlideMed[i]=dData/SLIDE_MED_N;
                        i++;
                }
        }
      dSlideMed[iSlideMedCounter]=dData/SLIDE_MED_N;
      iSlideMedCounter++;
      if (iSlideMedCounter==SLIDE_MED_N) iSlideMedCounter=0;
      DWORD dSlideMedLocal=0;
      i=0;
      while (i<SLIDE_MED_N)
      {
         dSlideMedLocal=dSlideMedLocal+dSlideMed[i];
         i++;
      }
      SlideMedSeries->AddY(dSlideMedLocal) ;
      if (SlideMedSeries->Count()>CHART_LEN) SlideMedSeries->Delete(0,1,true);



}
void __fastcall TChartForm::btClearClick(TObject *Sender)
{
    Series1->Clear();
    SlideMedSeries->Clear();
    PseudoSlideMedSeries->Clear();

}
//---------------------------------------------------------------------------

