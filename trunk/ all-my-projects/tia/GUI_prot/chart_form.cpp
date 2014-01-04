//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "chart_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChartForm *ChartForm;
//---------------------------------------------------------------------------
__fastcall TChartForm::TChartForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TChartForm::DataChart (DWORD dData)
{


   //     if (Series1->Count()>10)
      //  {
        //Series1->Depth=5;
      //  }
              AnsiString s;
        s.sprintf("%d",Series1->MandatoryValueList->Count);
        s.sprintf("%d",Series1->Count());
        //
      Label1->Caption=s;
     // Series1->MandatoryValueList->TotalABS=10;
      if (Series1->Count()>10) Series1->MandatoryValueList->Delete(0);
        Series1->AddY(dData,"lable") ;
}
