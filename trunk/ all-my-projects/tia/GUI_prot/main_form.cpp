//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_form.h"
#include "com_form.h"
#include "chart_form.h"
#include "math.h"
#include "weigth_form.h"
#include "parser_class.h"
#include "presure_form.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define  BUF_SIZE 512
TMainForm *MainForm;
Parser_Class* pcTenzoParser;
Parser_Class* pcCoef_0_Parser;
Parser_Class* pcCoef_1_Parser;
Parser_Class* pcCoef_2_Parser;
Parser_Class* pcCoef_3_Parser;
Parser_Class* pcCoef_4_Parser;
Parser_Class* pcCoef_5_Parser;
Parser_Class* pcCoef_6_Parser;
Parser_Class* pcCoef_7_Parser;
Parser_Class* pcAdc_1_Parser;
Parser_Class* pcAdc_2_Parser;
unsigned int i;


void WriteNewTenzoData (DWORD fTenzo);

void WriteNewTenzoData (DWORD fTenzo)
{
                ChartForm->DataChart(fTenzo);
            WeightForm->PushData(fTenzo);
}

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Button1Click(TObject *Sender)
{
        ComForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TestTimerTimer(TObject *Sender)
{

    float f;
    DWORD d;
    f= i;
    f=(f/100);
    f=(sin(f)*100);
    d=f+65000;
    AnsiString s;
        s.sprintf("Tenzo= %d \n",d);
    pcTenzoParser->ParsString(&s);
    // s.sprintf("Coef_0= %d \n",d);
   // pcCoef_0_Parser->ParsString(&s);
    //pcTenzoParser->AddData(d);
    i++;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedMeterTimerTimer(TObject *Sender)
{
        AnsiString s;
        s.sprintf("%d",pcTenzoParser->dwDataCounter);
        pcTenzoParser->dwDataCounter=0;
        LTenzoSpeed->Caption=s;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TrackBar1Change(TObject *Sender)
{
  TestTimer->Interval=TrackBar1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button2Click(TObject *Sender)
{
   ChartForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ProcessTimerTimer(TObject *Sender)
{
        pcTenzoParser->ProcessData();
        pcCoef_0_Parser->ProcessData();
        pcCoef_1_Parser->ProcessData();
        pcCoef_2_Parser->ProcessData();
        pcCoef_3_Parser->ProcessData();
        pcCoef_4_Parser->ProcessData();
        pcCoef_5_Parser->ProcessData();
        pcCoef_6_Parser->ProcessData();
        pcCoef_7_Parser->ProcessData();
        pcAdc_1_Parser->ProcessData();
        pcAdc_2_Parser->ProcessData();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Button3Click(TObject *Sender)
{
    WeightForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormActivate(TObject *Sender)
{

          pcTenzoParser = new  Parser_Class (WriteNewTenzoData,"Tenzo=");
          pcCoef_0_Parser = new  Parser_Class (PushCoef_0,"Coef_0=");
          pcCoef_1_Parser = new  Parser_Class (PushCoef_1,"Coef_1=");
          pcCoef_2_Parser = new  Parser_Class (PushCoef_2,"Coef_2=");
          pcCoef_3_Parser = new  Parser_Class (PushCoef_3,"Coef_3=");
          pcCoef_4_Parser = new  Parser_Class (PushCoef_4,"Coef_4=");
          pcCoef_5_Parser = new  Parser_Class (PushCoef_5,"Coef_5=");
          pcCoef_6_Parser = new  Parser_Class (PushCoef_6,"Coef_6=");
          pcCoef_7_Parser = new  Parser_Class (PushCoef_7,"Coef_7=");
          pcAdc_1_Parser = new  Parser_Class (PushAdc_1,"Adc_1=");
          pcAdc_2_Parser = new  Parser_Class (PushAdc_2,"Adc_2=");

          //ComForm->pcTenzoParser=pcTenzoParser;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button4Click(TObject *Sender)
{
PresureForm->Show();
}
//---------------------------------------------------------------------------

