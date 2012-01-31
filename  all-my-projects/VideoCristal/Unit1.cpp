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
        asTempString=Edit3->Text;   // ����� ������ ����� ��������
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
// ����� COM ������ � ������� ��������
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
      COMMTIMEOUTS timeouts;  //��������� ��� ��������� ���������


      dcb.DCBlength = sizeof(DCB); 	// � ������ ���� ��������� DCB
                                        // ���������� ������� � �����,
                                        // ��� ����� �������������� ���������
                                        // ��������� ����� ��� ��������
                                        // ������������ ���������

      //������� ��������� DCB �� �����
      if(!GetCommState(COMport, &dcb))
      {
         //CloseHandle(COMport);
         //Form1->lComChoise->Font->Color = clRed;
         //Form1->lComChoise->Caption =  "�� ������� ������� DCB";
         return FALSE;
      }


       //������������� ��������� DCB
       dcb.BaudRate = 115200;                                  //����� �������� �������� 115200 ���
       dcb.fBinary = TRUE;                                    //�������� �������� ����� ������
       dcb.fOutxCtsFlow = FALSE;                              //��������� ����� �������� �� �������� CTS (clear-to-send)
       dcb.fOutxDsrFlow = FALSE;                              //��������� ����� �������� �� �������� DSR (data-set-ready)
       dcb.fDtrControl = DTR_CONTROL_DISABLE;                 //��������� ������������� ����� DTR (data-terminal-ready)
       dcb.fDsrSensitivity = FALSE;                           //��������� ��������������� �������� � ��������� ����� DSR
       dcb.fNull = FALSE;                                     //��������� ���� ������� ������
       dcb.fRtsControl = RTS_CONTROL_DISABLE;                 //��������� ������������� ����� RTS
       dcb.fAbortOnError = FALSE;                             //��������� ��������� ���� �������� ������/������ ��� ������
       dcb.ByteSize = 8;                                      //����� 8 ��� � �����
       dcb.Parity = NOPARITY;                                 //��������� �������� ��������
       dcb.StopBits = ONESTOPBIT;                             //����� ���� ����-���

        //��������� ��������� DCB � ����
        if(!SetCommState(COMport, &dcb))	//���� �� ������� - ������� ���� �
                                                // ������� ��������� �� ������ � ������ ���������
        {
           if ((GetLastError())==ERROR_GEN_FAILURE)
           {
                //Form1->lComChoise->Font->Color = clRed;
                //Form1->lComChoise->Caption =  "A device attached to the system is not functioning.";
           }
           else
           {
                //Form1->lComChoise->Font->Color = clRed;
                //Form1->lComChoise->Caption =  "�� ������� ���������� DCB";
           }
           //CloseHandle(COMport);

           return FALSE;
        }

        //���������� ��������
        timeouts.ReadIntervalTimeout = 0;	 	//������� ����� ����� ���������
        timeouts.ReadTotalTimeoutMultiplier = 0;	//����� ������� �������� ������
        timeouts.ReadTotalTimeoutConstant = ReadTimeout; //��������� ��� ������ �������� �������� ������
        timeouts.WriteTotalTimeoutMultiplier = 0;       //����� ������� �������� ������
        timeouts.WriteTotalTimeoutConstant = 2000;         //��������� ��� ������ �������� �������� ������

        //�������� ��������� ��������� � ����
        if(!SetCommTimeouts(COMport, &timeouts))	//���� �� ������� - ������� ���� � ������� ��������� �� ������ � ������ ���������
        {
            //CloseHandle(COMport);
            //Form1->lComChoise->Font->Color = clRed;
            //Form1->lComChoise->Caption = "�� ������� ���������� ����-����";
            return FALSE;
        }

         //���������� ������� �������� ����� � ��������
         if (!SetupComm(COMport,2000,2000))
        {
            //CloseHandle(COMport);
            //Form1->lComChoise->Font->Color = clRed;
            //Form1->lComChoise->Caption = "�� ������� ���������� ������� �����-��������";
            return FALSE;
        }

        //�������� ����������� ����� �����
        if (!PurgeComm(COMport, PURGE_RXCLEAR))
        {
            //CloseHandle(COMport);
            //Form1->lComChoise->Font->Color = clRed;
            //Form1->lComChoise->Caption = "�� ������� �������� ����������� ����� �����";
            return FALSE;
        }
 return TRUE;
}
