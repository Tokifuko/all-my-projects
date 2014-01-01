//=============================================================================
//................................. � ��������� ...............................
//.............................................................................
//....... ��������� ������������� ��� ������������ ������ � COM-������ ........
//....... � ������� ������� � �������������� ����������� �������� .............
//.............................................................................
//...... ������������ ������ TThread ��� ������� Resume() � Suspend() .........
//.............................................................................
//=============================================================================

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <io.h>         //��� ������ � �������
#include <fcntl.h>      //��� ������ � �������
#include <sys\stat.h>   //��� ������ � �������
#include <stdio>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PERFGRAP"
#pragma resource "*.dfm"
TForm1 *Form1;


//=============================================================================
//..................... ���������� ���������� ���������� ......................
//=============================================================================

#define BUFSIZE 255     //������� ������

unsigned char bufrd[BUFSIZE], bufwr[BUFSIZE]; //������� � ���������� ������

//---------------------------------------------------------------------------

HANDLE COMport;		//���������� �����

//��������� OVERLAPPED ���������� ��� ����������� ��������, ��� ���� ��� �������� ������ � ������ ����� �������� ������ ���������
//��� ��������� ���������� �������� ���������, ����� ��������� �� ����� �������� ���������
OVERLAPPED overlapped;		//����� ������������ ��� �������� ������ (��. ����� ReadThread)
OVERLAPPED overlappedwr;       	//����� ������������ ��� �������� ������ (��. ����� WriteThread)

//---------------------------------------------------------------------------

int handle;             	//���������� ��� ������ � ������ � ������� ���������� <io.h>

//---------------------------------------------------------------------------

bool fl=0;	//����, ����������� �� ���������� �������� ������ (1 - �������, 0 - �� �������)
unsigned int iChartCounter=0;
unsigned int iChartCounter_1=0;
unsigned int iChartCounter_2=0;

unsigned long counter;	//������� �������� ������, ���������� ��� ������ �������� �����


//=============================================================================
//.............................. ���������� ������� ...........................
//=============================================================================

void COMOpen(void);             //������� ����
void COMClose(void);            //������� ����


//=============================================================================
//.............................. ���������� ������� ...........................
//=============================================================================

//---------------------------------------------------------------------------

//����� ��� ������ ������������������ ������ �� COM-����� � �����
class ReadThread : public TThread
{
 private:
        void __fastcall Printing();	//����� �������� ������ �� ����� � � ����
 protected:
        void __fastcall Execute();	//�������� ������� ������
 public:
        __fastcall ReadThread(bool CreateSuspended);	//����������� ������
};

//---------------------------------------------------------------------------

//����� ��� ������ ������������������ ������ �� ������ � COM-����
class WriteThread : public TThread
{
private:
 	void __fastcall Printing();	//����� ��������� �� �����
protected:
        void __fastcall Execute();      //�������� ������� ������
public:
        __fastcall WriteThread(bool CreateSuspended);	//����������� ������
};

//---------------------------------------------------------------------------


//=============================================================================
//.............................. ���������� ������� ...........................
//=============================================================================

//-----------------------------------------------------------------------------
//............................... ����� ReadThead .............................
//-----------------------------------------------------------------------------

ReadThread *reader;     //������ ������ ReadThread

//---------------------------------------------------------------------------

//����������� ������ ReadThread, �� ��������� ������
__fastcall ReadThread::ReadThread(bool CreateSuspended) : TThread(CreateSuspended)
{}

//---------------------------------------------------------------------------

