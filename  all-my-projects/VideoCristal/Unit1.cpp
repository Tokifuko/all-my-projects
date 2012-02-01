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

#define BUFSIZE 1

#define PSH_VIDEO_LEN           60 // ������ ����-����� � ��������
#define STATE_PLAY_PSH          1
#define STATE_PLAY_VIDEO        2


TForm1 *Form1;
HANDLE hPort;
myRecord_t myRecord[255];
void ListReFill(void);
void SaveFile(void);
void LoadFile(void);
void COM_Search(void);
bool ConfigCOM(HANDLE COMport, int ReadTimeout);
void NewCardFound(AnsiString sNewID);
void CurCardLost(void);
void StartPlay (AnsiString sVideoFile, int iVideoLen);

int iStateVideoPlay=STATE_PLAY_PSH;
AnsiString sRecString;

unsigned int iRecCounter=0;
bool bGetCardFlag=false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void __fastcall TForm1::btAddRecordClick(TObject *Sender)
{
        char *pchTemp;
        AnsiString asTempString;
        Edit1->Text=Edit1->Text.SubString(1,CARD_ID_LEN); // ��� ������� ������ �� 14 �������� (CARD_ID_LEN)
        asTempString= Edit1->Text;
        pchTemp=asTempString.c_str();
        strcpy(myRecord[iRecCounter].chCardID,pchTemp);

        myRecord[iRecCounter].iVideoLength=Edit2->Text.ToInt();

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
            asNewString=(AnsiString)myRecord[i].chCardID;
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
         CloseHandle(COMport);
         Form1->lComChoise->Font->Color = clRed;
         Form1->lComChoise->Caption =  "�� ������� ������� DCB";
         return FALSE;
      }

       //������������� ��������� DCB
       dcb.BaudRate = 128000;                                 //����� �������� �������� 115200 ���
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
                Form1->lComChoise->Font->Color = clRed;
                Form1->lComChoise->Caption =  "A device attached to the system is not functioning.";
           }
           else
           {
                Form1->lComChoise->Font->Color = clRed;
                Form1->lComChoise->Caption =  "�� ������� ���������� DCB";
           }
           CloseHandle(COMport);

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
            CloseHandle(COMport);
            Form1->lComChoise->Font->Color = clRed;
            Form1->lComChoise->Caption = "�� ������� ���������� ����-����";
            return FALSE;
        }

         //���������� ������� �������� ����� � ��������
         if (!SetupComm(COMport,2000,2000))
        {
            CloseHandle(COMport);
            Form1->lComChoise->Font->Color = clRed;
            Form1->lComChoise->Caption = "�� ������� ���������� ������� �����-��������";
            return FALSE;
        }

        //�������� ����������� ����� �����
        if (!PurgeComm(COMport, PURGE_RXCLEAR))
        {
            CloseHandle(COMport);
            Form1->lComChoise->Font->Color = clRed;
            Form1->lComChoise->Caption = "�� ������� �������� ����������� ����� �����";
            return FALSE;
        }
 return TRUE;
}
void __fastcall TForm1::btOpenPortClick(TObject *Sender)
{
    String portname;
    unsigned char bufrd[BUFSIZE];
    DWORD temp;

    Form1->lComChoise->Caption = "���������...";

    Form1->Repaint();

    portname = Form1->cbPort->Text;	//�������� ��� ���������� �����


     hPort = ::CreateFile(portname.c_str(),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                0,
                                OPEN_EXISTING,
                                0,
                                0);
     if(hPort == INVALID_HANDLE_VALUE)
     {
          //DWORD dwError = GetLastError();
          //if(dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE)
          Form1->lComChoise->Caption = "ERROR, �� ������� ������� ����";
          Form1->lComChoise->Font->Color = clRed;
          Form1->lComChoise->Caption = "������ ������������ ����������";
     }
     else
     {
        if (ConfigCOM(hPort, 500))
        {       Form1->lComChoise->Font->Color = clGreen;
                Form1->lComChoise->Caption = "���������� �����������";
        }
        else
        {
                //Form1->lComChoise->Font->Color = clRed;
                //Form1->lComChoise->Caption = "������ ������������ ����������";
                CloseHandle(hPort);
        }
     }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::btClosePortClick(TObject *Sender)
{
        CloseHandle(hPort);
        Form1->lComChoise->Font->Color = clGreen;
        Form1->lComChoise->Caption = "���� ������";
}
//---------------------------------------------------------------------------

// ��� ������ ������ ������
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        char ch;
        DWORD temp;
        if (!ReadFile(hPort, &ch, 1, &temp, NULL)) return;    // ������ �����������
        if (ch!='\r') sRecString+=ch;                        // � ���� ����� ������
        else
        {
                int index =sRecString.Pos("Card Out");  // ������ ��������� � ���������� �����
                if (index!=0)      // �� ����� ����� ����� ��� ������ ��� ���. ���� ��������� ��������
                {       mLog->Lines->Add("get Card Out");
                        CurCardLost();
                }
                index = sRecString.Pos("CurCard");    // CurCard - ��� ������� �����
                if (index==0)
                {
                       sRecString="";
                       return;
                }
                AnsiString sNewCardID;
                sNewCardID=sRecString.SubString(index+8,sRecString.Length()-index-7);
                sRecString="";
                if (sNewCardID!=lCurCardID->Caption) NewCardFound(sNewCardID);
                bGetCardFlag=true;
        }
}
//---------------------------------------------------------------------------

