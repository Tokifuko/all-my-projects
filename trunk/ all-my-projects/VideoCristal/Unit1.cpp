//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
myRecord_t myRecord[255];
void ListReFill(void);
void SaveFile(void);
void LoadFile(void);

unsigned int iRecCounter=0;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{

LPTSTR szCmdline = _tcsdup(TEXT("C:\Program Files (x86)\Webteh\BSplayerPro\bsplayer.exe"));
        ShellExecute(NULL,NULL,"C:\\Program Files (x86)\\Webteh\\BSplayerPro\\bsplayer.exe","C:\\1.avi -fs",NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::btAddRecordClick(TObject *Sender)
{
        myRecord[iRecCounter].iCardID=Edit1->Text.ToInt();
        myRecord[iRecCounter].iVideoLength=Edit2->Text.ToInt();

        char *pchTemp;
        AnsiString asTempString;
        asTempString=Edit3->Text;   // иначе ошибка восми символов
        pchTemp= asTempString.c_str();
        strcpy(myRecord[iRecCounter].chVideoPach,pchTemp);
        iRecCounter++;
        ListReFill();
}
//---------------------------------------------------------------------------
void ListReFill(void)
{
        for(int i = Form1->ListBox1->Items->Count-1; i >= 0; i--) Form1->ListBox1->Items->Delete(i);


        AnsiString asNewString;
        for (int i=0; i<iRecCounter; i++)
        {
            asNewString=(AnsiString)myRecord[i].iCardID;
            asNewString+="    ";
            asNewString+=(AnsiString)myRecord[i].iVideoLength;
            asNewString+="    ";
            asNewString+=(AnsiString)myRecord[i].chVideoPach;
            Form1->ListBox1->Items->Add(asNewString);
        }

}

void __fastcall TForm1::btDelRecordClick(TObject *Sender)
{
        int iCurentItem= ListBox1->ItemIndex;
        if (iRecCounter==0) return;
        iRecCounter--;
        for (int i=iCurentItem; i<iRecCounter; i++)
        {
           myRecord[i]=myRecord[i+1];
        }
        ListReFill();
}
//---------------------------------------------------------------------------
void SaveFile(void)
{
        FILE *f=fopen( "data.dat", "wb" );
        if (f==NULL) return;
        for (int i=0; i<iRecCounter; i++)
        {
                fwrite(&myRecord[i],sizeof(myRecord_t),1,f);
        }
        fclose(f);
        ListReFill();
}

void LoadFile(void)
{
        FILE *f=fopen( "data.dat", "rb" );
        if (f==NULL) return;
        iRecCounter=0;
        myRecord_t tTempRec;
        while ( fread(&tTempRec,sizeof(myRecord_t),1,f))
        {
                myRecord[iRecCounter]=tTempRec;
                iRecCounter++;
        }
       fclose(f);
       ListReFill();
}
void __fastcall TForm1::btSaveDataClick(TObject *Sender)
{
   SaveFile();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btLoadDataClick(TObject *Sender)
{
        LoadFile();
        ListReFill();
}
//---------------------------------------------------------------------------

