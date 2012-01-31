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
void COM_Search(void);
bool ConfigCOM(HANDLE COMport, int ReadTimeout);

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

//---------------------------------------------------------------------------
// Поиск COM портов с помощью перебора
//---------------------------------------------------------------------------

void COM_Search()
{
     Form1->cbPort->Items->Clear();

     for (UINT i=1; i<256; i++)
        {
                char sPort[10];
                //sprintf(sPort,"\\\\.\\COM%d", i);
                sprintf(sPort,"COM%d", i);
                BOOL bSuccess = FALSE;
                HANDLE hPort = ::CreateFile(sPort,
                                         GENERIC_READ | GENERIC_WRITE,
                                         0,
                                         0,
                                         OPEN_EXISTING,
                                         0,
                                         0);
                if(hPort == INVALID_HANDLE_VALUE)
                {
                        DWORD dwError = GetLastError();
                        if(dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE)
                                bSuccess = TRUE;
                }
                else
                {
                        bSuccess = TRUE;
                        CloseHandle(hPort);
                } // if(hPort == INVALID_HANDLE_VALUE)

                if(bSuccess)    Form1->cbPort->Items->Add(sPort);

         } // for (UINT i=1; i<256; i++)
}
void __fastcall TForm1::cbPortDropDown(TObject *Sender)
{
 COM_Search();
}
//---------------------------------------------------------------------------
bool ConfigCOM(HANDLE COMport, int ReadTimeout)
{
      DCB dcb;
      COMMTIMEOUTS timeouts;  //структура для установки таймаутов


      dcb.DCBlength = sizeof(DCB); 	// в первое поле структуры DCB
                                        // необходимо занести её длину,
                                        // она будет использоваться функциями
                                        // настройки порта для контроля
                                        // корректности структуры

      //считать структуру DCB из порта
      if(!GetCommState(COMport, &dcb))
      {
         //CloseHandle(COMport);
         //Form1->lComChoise->Font->Color = clRed;
         //Form1->lComChoise->Caption =  "Не удалось считать DCB";
         return FALSE;
      }


       //инициализация структуры DCB
       dcb.BaudRate = 115200;                                  //задаём скорость передачи 115200 бод
       dcb.fBinary = TRUE;                                    //включаем двоичный режим обмена
       dcb.fOutxCtsFlow = FALSE;                              //выключаем режим слежения за сигналом CTS (clear-to-send)
       dcb.fOutxDsrFlow = FALSE;                              //выключаем режим слежения за сигналом DSR (data-set-ready)
       dcb.fDtrControl = DTR_CONTROL_DISABLE;                 //отключаем использование линии DTR (data-terminal-ready)
       dcb.fDsrSensitivity = FALSE;                           //отключаем восприимчивость драйвера к состоянию линии DSR
       dcb.fNull = FALSE;                                     //разрешить приём нулевых байтов
       dcb.fRtsControl = RTS_CONTROL_DISABLE;                 //отключаем использование линии RTS
       dcb.fAbortOnError = FALSE;                             //отключаем остановку всех операций чтения/записи при ошибке
       dcb.ByteSize = 8;                                      //задаём 8 бит в байте
       dcb.Parity = NOPARITY;                                 //отключаем проверку чётности
       dcb.StopBits = ONESTOPBIT;                             //задаём один стоп-бит

        //загрузить структуру DCB в порт
        if(!SetCommState(COMport, &dcb))	//если не удалось - закрыть порт и
                                                // вывести сообщение об ошибке в строке состояния
        {
           if ((GetLastError())==ERROR_GEN_FAILURE)
           {
                //Form1->lComChoise->Font->Color = clRed;
                //Form1->lComChoise->Caption =  "A device attached to the system is not functioning.";
           }
           else
           {
                //Form1->lComChoise->Font->Color = clRed;
                //Form1->lComChoise->Caption =  "Не удалось установить DCB";
           }
           //CloseHandle(COMport);

           return FALSE;
        }

        //установить таймауты
        timeouts.ReadIntervalTimeout = 0;	 	//таймаут между двумя символами
        timeouts.ReadTotalTimeoutMultiplier = 0;	//общий таймаут операции чтения
        timeouts.ReadTotalTimeoutConstant = ReadTimeout; //константа для общего таймаута операции чтения
        timeouts.WriteTotalTimeoutMultiplier = 0;       //общий таймаут операции записи
        timeouts.WriteTotalTimeoutConstant = 2000;         //константа для общего таймаута операции записи

        //записать структуру таймаутов в порт
        if(!SetCommTimeouts(COMport, &timeouts))	//если не удалось - закрыть порт и вывести сообщение об ошибке в строке состояния
        {
            //CloseHandle(COMport);
            //Form1->lComChoise->Font->Color = clRed;
            //Form1->lComChoise->Caption = "Не удалось установить тайм-ауты";
            return FALSE;
        }

         //установить размеры очередей приёма и передачи
         if (!SetupComm(COMport,2000,2000))
        {
            //CloseHandle(COMport);
            //Form1->lComChoise->Font->Color = clRed;
            //Form1->lComChoise->Caption = "Не удалось установить очереди приёма-передачи";
            return FALSE;
        }

        //очистить принимающий буфер порта
        if (!PurgeComm(COMport, PURGE_RXCLEAR))
        {
            //CloseHandle(COMport);
            //Form1->lComChoise->Font->Color = clRed;
            //Form1->lComChoise->Caption = "Не удалось очистить принимающий буфер порта";
            return FALSE;
        }
 return TRUE;
}