//������� ������� ������, ��������� ���� ������ �� COM-�����
void __fastcall ReadThread::Execute()
{
 COMSTAT comstat;		//��������� �������� ��������� �����, � ������ ��������� ������������ ��� ����������� ���������� �������� � ���� ������
 DWORD btr, temp, mask, signal;	//���������� temp ������������ � �������� ��������

 overlapped.hEvent = CreateEvent(NULL, true, true, NULL);	//������� ���������� ������-������� ��� ����������� ��������
 SetCommMask(COMport, EV_RXCHAR);                   	        //���������� ����� �� ������������ �� ������� ����� ����� � ����
 while(!Terminated)						//���� ����� �� ����� �������, ��������� ����
  {
   WaitCommEvent(COMport, &mask, &overlapped);               	//������� ������� ����� ����� (��� � ���� ������������� ��������)
   signal = WaitForSingleObject(overlapped.hEvent, INFINITE);	//������������� ����� �� ������� �����
   if(signal == WAIT_OBJECT_0)				        //���� ������� ������� ����� ���������
    {
     if(GetOverlappedResult(COMport, &overlapped, &temp, true)) //���������, ������� �� ����������� ������������� �������� WaitCommEvent
      if((mask & EV_RXCHAR)!=0)					//���� ��������� ������ ������� ������� �����
       {
         btr=1;
         while (btr!=0)
         {
          ClearCommError(COMport, &temp, &comstat);		//����� ��������� ��������� COMSTAT
          btr = comstat.cbInQue;                          	//� �������� �� �� ���������� �������� ������
          if(btr)                         			//���� ������������� ���� ����� ��� ������
          {
           ReadFile(COMport, bufrd, btr, &temp, &overlapped);     //��������� ����� �� ����� � ����� ���������
           counter+=btr;                                          //����������� ������� ������
           Synchronize(Printing);                      		//�������� ������� ��� ������ ������ �� ����� � � ����
          }
       }
       }
    }
  }
 CloseHandle(overlapped.hEvent);		//����� ������� �� ������ ������� ������-�������
}

//---------------------------------------------------------------------------

//������� �������� ����� �� ����� � � ���� (���� ��������)
void __fastcall ReadThread::Printing()
{
 int iPosStr;
 int iSign;
 DWORD  i;
 long lTemp;
 float fTemp;
 int iPosChar;
 char* pch;
 AnsiString sOld, sNew, sBuf, sHead;

 pch=bufrd;
 while (*pch) // �������� � ������� �����������, ���� ��������� ����� ������
                // ��� ��� \n ����� ������ � ��������� ������, � �� � ����
 {
      iPosStr=Form1->Memo1->Lines->Count;
      iPosStr--;
      sOld=Form1->Memo1->Lines->Strings[iPosStr];
      Form1->Memo1->Lines->Strings[iPosStr]=sOld+*pch;
      if (*pch=='\n')
      {
        sBuf=Form1->Memo1->Lines->Strings[iPosStr];
 // **************** ������ ��������� � ���   **********************************
        sHead="ACD_VAL=";        // ��� ������ ��������� �� ��������� ���
        iPosChar=sBuf.Pos(sHead);
        if (iPosChar!=0)
        {
                sBuf=sBuf.SubString(iPosChar+sHead.Length(),sBuf.Length()-iPosChar-sHead.Length()-1);
                i=sBuf.ToDouble();
                Form1->Series2->AddXY(iChartCounter++,i/100 ,"",clRed);
                sBuf.printf("%d \n", i);
                Form1->Memo1->Lines->Add(sBuf); //������� �������� ������ � Memo
        }  // if (iPosChar!=0)

 // **************** ������ ��������� �� ��������   **********************************
        sHead="CALIPERS_VAL=";        // ��� ������ ���������
        iPosChar=sBuf.Pos(sHead);
        if (iPosChar!=0)
        {
                sBuf=sBuf.SubString(iPosChar+sHead.Length(),sBuf.Length()-iPosChar-sHead.Length()-1);
                lTemp=sBuf.ToDouble();
                fTemp=lTemp;
                fTemp=fTemp/100;

                Form1->Series3->AddXY(iChartCounter_2++,fTemp ,"",clGreen);
                sBuf.printf(" %f \n", fTemp);
                Form1->Memo1->Lines->Add(sBuf); //������� �������� ������ � Memo
                 Form1->lCalipersData->Caption=sBuf;
        }  // if (iPosChar!=0)

        Form1->Memo1->Lines->Add("");   // ������ ����� ������
      } //if (*pch=='\n')
      pch++;

 }

 Form1->StatusBar1->Panels->Items[2]->Text = "����� ������� " + IntToStr(counter) + " ����";	//������� ������� � ������ ���������

 if(Form1->CheckBox3->Checked == true)  //���� ������� ����� ������ � ����
  {
   write(handle, bufrd, strlen(bufrd)); //�������� � ���� ������ �� �������� ������
  }
 memset(bufrd, 0, BUFSIZE);	        //�������� ����� (����� ������ �� ������������� ���� �� �����)
}

//---------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//............................... ����� WriteThead ............................
//-----------------------------------------------------------------------------

