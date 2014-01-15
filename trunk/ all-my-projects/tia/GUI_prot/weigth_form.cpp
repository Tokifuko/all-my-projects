//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <stdio>
//#include <cstdlib>
#pragma hdrstop

#include "weigth_form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MyPoint"
#pragma link "TeeSeriesTextEd"
#pragma link "TeeURL"
#pragma resource "*.dfm"
TWeightForm *WeightForm;

#define SLIDE_MED_N             32

DWORD dAverageLocal=0;
DWORD dAverageToChange=0;
long double dWeightLocal=0;
long double ldWeightToChange=0;

using std::vector;
using std::deque;

struct tCalibrPoint
{
   DWORD dAdcData;
   long double ldWeight ;
};

long double CalcWeight(DWORD dData);
bool PointCompare(tCalibrPoint a,tCalibrPoint b);
bool ConvertStringToPoint (AnsiString* s,tCalibrPoint* p);

deque <DWORD> stdAverageArray;
vector<tCalibrPoint> vCalibr;
//---------------------------------------------------------------------------
__fastcall TWeightForm::TWeightForm(TComponent* Owner)
        : TForm(Owner)
{
        AnsiString s;
        s=Application->ExeName;
        s.Delete(s.Length()-3,4);
        eFileNameEdit->Text=s+".txt";
        Memo1->Lines->LoadFromFile(eFileNameEdit->Text);
}
//---------------------------------------------------------------------------
//----------- вычисление среднего арифмитического  двунаправленной очереди --
DWORD CalcAverage ( deque <DWORD> &d)
{
        DWORD dAverage=0;
        std::deque<DWORD>::iterator MyIt = d.begin();
        while (MyIt != d.end()) dAverage+=(*MyIt++)/d.size();
       return dAverage;
}
//--------------- сюда поступают данные от АЦП   ----------------------
void TWeightForm::PushData (DWORD dData)
{
      //скользящее среднее
      stdAverageArray.push_back(dData);
      if (stdAverageArray.size()>SLIDE_MED_N) stdAverageArray.pop_front();
     dAverageLocal=CalcAverage(stdAverageArray);

      dWeightLocal=CalcWeight(dData);

      //  индикация
      AnsiString s;
      s.sprintf("%d",dAverageLocal);
      Label5->Caption=s;
      s.sprintf("%3.3Lf",dWeightLocal);
      Label6->Caption=s;

      //   на графике
      CurrentDataSeries->Clear();
      CurrentDataSeries->AddXY(dData,CalibrSeries->MinYValue()-1);
      CurrentDataSeries->AddXY(dData,CalibrSeries->MaxYValue()+1);
      CurrentPointSeries->Clear();
      CurrentPointSeries->AddXY(dData,dWeightLocal);
}

//----------- кнопка СОХРАНИТЬ, сохранет точку в калибровочном векторе ---
void __fastcall TWeightForm::Button1Click(TObject *Sender)
{
      tCalibrPoint stNewPoint;
      if  (dAverageToChange==0) return;
      if  (ldWeightToChange==0) return;
      stNewPoint.dAdcData=dAverageToChange;
      stNewPoint.ldWeight=ldWeightToChange;
      vCalibr.push_back(stNewPoint);   // добавляем точку
      std::sort(vCalibr.begin(),vCalibr.end(),PointCompare); // и пересортировываем вектор
      DisplayCalibrData(); // отображение


}
//---------------------------------------------------------------------------
//------------ Отображение калибровочного вектора на форме ------------------
void __fastcall TWeightForm::DisplayCalibrData (void)
{
   AnsiString s;
   std::vector<tCalibrPoint>::iterator it=vCalibr.begin();
   CalibrSeries->Clear();
   Memo1->Clear();
    while (it!=vCalibr.end())
    {
      CalibrSeries->AddXY(it->dAdcData,it->ldWeight); // отображение на графике
      s.printf("%d; %3.3Lf",it->dAdcData,it->ldWeight);
      Memo1->Lines->Add(s); // отображение в МЕМО
      ++it;
    }
}
//---------------------------------------------------------------------------

