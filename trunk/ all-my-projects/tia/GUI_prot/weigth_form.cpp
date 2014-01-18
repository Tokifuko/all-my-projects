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
//----------- ���������� �������� ���������������  ��������������� ������� --
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
//--------------- ���� ��������� ������ �� ���   ----------------------
void TWeightForm::PushData (DWORD dData)
{
      //���������� �������
      stdAverageArray.push_back(dData);
      if (stdAverageArray.size()>SLIDE_MED_N) stdAverageArray.pop_front();
     dAverageLocal=CalcAverage(stdAverageArray);

      ldWeightLocal=CalcWeight(dAverageLocal);

      //  ���������
      Label5->Caption=FloatToStrF(dAverageLocal,ffGeneral,32,0);
      Label6->Caption=FloatToStrF(ldWeightLocal,ffFixed,6,4);

      //   �� �������
      CurrentDataSeries->Clear(); // ������������ ����� ������� ������
      CurrentDataSeries->AddXY(dData,CalibrSeries->MinYValue()-1);
      CurrentDataSeries->AddXY(dData,CalibrSeries->MaxYValue()+1);
      CurrentPointSeries->Clear(); // ������� ����� ������� ������
      CurrentPointSeries->AddXY(dData,CalcWeight(dData));
      CurrentAveragePoint->Clear(); // ������ ����� - ������� ��������
      CurrentAveragePoint->AddXY(dAverageLocal,CalcWeight(dAverageLocal));

}

//----------- ������ ���������, �������� ����� � ������������� ������� ---
void __fastcall TWeightForm::Button1Click(TObject *Sender)
{
      tCalibrPoint stNewPoint;
      if  (dAverageToChange==0) return;
      if  (ldWeightToChange==0) return;
      stNewPoint.dAdcData=dAverageToChange;
      stNewPoint.ldWeight=ldWeightToChange;
      vCalibr.push_back(stNewPoint);   // ��������� �����
      std::sort(vCalibr.begin(),vCalibr.end(),PointCompare); // � ����������������� ������
      DisplayCalibrData(); // �����������
}
//---------------------------------------------------------------------------
//------------ ����������� �������������� ������� �� ����� ------------------
void __fastcall TWeightForm::DisplayCalibrData (void)
{
   AnsiString s;
   std::vector<tCalibrPoint>::iterator it=vCalibr.begin();
   CalibrSeries->Clear();
   Memo1->Clear();
    while (it!=vCalibr.end())
    {
      CalibrSeries->AddXY(it->dAdcData,it->ldWeight); // ����������� �� �������
      s=FloatToStrF(it->dAdcData,ffGeneral,32,0)+"; "+FloatToStrF(it->ldWeight,ffFixed,3,3);
      Memo1->Lines->Add(s); // ����������� � ����   "dAdcData; ldWeight"
      ++it;
    }
}
//---------------------------------------------------------------------------

//---------- ������ �������� ���---------------------------------------------
//----- �������������� ������ ��� ����� ������������� �����------------------
void __fastcall TWeightForm::btChWeigthClick(TObject *Sender)
{
        ldWeightToChange=ldWeightLocal;
      dAverageToChange=dAverageLocal;

      // �����������
      Edit1->Text=FloatToStrF(ldWeightToChange,ffFixed,3,3);
      Label8->Caption=FloatToStrF(dAverageToChange,ffGeneral,32,0);
      DWORD d;
      d=ldWeightToChange; // �������������� ����� ������� ������ ����� �����
      TrackBar1->Position=d;
      d=(ldWeightToChange-d)*(TrackBar2->Max);
        TrackBar2->Position=d;
}
//--------- ��������� ���� ����������  TrackBar-------------
//-------------------- ����������� ----------------------------------
void __fastcall TWeightForm::TrackBar1Change(TObject *Sender)
{
      DWORD d=ldWeightToChange;
      ldWeightToChange=ldWeightToChange-d;  // ��������� �������
     ldWeightToChange=ldWeightToChange+TrackBar1->Position;
        Edit1->Text=FloatToStrF(ldWeightToChange,ffFixed,3,3);
}
//--------- ��������� ���� ��������-��  TrackBar-------------
//---------------- ������ ---------------------------------------------
void __fastcall TWeightForm::TrackBar2Change(TObject *Sender)
{
        DWORD d=ldWeightToChange;
     ldWeightToChange=d; // ��������� �����
        ldWeightToChange=ldWeightToChange+((float)(TrackBar2->Position)/(float)(TrackBar2->Max));
        Edit1->Text=FloatToStrF(ldWeightToChange,ffFixed,3,3);
}
//---------------------------------------------------------------------------
// -------- ����� �� EDIT, ����� �������� ������ ����� -------------------
void __fastcall TWeightForm::Edit1Exit(TObject *Sender)
{
   long double ld;
   ld=Edit1->Text.ToDouble();
   if (ld>(TrackBar1->Max)) ld=TrackBar1->Max;
   DWORD d;
   d=ld; // �������������� ����� ������� ������ ����� �����
   TrackBar1->Position=d;
   d=(ld-d)*(TrackBar2->Max);
   TrackBar2->Position=d;
   ldWeightToChange=ld;

}
//---------------------------------------------------------------------------
// --------------------- CalcWeight -----------------------------------------
// ---  ��������� ������� ���, ��������� ������ ��� � ������������� ������ --
long double CalcWeight(DWORD dData)
{
tCalibrPoint stFirstPoint;
tCalibrPoint stSecondPoint;
    std::vector<tCalibrPoint>::iterator it=vCalibr.begin();
    // ���� ������ �������, ������ ��������
    if (vCalibr.size()==0) return 0;
    while (it!=vCalibr.end())
    {
        if (dData<=(it->dAdcData))
        {
                stFirstPoint=*it;
                // ���� �� ����� ������ - �� ������� �������� ���� �� ����
                if  (it==vCalibr.begin())  return  stFirstPoint.ldWeight;
                     // ���� ����� ��� ���� ������� �������, ����� ���
                     else
                     {
                       --it;
                       stSecondPoint=*it;
                     }
                break;  // while (it!=vCalibr.end())
        }
        ++it;
    }
    // ���� ���� ������ ������ ������ �������� �������
    // �� ����� ���������, ����� ������� �������.
    if (it== vCalibr.end())
    {
        --it;
        return it->ldWeight;
    }

/* ������� ���������  ������ y=f(x)
 ��� x - ��� ������ � ��� , y - ���
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
//------------ ��������� ������������� ����� �� ������ ----------------------
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
//------------ �������� ��� ���������� --------------------------------------
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
//------------ ������ ���������   -------------------------------------------
//---------- ��������� ���� �� ���� � ������������� ������-------------------

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
                 vCalibr.push_back(stNewPoint);   // ��������� �����
                i++;
                
        }
        std::sort(vCalibr.begin(),vCalibr.end(),PointCompare); // � ����������������� ������
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