WriteThread *writer;     //������ ������ WriteThread

//---------------------------------------------------------------------------

//����������� ������ WriteThread, �� ��������� ������
__fastcall WriteThread::WriteThread(bool CreateSuspended) : TThread(CreateSuspended)
{}

//---------------------------------------------------------------------------

//������� ������� ������, ��������� �������� ������ �� ������ � COM-����
void __fastcall WriteThread::Execute()
{
 DWORD temp, signal;	//temp - ����������-��������

 overlappedwr.hEvent = CreateEvent(NULL, true, true, NULL);   	  //������� �������
 WriteFile(COMport, bufwr, strlen(bufwr), &temp, &overlappedwr);  //�������� ����� � ���� (������������� ��������!)
 signal = WaitForSingleObject(overlappedwr.hEvent, INFINITE);	  //������������� �����, ���� �� ���������� ������������� �������� WriteFile
 if((signal == WAIT_OBJECT_0) && (GetOverlappedResult(COMport, &overlappedwr, &temp, true))) fl = true; //���� �������� ����������� �������, ���������� ��������������� ������
 else fl = false;
 Synchronize(Printing);	//������� ��������� �������� � ������ ���������
 CloseHandle(overlappedwr.hEvent);	//����� ������� �� ������ ������� ������-�������
}

//---------------------------------------------------------------------------

//����� ��������� �������� ������ �� �����
void __fastcall WriteThread::Printing()
{
 if(!fl)	//��������� ��������� ������
  {
   Form1->StatusBar1->Panels->Items[0]->Text  = "������ ��������";
   return;
  }
 Form1->StatusBar1->Panels->Items[0]->Text  = "�������� ������ �������";
}

//---------------------------------------------------------------------------


//=============================================================================
//............................. �������� ����� ................................
//=============================================================================

//---------------------------------------------------------------------------

//����������� �����, ������ � �� ����������� ������������� ��������� �����
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
 //������������� ��������� ����� ��� ������� ���������
 Form1->Label5->Enabled = false;
 Form1->Label6->Enabled = false;
 Form1->Button1->Enabled = false;
 Form1->CheckBox1->Enabled = false;
 Form1->CheckBox2->Enabled = false;
}

//---------------------------------------------------------------------------

//���������� ������� �� ������ "������� ����"
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
 if(SpeedButton1->Down)
  {
   COMOpen();                   //���� ������ ������ - ������� ����

   //��������/�������� �������� �� �����
   Form1->ComboBox1->Enabled = false;
   Form1->ComboBox2->Enabled = false;
   Form1->Button1->Enabled = true;
   Form1->CheckBox1->Enabled = true;
   Form1->CheckBox2->Enabled = true;

   Form1->SpeedButton1->Caption = "������� ����";	//������� ������� �� ������

   counter = 0;	//���������� ������� ������

   //���� ���� �������� ������ DTR � RTS, ���������� ��� ����� � �������
   Form1->CheckBox1Click(Sender);
   Form1->CheckBox2Click(Sender);
  }

 else
  {
   COMClose();                  //���� ������ ������ - ������� ����

   Form1->SpeedButton1->Caption = "������� ����";	//������� ������� �� ������
   Form1->StatusBar1->Panels->Items[0]->Text = "";	//�������� ������ ������� ������ ���������

   //��������/�������� �������� �� �����
   Form1->ComboBox1->Enabled = true;
   Form1->ComboBox2->Enabled = true;
   Form1->Button1->Enabled = false;
   Form1->CheckBox1->Enabled = false;
   Form1->CheckBox2->Enabled = false;
  }
}

//---------------------------------------------------------------------------

//���������� �������� �����
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
 if(reader)reader->Terminate(); 	//��������� ����� ������ �� �����, �������� if(reader) �����������, ����� ��������� ������
 if(writer)writer->Terminate();         //��������� ����� ������ � ����, �������� if(writer) �����������, ����� ��������� ������
 if(COMport)CloseHandle(COMport);       //������� ����
 if(handle)close(handle);               //������� ����, � ������� ������ ������ ����������� ������

}
//---------------------------------------------------------------------------

