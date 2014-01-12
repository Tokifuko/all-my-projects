//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#pragma hdrstop

#include "weigth_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MyPoint"
#pragma resource "*.dfm"
TWeightForm *WeightForm;

#define SLIDE_MED_N             32
DWORD dSlideMed[SLIDE_MED_N];
unsigned int iSlideMedCounter=0;
using std::vector;

struct tCalibrPoint
{
   DWORD dAdcData;
   DWORD dWeight ;
};

vector<tCalibrPoint> vCalibr;
//---------------------------------------------------------------------------
__fastcall TWeightForm::TWeightForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TWeightForm::PushData (DWORD dData)
{

        CurrentDataSeries->Clear();
        CurrentDataSeries->AddY(dData);

      //скользящее среднее
      unsigned int i=0;
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

      //  индикация
      AnsiString s;
      s.sprintf("%d",dSlideMedLocal);
      Label5->Caption=s;
      Label6->Caption="34,75"; //  дописать

}
void __fastcall TWeightForm::Button1Click(TObject *Sender)
{
      tCalibrPoint stNewPoint;
      stNewPoint.dAdcData=34535;
      stNewPoint.dWeight=34534;
      vCalibr.push_back(stNewPoint);

}
//---------------------------------------------------------------------------
void __fastcall TWeightForm::btChWeigthClick(TObject *Sender)
{
        DWORD d=0;
        AnsiString s;
        d=Label5->Caption.ToDouble();
      s.sprintf("%d",d);
      Label8->Caption=s;
      if  (vCalibr.size()>=2)
      {
            d=Label6->Caption.ToDouble();
            s.sprintf("%f",d);
            Edit1->Text=s;
            unsigned int i;
            i=d/1;
            if ( i<=TrackBar1->Max) TrackBar1->Position=i;
                else  TrackBar1->Position=TrackBar1->Max;
            d=d-i;
            d=d*100;
            i=d/1;
            if ( i<=TrackBar2->Max) TrackBar2->Position=i;
                else  TrackBar2->Position=TrackBar1->Max;
      }


}
//---------------------------------------------------------------------------
