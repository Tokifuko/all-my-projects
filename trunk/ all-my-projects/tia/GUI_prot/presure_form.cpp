//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "ms5803-14ba.h"
#include "presure_form.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPresureForm *PresureForm;
DWORD dwCoef[8];
DWORD dwAdc1;
DWORD dwAdc2;

AnsiString s;

void PushCoef_0 (DWORD dData)
{
        dwCoef[0]=dData;
        PresureForm->LabelCoef_0->Caption=s.sprintf("Coef 0 = %d",dData);
}
void PushCoef_1 (DWORD dData)
{
        dwCoef[1]=dData;
        PresureForm->LabelCoef_1->Caption=s.sprintf("Coef 1 = %d",dData);
}
void PushCoef_2 (DWORD dData)
{
        dwCoef[2]=dData;
        PresureForm->LabelCoef_2->Caption=s.sprintf("Coef 2 = %d",dData);
}
void PushCoef_3 (DWORD dData)
{
        dwCoef[3]=dData;
        PresureForm->LabelCoef_3->Caption=s.sprintf("Coef 3 = %d",dData);
}
void PushCoef_4 (DWORD dData)
{
        dwCoef[4]=dData;
        PresureForm->LabelCoef_4->Caption=s.sprintf("Coef 4 = %d",dData);
}
void PushCoef_5 (DWORD dData)
{
        dwCoef[5]=dData;
        PresureForm->LabelCoef_5->Caption=s.sprintf("Coef 5 = %d",dData);
}
void PushCoef_6 (DWORD dData)
{
        dwCoef[6]=dData;
        PresureForm->LabelCoef_6->Caption=s.sprintf("Coef 6 = %d",dData);
}
void PushCoef_7 (DWORD dData)
{
        dwCoef[7]=dData;
        PresureForm->LabelCoef_7->Caption=s.sprintf("Coef 7 = %d",dData);
}
void PushAdc_1 (DWORD dData)
{
        dwAdc1=dData;
        PresureForm->LabelAdc_1->Caption=s.sprintf("Adc 1 = %d",dData);
        PresureForm->Calculation();
}
void PushAdc_2 (DWORD dData)
{
        dwAdc2=dData;
        PresureForm->LabelAdc_2->Caption=s.sprintf("Adc 2 = %d",dData);
        PresureForm->Calculation();
}

//---------------------------------------------------------------------------
__fastcall TPresureForm::TPresureForm(TComponent* Owner)
        : TForm(Owner)
{
}

void TPresureForm::Calculation (void)
{
   CalibrationData CoefData;
   CoefData.C1=  dwCoef[1];
   CoefData.C2=  dwCoef[2];
   CoefData.C3=  dwCoef[3];
   CoefData.C4=  dwCoef[4];
   CoefData.C5=  dwCoef[5];
   CoefData.C6=  dwCoef[6];

   MeasurementData AdcData;
   AdcData.D1  =dwAdc1;
   AdcData.D2  =dwAdc2;

   CalculatedValues values;

   calculateTemperature(CoefData, AdcData, &values);
    calculateTemperatureCompensatedPressure(CoefData, AdcData, &values);
   // doSecondOrderTemperatureCompensation(&values);

    LabeldT->Caption=s.sprintf("dT %i\n", values.dT);
    LabelTemp->Caption=s.sprintf("TEMP %i\n", values.TEMP);
    LabelOff->Caption=s.sprintf("OFF %Ld\n", values.OFF);
    LabelSens->Caption=s.sprintf("SENS %Ld\n", values.SENS);
    LabelPres->Caption=s.sprintf("Pres %i\n", values.P);

}

//---------------------------------------------------------------------------
void __fastcall TPresureForm::Button1Click(TObject *Sender)
{
    CalibrationData CB_DATA = {46546,42845,29751,29457,32745,29059}; //static values from data sheet
    MeasurementData MM_DATA = {4311550,8387300}; //static values from data sheet
    CalculatedValues values;

    calculateTemperature(CB_DATA, MM_DATA, &values);
    calculateTemperatureCompensatedPressure(CB_DATA, MM_DATA, &values);
    doSecondOrderTemperatureCompensation(&values);

    LabeldT->Caption=s.sprintf("dT %i\n", values.dT);
    LabelTemp->Caption=s.sprintf("TEMP %i\n", values.TEMP);
    LabelOff->Caption=s.sprintf("OFF %lld\n", values.OFF);
    LabelSens->Caption=s.sprintf("SENS %lld\n", values.SENS);
    LabelPres->Caption=s.sprintf("Pres %i\n", values.P);

    if(values.dT == 4580 && values.TEMP == 2015 && values.OFF == 2808943914ULL && values.SENS == 1525751591ULL && values.P == 10005) {
        LableStatus->Caption=s.sprintf("Calculated values are correct.\n");
    } else {
        LableStatus->Caption=s.sprintf("Check algorithm. Values are incorrect.\n");
    }
}
//---------------------------------------------------------------------------