//������� "��������� � ����"
void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
 if(Form1->CheckBox3->Checked)		//���� ������� ��������
  {
   //������������ ��������������� �������� �� �����
   Form1->Label5->Enabled = true;
   Form1->Label6->Enabled = true;

   //������� ��������� ������ � ���� � ������ ���������
   Form1->StatusBar1->Panels->Items[1]->Text = "����� � ����!";
  }

 else   				//���� ������� ���������
  {
   //��������� ��������������� �������� �� �����
   Form1->Label5->Enabled = false;
   Form1->Label6->Enabled = false;

   //������ ��������� ������ � ���� �� ������ ���������
   Form1->StatusBar1->Panels->Items[1]->Text = "";
  }

}
//---------------------------------------------------------------------------

//������ "��������"
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 memset(bufwr,0,BUFSIZE);			//�������� ����������� ���������� �����, ����� ������ �� ������������� ���� �� �����
 PurgeComm(COMport, PURGE_TXCLEAR);             //�������� ���������� ����� �����
 strcpy(bufwr,Form1->Edit1->Text.c_str());      //������� � ����������� ���������� ����� ������ �� Edit1 

 writer = new WriteThread(false);               //������� � ������������ ����� ������ ������ � ����
 writer->FreeOnTerminate = true;                //���������� ��� ��������, ����� ����� ������������� ����������� ����� ����������

}

//---------------------------------------------------------------------------

//������ "�������� ����"
void __fastcall TForm1::Button3Click(TObject *Sender)
{
 Form1->Memo1->Clear();	//�������� Memo1
}

//---------------------------------------------------------------------------

//������� "DTR"
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
 //���� ����������� - ���������� ����� DTR � �������, ����� - � ����
 if(Form1->CheckBox1->Checked) EscapeCommFunction(COMport, SETDTR);
 else EscapeCommFunction(COMport, CLRDTR);
}

//---------------------------------------------------------------------------

//������� "RTS"
void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
 //���� ����������� - ���������� ����� RTS � �������, ����� - � ����
 if(Form1->CheckBox2->Checked) EscapeCommFunction(COMport, SETRTS);
 else EscapeCommFunction(COMport, CLRRTS);
}

//---------------------------------------------------------------------------

//=============================================================================
//........................... ���������� ������� ..............................
//=============================================================================

//---------------------------------------------------------------------------