// ��� ������ ���������� �����
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
   if (!bGetCardFlag)
   {
        if (lCurCardID->Caption=="����� �� �������" ) return;
        CurCardLost();
   }
   bGetCardFlag=false;
}
//---------------------------------------------------------------------------

void NewCardFound(AnsiString sNewID)
{
        Form1->lCurCardID->Caption=sNewID;
        Form1->mLog->Lines->Add("���������� ����� ����� ID="+sNewID);
        AnsiString asTemp;
        char *pch;
        int index;
        Form1->lCurVideoLength->Caption="������ �� �������";
        Form1->lCurCardFilePach->Caption="������ �� �������";
        for (int i=0; i<iRecCounter; i++)
        {
                pch=sNewID.c_str();
                index=strcmp(myRecord[i].chCardID, pch);
                if (index==0)     //A zero value indicates that both strings are equal.
                {
                        Form1->lCurVideoLength->Caption=(AnsiString)myRecord[i].iVideoLength;
                        Form1->lCurCardFilePach->Caption=(AnsiString)myRecord[i].chVideoPach;
                        if (Form1->cbStartPlay->Checked)
                        {
                                StartPlay((AnsiString)myRecord[i].chVideoPach,myRecord[i].iVideoLength);
                                iStateVideoPlay=STATE_PLAY_VIDEO;
                        }
                }
        }
}
void CurCardLost(void)
{
        Form1->lCurCardID->Caption="����� �� �������" ;
        Form1->mLog->Lines->Add("����� ���������");
        Form1->lCurVideoLength->Caption="����� �� �������";
        Form1->lCurCardFilePach->Caption="����� �� �������";
        bGetCardFlag=false;
        if (iStateVideoPlay==STATE_PLAY_VIDEO)
        {
                StartPlay(Form1->lPshFile->Caption,PSH_VIDEO_LEN);
                iStateVideoPlay=STATE_PLAY_PSH;
        }
}
void __fastcall TForm1::btGetCardIDClick(TObject *Sender)
{
        if  (lCurCardID->Caption!= "����� �� �������") Edit1->Text=lCurCardID->Caption;
}
//---------------------------------------------------------------------------

void StartPlay (AnsiString sVideoFile, int iVideoLen)
{
        sVideoFile+=" -fs";
        AnsiString stTemp=Form1->lBSPlayerPach->Caption;
        char* pchBSPlayer=stTemp.c_str();
        char* pchFile=sVideoFile.c_str();
        ShellExecute(NULL,NULL,pchBSPlayer,pchFile,NULL,SW_SHOWNORMAL);
        Form1->Timer3->Enabled=false;
        Form1->Timer3->Interval=iVideoLen*1000;
        Form1->Timer3->Enabled=true;

}



void __fastcall TForm1::bfFindBSPlayerClick(TObject *Sender)
{
        if (odFindBSPlayer->Execute()) lBSPlayerPach->Caption=odFindBSPlayer->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btFindVideoFileClick(TObject *Sender)
{
        if (odFindVideoFile->Execute())Edit3->Text=odFindVideoFile->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btFindPshFileClick(TObject *Sender)
{
       if (odFindPshFile->Execute()) lPshFile->Caption=odFindPshFile->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
        if (Form1->cbStartPlay->Checked) StartPlay(lPshFile->Caption,PSH_VIDEO_LEN);
        iStateVideoPlay=STATE_PLAY_PSH;
}
//---------------------------------------------------------------------------

