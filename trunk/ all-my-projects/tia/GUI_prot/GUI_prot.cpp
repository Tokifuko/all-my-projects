//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("main_form.cpp", MainForm);
USEFORM("com_form.cpp", ComForm);
USEFORM("chart_form.cpp", ChartForm);
USEFORM("weigth_form.cpp", WeightForm);
USEFORM("presure_form.cpp", PresureForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TComForm), &ComForm);
                 Application->CreateForm(__classid(TChartForm), &ChartForm);
                 Application->CreateForm(__classid(TWeightForm), &WeightForm);
                 Application->CreateForm(__classid(TPresureForm), &PresureForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