//������� �������� � ������������� �����
void COMOpen()
{
 String portname;     	 //��� ����� (��������, "COM1", "COM2" � �.�.)
 DCB dcb;                //��������� ��� ����� ������������� ����� DCB
 COMMTIMEOUTS timeouts;  //��������� ��� ��������� ���������
 
 portname = Form1->ComboBox1->Text;	//�������� ��� ���������� �����

 //������� ����, ��� ����������� �������� ����������� ����� ������� ���� FILE_FLAG_OVERLAPPED
 COMport = CreateFile(portname.c_str(),GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
 //�����:
 // - portname.c_str() - ��� ����� � �������� ����� �����, c_str() ����������� ������ ���� String � ������ � ���� ������� ���� char, ����� ������� �� ������
 // - GENERIC_READ | GENERIC_WRITE - ������ � ����� �� ������/�������
 // - 0 - ���� �� ����� ���� ������������� (shared)
 // - NULL - ���������� ����� �� �����������, ������������ ���������� ������������ �� ���������
 // - OPEN_EXISTING - ���� ������ ����������� ��� ��� ������������ ����
 // - FILE_FLAG_OVERLAPPED - ���� ���� ��������� �� ������������� ����������� ��������
 // - NULL - ��������� �� ���� ������� �� ������������ ��� ������ � �������

 if(COMport == INVALID_HANDLE_VALUE)            //���� ������ �������� �����
  {
   Form1->SpeedButton1->Down = false;           //������ ������
   Form1->StatusBar1->Panels->Items[0]->Text = "�� ������� ������� ����";       //������� ��������� � ������ ���������
   return;
  }

 //������������� �����

 dcb.DCBlength = sizeof(DCB); 	//� ������ ���� ��������� DCB ���������� ������� � �����, ��� ����� �������������� ��������� ��������� ����� ��� �������� ������������ ���������

 //������� ��������� DCB �� �����
 if(!GetCommState(COMport, &dcb))	//���� �� ������� - ������� ���� � ������� ��������� �� ������ � ������ ���������
  {
   COMClose();
   Form1->StatusBar1->Panels->Items[0]->Text  = "�� ������� ������� DCB";
   return;
  }

 //������������� ��������� DCB
 dcb.BaudRate = StrToInt(Form1->ComboBox2->Text);       //����� �������� �������� 115200 ���
 dcb.fBinary = TRUE;                                    //�������� �������� ����� ������
 dcb.fOutxCtsFlow = FALSE;                              //��������� ����� �������� �� �������� CTS
 dcb.fOutxDsrFlow = FALSE;                              //��������� ����� �������� �� �������� DSR
 dcb.fDtrControl = DTR_CONTROL_DISABLE;                 //��������� ������������� ����� DTR
 dcb.fDsrSensitivity = FALSE;                           //��������� ��������������� �������� � ��������� ����� DSR
 dcb.fNull = FALSE;                                     //��������� ���� ������� ������
 dcb.fRtsControl = RTS_CONTROL_DISABLE;                 //��������� ������������� ����� RTS
 dcb.fAbortOnError = FALSE;                             //��������� ��������� ���� �������� ������/������ ��� ������
 dcb.ByteSize = 8;                                      //����� 8 ��� � �����
 dcb.Parity = 0;                                        //��������� �������� ��������
 dcb.StopBits = 0;                                      //����� ���� ����-���

 //��������� ��������� DCB � ����
 if(!SetCommState(COMport, &dcb))	//���� �� ������� - ������� ���� � ������� ��������� �� ������ � ������ ���������
  {
   COMClose();
   Form1->StatusBar1->Panels->Items[0]->Text  = "�� ������� ���������� DCB";
   return;
  }

 //���������� ��������
 timeouts.ReadIntervalTimeout = 0;	 	//������� ����� ����� ���������
 timeouts.ReadTotalTimeoutMultiplier = 0;	//����� ������� �������� ������
 timeouts.ReadTotalTimeoutConstant = 0;         //��������� ��� ������ �������� �������� ������
 timeouts.WriteTotalTimeoutMultiplier = 0;      //����� ������� �������� ������
 timeouts.WriteTotalTimeoutConstant = 0;        //��������� ��� ������ �������� �������� ������

 //�������� ��������� ��������� � ����
 if(!SetCommTimeouts(COMport, &timeouts))	//���� �� ������� - ������� ���� � ������� ��������� �� ������ � ������ ���������
  {
   COMClose();
   Form1->StatusBar1->Panels->Items[0]->Text  = "�� ������� ���������� ����-����";
   return;
  }

 //���������� ������� �������� ����� � ��������
 SetupComm(COMport,2000,2000);

 //������� ��� ������� ������������ ���� ��� ������ ����������� ������
 handle = open("test.txt", O_CREAT | O_APPEND | O_BINARY | O_WRONLY, S_IREAD | S_IWRITE);

 if(handle==-1)		//���� ��������� ������ �������� �����
  {
   Form1->StatusBar1->Panels->Items[1]->Text = "������ �������� �����";	//������� ��������� �� ���� � ��������� ������
   Form1->Label6->Hide();                                               //�������� ������� � ������ �����
   Form1->CheckBox3->Checked = false;                                   //�������� � ��������� �������
   Form1->CheckBox3->Enabled = false;
  }
 else { Form1->StatusBar1->Panels->Items[0]->Text = "���� ������ �������"; } //����� ������� � ������ ��������� ��������� �� �������� �������� ����� 

 PurgeComm(COMport, PURGE_RXCLEAR);	//�������� ����������� ����� �����

 reader = new ReadThread(false);	//������� � ��������� ����� ������ ������
 reader->FreeOnTerminate = true;        //���������� ��� �������� ������, ����� �� ������������� ����������� ����� ����������

}

//---------------------------------------------------------------------------

//������� �������� �����
void COMClose()
{
 if(writer)writer->Terminate();		//���� ����� ������ ��������, ��������� ���; �������� if(writer) �����������, ����� ��������� ������
 if(reader)reader->Terminate();         //���� ����� ������ ��������, ��������� ���; �������� if(reader) �����������, ����� ��������� ������
 CloseHandle(COMport);                  //������� ����
 COMport=0;				//�������� ���������� ��� ����������� �����
 close(handle);				//������� ���� ��� ������ ����������� ������
 handle=0;				//�������� ���������� ��� ����������� �����
}

//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
Form1->Series3->Clear();
Form1->Series2->Clear();
}
//---------------------------------------------------------------------------

