//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_form.h"
#include "com_form.h"
#include "math.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define  BUF_SIZE 255
TMainForm *MainForm;
unsigned int i;
DWORD fTenzoBuf[BUF_SIZE];
unsigned int iTenzoCounter=0;
DWORD   dTenzoSpeed =0;
DWORD dUartSpeed=0;

void WriteNewTenzoData (DWORD fTenzo);

void WriteNewTenzoData (DWORD fTenzo)
{
        fTenzoBuf[iTenzoCounter]=fTenzo;
        iTenzoCounter++;
        if (iTenzoCounter==(BUF_SIZE-1)) iTenzoCounter=0;
        dTenzoSpeed++;
        dUartSpeed+=fTenzo;
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
        ComForm->CallBack=WriteNewTenzoData;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::TestTimerTimer(TObject *Sender)
{
    //WriteNewTenzoData( sin(M_PI/10*i) );
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::SpeedMeterTimerTimer(TObject *Sender)
{
        AnsiString s;
        s.sprintf("%d",dTenzoSpeed);
        //s.sprintf("%d",dUartSpeed);
     //LTenzoSpeed->Caption.sprintf("%d",dTenzoSpeed);
     //LTenzoSpeed->Caption.sprintf("%d",dTenzoSpeed);
     LTenzoSpeed->Caption=s;
   dTenzoSpeed=0;
   dUartSpeed=0;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TrackBar1Change(TObject *Sender)
{
TestTimer->Interval=TrackBar1->Position;
}
//---------------------------------------------------------------------------

