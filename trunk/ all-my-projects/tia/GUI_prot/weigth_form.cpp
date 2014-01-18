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
long double ldWeightLocal=0;
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
        DecimalSeparator='.';
}
//---------------------------------------------------------------------------
//----------- вычисление среднего арифмитического  двунаправленной очереди --
DWORD CalcAverage ( deque <DWORD> &d)
{
        DWORD dAverage=0;
        std::deque<DWORD>::iterator MyIt = d.begin();
        while (MyIt != d.end())
        {
                dAverage+=(*MyIt);
                MyIt++;
        }
       return dAverage/d.size();
}
//--------------- сюда поступают данные от АЦП   ----------------------
void TWeightForm::PushData (DWORD dData)
{
      //скользящее среднее
      stdAverageArray.push_back(dData);
      if (stdAverageArray.size()>SLIDE_MED_N) stdAverageArray.pop_front();
     dAverageLocal=CalcAverage(stdAverageArray);

      ldWeightLocal=CalcWeight(dAverageLocal);

      //  индикация
      Label5->Caption=FloatToStrF(dAverageLocal,ffGeneral,32,0);
      Label6->Caption=FloatToStrF(ldWeightLocal,ffFixed,6,4);

      //   на графике
      CurrentDataSeries->Clear(); // вертикальная линия текущих данных
      CurrentDataSeries->AddXY(dData,CalibrSeries->MinYValue()-1);
      CurrentDataSeries->AddXY(dData,CalibrSeries->MaxYValue()+1);
      CurrentPointSeries->Clear(); // зеленая точка текущих данный
      CurrentPointSeries->AddXY(dData,CalcWeight(dData));
      CurrentAveragePoint->Clear(); // желтая точка - среднее значение
      CurrentAveragePoint->AddXY(dAverageLocal,CalcWeight(dAverageLocal));

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
      s=FloatToStrF(it->dAdcData,ffGeneral,32,0)+"; "+FloatToStrF(it->ldWeight,ffFixed,3,3);
      Memo1->Lines->Add(s); // отображение в МЕМО   "dAdcData; ldWeight"
      ++it;
    }
}
//---------------------------------------------------------------------------

//---------- кнопка УТОЧНИТЬ ВЕС---------------------------------------------
//----- подготавливает данные для новой калибровочной точки------------------
void __fastcall TWeightForm::btChWeigthClick(TObject *Sender)
{
        ldWeightToChange=ldWeightLocal;
      dAverageToChange=dAverageLocal;

      // отображение
      Edit1->Text=FloatToStrF(ldWeightToChange,ffFixed,3,3);
      Label8->Caption=FloatToStrF(dAverageToChange,ffGeneral,32,0);
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
        Edit1->Text=FloatToStrF(ldWeightToChange,ffFixed,3,3);
}
//--------- изменение веса ползунка-ми  TrackBar-------------
//---------------- граммы ---------------------------------------------
void __fastcall TWeightForm::TrackBar2Change(TObject *Sender)
{
        DWORD d=ldWeightToChange;
     ldWeightToChange=d; // оставляем целое
        ldWeightToChange=ldWeightToChange+((float)(TrackBar2->Position)/(float)(TrackBar2->Max));
        Edit1->Text=FloatToStrF(ldWeightToChange,ffFixed,3,3);
}
//---------------------------------------------------------------------------
// -------- выход из EDIT, после введения нового числа -------------------
void __fastcall TWeightForm::Edit1Exit(TObject *Sender)
{
   long double ld;
   ld=Edit1->Text.ToDouble();
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
        return (long double) ld;
}
//------------ получение калибровочной точки из строки ----------------------
bool ConvertStringToPoint (AnsiString* s,tCalibrPoint* p)
{
        int i=s->AnsiPos(';');
        if (i==0) return false;
        AnsiString sData, sWeight;
        sData=s->SubString(0,i-1);
        sWeight=s->SubString(i+1,s->Length());
        p->dAdcData=sData.ToDouble();
        p->ldWeight=sWeight.ToDouble();
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
//------------ кнопка ПРИМЕНИТЬ   -------------------------------------------
//---------- загружает точи из МЕМО в калибровочный вектор-------------------

void __fastcall TWeightForm::btApplyClick(TObject *Sender)
{
        tCalibrPoint stNewPoint;
        AnsiString s;
        int i=0;
        vCalibr.clear();
        while (i<Memo1->Lines->Count)
        {
                s=Memo1->Lines->operator [](i);
                try   {ConvertStringToPoint(&s,&stNewPoint);}
                catch (EConvertError &E) {ShowMessage(AnsiString(E.ClassName()) + "\n" + AnsiString(E.Message));}
                /// StatusBar1->SimpleText=(AnsiString(E.ClassName()) + "    " + AnsiString(E.Message));
                 vCalibr.push_back(stNewPoint);   // добавляем точку
                i++;
                
        }
        std::sort(vCalibr.begin(),vCalibr.end(),PointCompare); // и пересортировываем вектор
        DisplayCalibrData();

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