//---------- кнопка УТОЧНИТЬ ВЕС---------------------------------------------
//----- подготавливает данные для новой калибровочной точки------------------
void __fastcall TWeightForm::btChWeigthClick(TObject *Sender)
{
        ldWeightToChange=dWeightLocal;
      dAverageToChange=dAverageLocal;

      AnsiString s;
      s.sprintf("%3.3Lf",ldWeightToChange);
      Edit1->Text=s;
      s.sprintf("%d",dAverageToChange);
      Label8->Caption=s;
      DWORD d;
      d=ldWeightToChange; // преобразование типов оставит только целую часть
      TrackBar1->Position=d;
      d=(ldWeightToChange-d)*(TrackBar2->Max);
        TrackBar2->Position=d;
}
//--------- изменение веса ползунками  TrackBar-------------
//-------------------- киллограммы ----------------------------------
void __fastcall TWeightForm::TrackBar1Change(TObject *Sender)
{
      DWORD d=ldWeightToChange;
      ldWeightToChange=ldWeightToChange-d;  // оставляем дробное
     ldWeightToChange=ldWeightToChange+TrackBar1->Position;
     AnsiString s;
      s.sprintf("%3.3Lf",ldWeightToChange);
      Edit1->Text=s;
}
//--------- изменение веса ползунка-ми  TrackBar-------------
//---------------- граммы ---------------------------------------------
void __fastcall TWeightForm::TrackBar2Change(TObject *Sender)
{
        DWORD d=ldWeightToChange;
     ldWeightToChange=d; // оставляем целое
        ldWeightToChange=ldWeightToChange+((float)(TrackBar2->Position)/(float)(TrackBar2->Max));
     AnsiString s;
      s.sprintf("%3.3Lf",ldWeightToChange);
      Edit1->Text=s;
}
//---------------------------------------------------------------------------
// -------- выход из EDIT, после введения нового числа -------------------
void __fastcall TWeightForm::Edit1Exit(TObject *Sender)
{
   long double ld;
   AnsiString s;
   s=Edit1->Text;
   ld=strtod(s.c_str(),NULL);
   if (ld>(TrackBar1->Max)) ld=TrackBar1->Max;
   DWORD d;
   d=ld; // преобразование типов оставит только целую часть
   TrackBar1->Position=d;
   d=(ld-d)*(TrackBar2->Max);
   TrackBar2->Position=d;
   ldWeightToChange=ld;

}
//---------------------------------------------------------------------------
// --------------------- CalcWeight -----------------------------------------
// ---  вычисляет текущий вес, используя данные АЦП и калибровочный вектор --
long double CalcWeight(DWORD dData)
{
tCalibrPoint stFirstPoint;
tCalibrPoint stSecondPoint;
    std::vector<tCalibrPoint>::iterator it=vCalibr.begin();
    // ищем первый элемент, больше текущего
    if (vCalibr.size()==0) return 0;
    while (it!=vCalibr.end())
    {
        if (dData<=(it->dAdcData))
        {
                stFirstPoint=*it;
                // если он самый первый - то выводим значение веса из него
                if  (it==vCalibr.begin())  return  stFirstPoint.ldWeight;
                     // если перед ним есть меньший элемент, берем его
                     else
                     {
                       --it;
                       stSecondPoint=*it;
                     }
                break;  // while (it!=vCalibr.end())
        }
        ++it;
    }
    // если наши данные больше любого элемента вектора
    // то берем последний, самый больший элемент.
    if (it== vCalibr.end())
    {
        --it;
        return it->ldWeight;
    }

/* система уравнений  прямой y=f(x)
 где x - это данные с АЦП , y - вес
 | y1 = kx1 + b
 | y2 = kx2 + b
 b = y2 - kx2
 y1 = kx1 + y2 - kx2
k = (y1 - y2) / (x1 - x2)
b = y2 - k*x2
*/
        long double ld, k, b;
        k=(stFirstPoint.ldWeight-stSecondPoint.ldWeight)/(stFirstPoint.dAdcData-stSecondPoint.dAdcData);
        b= stSecondPoint.ldWeight-(k*stSecondPoint.dAdcData);
        ld=k*dData +b;
        return ld;
}
//------------ получение калибровочной точки из строки ----------------------
bool ConvertStringToPoint (AnsiString* s,tCalibrPoint* p)
{
        int i=s->AnsiPos(';');
        if (i==0) return false;
        AnsiString sData, sWeight;
        sData=s->SubString(0,i-1);
        sWeight=s->SubString(i+1,s->Length());
        sData="2564";
        int d;
     11111111111111111111111111111111111111111111111!11!!!!1
      //  p->dAdcData=sData.ToDouble();
       // p->ldWeight=sWeight.ToDouble();
        return true;
}
//---------------------------------------------------------------------------
//------------ предикат для сортировки --------------------------------------
bool PointCompare(tCalibrPoint a,tCalibrPoint b)
{
        if ((a.dAdcData)<=(b.dAdcData)) return true;
        return false;
}
//---------------------------------------------------------------------------

void __fastcall TWeightForm::btOpenDialogClick(TObject *Sender)
{
        OpenDialog1->FileName=eFileNameEdit->Text;
        OpenDialog1->Execute();
        eFileNameEdit->Text=OpenDialog1->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TWeightForm::btApplyClick(TObject *Sender)
{
        tCalibrPoint stNewPoint;
        AnsiString s;
        s=Memo1->Lines->operator [](0);
        ConvertStringToPoint(&s,&stNewPoint);
}
//---------------------------------------------------------------------------

void __fastcall TWeightForm::btsaveToFileClick(TObject *Sender)
{
Memo1->Lines->SaveToFile(eFileNameEdit->Text);
}
//---------------------------------------------------------------------------

void __fastcall TWeightForm::btLoadFromFileClick(TObject *Sender)
{
Memo1->Lines->LoadFromFile(eFileNameEdit->Text);
}
//---------------------------------------------------------------------------

