//=============================================================================
//................................. О программе ...............................
//.............................................................................
//....... Программа предназначена для демонстрации работы с COM-портом ........
//....... с помощью потоков с использованием асинхронных операций .............
//.............................................................................
//...... Используются потоки TThread без методов Resume() и Suspend() .........
//.............................................................................
//=============================================================================

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <io.h>         //для работы с файлами
#include <fcntl.h>      //для работы с файлами
#include <sys\stat.h>   //для работы с файлами
#include <stdio>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PERFGRAP"
#pragma resource "*.dfm"
TForm1 *Form1;


//=============================================================================
//..................... объявления глобальных переменных ......................
//=============================================================================

#define BUFSIZE 255     //ёмкость буфера

unsigned char bufrd[BUFSIZE], bufwr[BUFSIZE]; //приёмный и передающий буферы

//---------------------------------------------------------------------------

HANDLE COMport;		//дескриптор порта

//структура OVERLAPPED необходима для асинхронных операций, при этом для операции чтения и записи нужно объявить разные структуры
//эти структуры необходимо объявить глобально, иначе программа не будет работать правильно
OVERLAPPED overlapped;		//будем использовать для операций чтения (см. поток ReadThread)
OVERLAPPED overlappedwr;       	//будем использовать для операций записи (см. поток WriteThread)

//---------------------------------------------------------------------------

int handle;             	//дескриптор для работы с файлом с помощью библиотеки <io.h>

//---------------------------------------------------------------------------

bool fl=0;	//флаг, указывающий на успешность операций записи (1 - успешно, 0 - не успешно)
unsigned int iChartCounter=0;
unsigned int iChartCounter_1=0;
unsigned int iChartCounter_2=0;

unsigned long counter;	//счётчик принятых байтов, обнуляется при каждом открытии порта


//=============================================================================
//.............................. объявления функций ...........................
//=============================================================================

void COMOpen(void);             //открыть порт
void COMClose(void);            //закрыть порт


//=============================================================================
//.............................. объявления потоков ...........................
//=============================================================================

//---------------------------------------------------------------------------

//поток для чтения последовательности байтов из COM-порта в буфер
class ReadThread : public TThread
{
 private:
        void __fastcall Printing();	//вывод принятых байтов на экран и в файл
 protected:
        void __fastcall Execute();	//основная функция потока
 public:
        __fastcall ReadThread(bool CreateSuspended);	//конструктор потока
};

//---------------------------------------------------------------------------

//поток для записи последовательности байтов из буфера в COM-порт
class WriteThread : public TThread
{
private:
 	void __fastcall Printing();	//вывод состояния на экран
protected:
        void __fastcall Execute();      //основная функция потока
public:
        __fastcall WriteThread(bool CreateSuspended);	//конструктор потока
};

//---------------------------------------------------------------------------


//=============================================================================
//.............................. реализация потоков ...........................
//=============================================================================

//-----------------------------------------------------------------------------
//............................... поток ReadThead .............................
//-----------------------------------------------------------------------------

ReadThread *reader;     //объект потока ReadThread

//---------------------------------------------------------------------------

//конструктор потока ReadThread, по умолчанию пустой
__fastcall ReadThread::ReadThread(bool CreateSuspended) : TThread(CreateSuspended)
{}

//---------------------------------------------------------------------------

//главная функция потока, реализует приём байтов из COM-порта
void __fastcall ReadThread::Execute()
{
 COMSTAT comstat;		//структура текущего состояния порта, в данной программе используется для определения количества принятых в порт байтов
 DWORD btr, temp, mask, signal;	//переменная temp используется в качестве заглушки

 overlapped.hEvent = CreateEvent(NULL, true, true, NULL);	//создать сигнальный объект-событие для асинхронных операций
 SetCommMask(COMport, EV_RXCHAR);                   	        //установить маску на срабатывание по событию приёма байта в порт
 while(!Terminated)						//пока поток не будет прерван, выполняем цикл
  {
   WaitCommEvent(COMport, &mask, &overlapped);               	//ожидать события приёма байта (это и есть перекрываемая операция)
   signal = WaitForSingleObject(overlapped.hEvent, INFINITE);	//приостановить поток до прихода байта
   if(signal == WAIT_OBJECT_0)				        //если событие прихода байта произошло
    {
     if(GetOverlappedResult(COMport, &overlapped, &temp, true)) //проверяем, успешно ли завершилась перекрываемая операция WaitCommEvent
      if((mask & EV_RXCHAR)!=0)					//если произошло именно событие прихода байта
       {
         btr=1;
         while (btr!=0)
         {
          ClearCommError(COMport, &temp, &comstat);		//нужно заполнить структуру COMSTAT
          btr = comstat.cbInQue;                          	//и получить из неё количество принятых байтов
          if(btr)                         			//если действительно есть байты для чтения
          {
           ReadFile(COMport, bufrd, btr, &temp, &overlapped);     //прочитать байты из порта в буфер программы
           counter+=btr;                                          //увеличиваем счётчик байтов
           Synchronize(Printing);                      		//вызываем функцию для вывода данных на экран и в файл
          }
       }
       }
    }
  }
 CloseHandle(overlapped.hEvent);		//перед выходом из потока закрыть объект-событие
}

//---------------------------------------------------------------------------

//выводим принятые байты на экран и в файл (если включено)
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
 while (*pch) // работаем с буфером посимвольно, чтоб отследить конец строки
                // так как \n может придти в следующем пакете, а не в этом
 {
      iPosStr=Form1->Memo1->Lines->Count;
      iPosStr--;
      sOld=Form1->Memo1->Lines->Strings[iPosStr];
      Form1->Memo1->Lines->Strings[iPosStr]=sOld+*pch;
      if (*pch=='\n')
      {
        sBuf=Form1->Memo1->Lines->Strings[iPosStr];
 // **************** парсим показания с АЦП   **********************************
        sHead="ACD_VAL=";        // это начало сообщения со значением АЦП
        iPosChar=sBuf.Pos(sHead);
        if (iPosChar!=0)
        {
                sBuf=sBuf.SubString(iPosChar+sHead.Length(),sBuf.Length()-iPosChar-sHead.Length()-1);
                i=sBuf.ToDouble();
                Form1->Series2->AddXY(iChartCounter++,i/100 ,"",clRed);
                sBuf.printf("%d \n", i);
                Form1->Memo1->Lines->Add(sBuf); //выводим принятую строку в Memo
        }  // if (iPosChar!=0)

 // **************** парсим показания со штангени   **********************************
        sHead="CALIPERS_VAL=";        // это начало сообщения
        iPosChar=sBuf.Pos(sHead);
        if (iPosChar!=0)
        {
                sBuf=sBuf.SubString(iPosChar+sHead.Length(),sBuf.Length()-iPosChar-sHead.Length()-1);
                lTemp=sBuf.ToDouble();
                fTemp=lTemp;
                fTemp=fTemp/100;

                Form1->Series3->AddXY(iChartCounter_2++,fTemp ,"",clGreen);
                sBuf.printf(" %f \n", fTemp);
                Form1->Memo1->Lines->Add(sBuf); //выводим принятую строку в Memo
                 Form1->lCalipersData->Caption=sBuf;
        }  // if (iPosChar!=0)

        Form1->Memo1->Lines->Add("");   // пришел конец строки
      } //if (*pch=='\n')
      pch++;

 }

 Form1->StatusBar1->Panels->Items[2]->Text = "Всего принято " + IntToStr(counter) + " байт";	//выводим счётчик в строке состояния

 if(Form1->CheckBox3->Checked == true)  //если включен режим вывода в файл
  {
   write(handle, bufrd, strlen(bufrd)); //записать в файл данные из приёмного буфера
  }
 memset(bufrd, 0, BUFSIZE);	        //очистить буфер (чтобы данные не накладывались друг на друга)
}

//---------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//............................... поток WriteThead ............................
//-----------------------------------------------------------------------------

WriteThread *writer;     //объект потока WriteThread

//---------------------------------------------------------------------------

//конструктор потока WriteThread, по умолчанию пустой
__fastcall WriteThread::WriteThread(bool CreateSuspended) : TThread(CreateSuspended)
{}

//---------------------------------------------------------------------------

//главная функция потока, выполняет передачу байтов из буфера в COM-порт
void __fastcall WriteThread::Execute()
{
 DWORD temp, signal;	//temp - переменная-заглушка

 overlappedwr.hEvent = CreateEvent(NULL, true, true, NULL);   	  //создать событие
 WriteFile(COMport, bufwr, strlen(bufwr), &temp, &overlappedwr);  //записать байты в порт (перекрываемая операция!)
 signal = WaitForSingleObject(overlappedwr.hEvent, INFINITE);	  //приостановить поток, пока не завершится перекрываемая операция WriteFile
 if((signal == WAIT_OBJECT_0) && (GetOverlappedResult(COMport, &overlappedwr, &temp, true))) fl = true; //если операция завершилась успешно, установить соответствующий флажок
 else fl = false;
 Synchronize(Printing);	//вывести состояние операции в строке состояния
 CloseHandle(overlappedwr.hEvent);	//перед выходом из потока закрыть объект-событие
}

//---------------------------------------------------------------------------

//вывод состояния передачи данных на экран
void __fastcall WriteThread::Printing()
{
 if(!fl)	//проверяем состояние флажка
  {
   Form1->StatusBar1->Panels->Items[0]->Text  = "Ошибка передачи";
   return;
  }
 Form1->StatusBar1->Panels->Items[0]->Text  = "Передача прошла успешно";
}

//---------------------------------------------------------------------------


//=============================================================================
//............................. элементы формы ................................
//=============================================================================

//---------------------------------------------------------------------------

//конструктор формы, обычно в нём выполняется инициализация элементов формы
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
 //инициализация элементов формы при запуске программы
 Form1->Label5->Enabled = false;
 Form1->Label6->Enabled = false;
 Form1->Button1->Enabled = false;
 Form1->CheckBox1->Enabled = false;
 Form1->CheckBox2->Enabled = false;
}

//---------------------------------------------------------------------------

//обработчик нажатия на кнопку "Открыть порт"
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
 if(SpeedButton1->Down)
  {
   COMOpen();                   //если кнопка нажата - открыть порт

   //показать/спрятать элементы на форме
   Form1->ComboBox1->Enabled = false;
   Form1->ComboBox2->Enabled = false;
   Form1->Button1->Enabled = true;
   Form1->CheckBox1->Enabled = true;
   Form1->CheckBox2->Enabled = true;

   Form1->SpeedButton1->Caption = "Закрыть порт";	//сменить надпись на кнопке

   counter = 0;	//сбрасываем счётчик байтов

   //если были включены флажки DTR и RTS, установить эти линии в единицу
   Form1->CheckBox1Click(Sender);
   Form1->CheckBox2Click(Sender);
  }

 else
  {
   COMClose();                  //если кнопка отжата - закрыть порт

   Form1->SpeedButton1->Caption = "Открыть порт";	//сменить надпись на кнопке
   Form1->StatusBar1->Panels->Items[0]->Text = "";	//очистить первую колонку строки состояния

   //показать/спрятать элементы на форме
   Form1->ComboBox1->Enabled = true;
   Form1->ComboBox2->Enabled = true;
   Form1->Button1->Enabled = false;
   Form1->CheckBox1->Enabled = false;
   Form1->CheckBox2->Enabled = false;
  }
}

//---------------------------------------------------------------------------

//обработчик закрытия формы
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
 if(reader)reader->Terminate(); 	//завершить поток чтения из порта, проверка if(reader) обязательна, иначе возникают ошибки
 if(writer)writer->Terminate();         //завершить поток записи в порт, проверка if(writer) обязательна, иначе возникают ошибки
 if(COMport)CloseHandle(COMport);       //закрыть порт
 if(handle)close(handle);               //закрыть файл, в который велась запись принимаемых данных

}
//---------------------------------------------------------------------------

//галочка "Сохранить в файл"
void __fastcall TForm1::CheckBox3Click(TObject *Sender)
{
 if(Form1->CheckBox3->Checked)		//если галочка включена
  {
   //активировать соответствующие элементы на форме
   Form1->Label5->Enabled = true;
   Form1->Label6->Enabled = true;

   //вывести индикатор записи в файл в строке состояния
   Form1->StatusBar1->Panels->Items[1]->Text = "Вывод в файл!";
  }

 else   				//если галочка выключена
  {
   //отключить соответствующие элементы на форме
   Form1->Label5->Enabled = false;
   Form1->Label6->Enabled = false;

   //убрать индикатор записи в файл из строки состояния
   Form1->StatusBar1->Panels->Items[1]->Text = "";
  }

}
//---------------------------------------------------------------------------

//кнопка "Передать"
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 memset(bufwr,0,BUFSIZE);			//очистить программный передающий буфер, чтобы данные не накладывались друг на друга
 PurgeComm(COMport, PURGE_TXCLEAR);             //очистить передающий буфер порта
 strcpy(bufwr,Form1->Edit1->Text.c_str());      //занести в программный передающий буфер строку из Edit1 

 writer = new WriteThread(false);               //создать и активировать поток записи данных в порт
 writer->FreeOnTerminate = true;                //установить это свойство, чтобы поток автоматически уничтожался после завершения

}

//---------------------------------------------------------------------------

//кнопка "Очистить поле"
void __fastcall TForm1::Button3Click(TObject *Sender)
{
 Form1->Memo1->Clear();	//очистить Memo1
}

//---------------------------------------------------------------------------

//галочка "DTR"
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
 //если установлена - установить линию DTR в единицу, иначе - в ноль
 if(Form1->CheckBox1->Checked) EscapeCommFunction(COMport, SETDTR);
 else EscapeCommFunction(COMport, CLRDTR);
}

//---------------------------------------------------------------------------

//галочка "RTS"
void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
 //если установлена - установить линию RTS в единицу, иначе - в ноль
 if(Form1->CheckBox2->Checked) EscapeCommFunction(COMport, SETRTS);
 else EscapeCommFunction(COMport, CLRRTS);
}

//---------------------------------------------------------------------------

//=============================================================================
//........................... реализации функций ..............................
//=============================================================================

//---------------------------------------------------------------------------

//функция открытия и инициализации порта
void COMOpen()
{
 String portname;     	 //имя порта (например, "COM1", "COM2" и т.д.)
 DCB dcb;                //структура для общей инициализации порта DCB
 COMMTIMEOUTS timeouts;  //структура для установки таймаутов
 
 portname = Form1->ComboBox1->Text;	//получить имя выбранного порта

 //открыть порт, для асинхронных операций обязательно нужно указать флаг FILE_FLAG_OVERLAPPED
 COMport = CreateFile(portname.c_str(),GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
 //здесь:
 // - portname.c_str() - имя порта в качестве имени файла, c_str() преобразует строку типа String в строку в виде массива типа char, иначе функция не примет
 // - GENERIC_READ | GENERIC_WRITE - доступ к порту на чтение/записть
 // - 0 - порт не может быть общедоступным (shared)
 // - NULL - дескриптор порта не наследуется, используется дескриптор безопасности по умолчанию
 // - OPEN_EXISTING - порт должен открываться как уже существующий файл
 // - FILE_FLAG_OVERLAPPED - этот флаг указывает на использование асинхронных операций
 // - NULL - указатель на файл шаблона не используется при работе с портами

 if(COMport == INVALID_HANDLE_VALUE)            //если ошибка открытия порта
  {
   Form1->SpeedButton1->Down = false;           //отжать кнопку
   Form1->StatusBar1->Panels->Items[0]->Text = "Не удалось открыть порт";       //вывести сообщение в строке состояния
   return;
  }

 //инициализация порта

 dcb.DCBlength = sizeof(DCB); 	//в первое поле структуры DCB необходимо занести её длину, она будет использоваться функциями настройки порта для контроля корректности структуры

 //считать структуру DCB из порта
 if(!GetCommState(COMport, &dcb))	//если не удалось - закрыть порт и вывести сообщение об ошибке в строке состояния
  {
   COMClose();
   Form1->StatusBar1->Panels->Items[0]->Text  = "Не удалось считать DCB";
   return;
  }

 //инициализация структуры DCB
 dcb.BaudRate = StrToInt(Form1->ComboBox2->Text);       //задаём скорость передачи 115200 бод
 dcb.fBinary = TRUE;                                    //включаем двоичный режим обмена
 dcb.fOutxCtsFlow = FALSE;                              //выключаем режим слежения за сигналом CTS
 dcb.fOutxDsrFlow = FALSE;                              //выключаем режим слежения за сигналом DSR
 dcb.fDtrControl = DTR_CONTROL_DISABLE;                 //отключаем использование линии DTR
 dcb.fDsrSensitivity = FALSE;                           //отключаем восприимчивость драйвера к состоянию линии DSR
 dcb.fNull = FALSE;                                     //разрешить приём нулевых байтов
 dcb.fRtsControl = RTS_CONTROL_DISABLE;                 //отключаем использование линии RTS
 dcb.fAbortOnError = FALSE;                             //отключаем остановку всех операций чтения/записи при ошибке
 dcb.ByteSize = 8;                                      //задаём 8 бит в байте
 dcb.Parity = 0;                                        //отключаем проверку чётности
 dcb.StopBits = 0;                                      //задаём один стоп-бит

 //загрузить структуру DCB в порт
 if(!SetCommState(COMport, &dcb))	//если не удалось - закрыть порт и вывести сообщение об ошибке в строке состояния
  {
   COMClose();
   Form1->StatusBar1->Panels->Items[0]->Text  = "Не удалось установить DCB";
   return;
  }

 //установить таймауты
 timeouts.ReadIntervalTimeout = 0;	 	//таймаут между двумя символами
 timeouts.ReadTotalTimeoutMultiplier = 0;	//общий таймаут операции чтения
 timeouts.ReadTotalTimeoutConstant = 0;         //константа для общего таймаута операции чтения
 timeouts.WriteTotalTimeoutMultiplier = 0;      //общий таймаут операции записи
 timeouts.WriteTotalTimeoutConstant = 0;        //константа для общего таймаута операции записи

 //записать структуру таймаутов в порт
 if(!SetCommTimeouts(COMport, &timeouts))	//если не удалось - закрыть порт и вывести сообщение об ошибке в строке состояния
  {
   COMClose();
   Form1->StatusBar1->Panels->Items[0]->Text  = "Не удалось установить тайм-ауты";
   return;
  }

 //установить размеры очередей приёма и передачи
 SetupComm(COMport,2000,2000);

 //создать или открыть существующий файл для записи принимаемых данных
 handle = open("test.txt", O_CREAT | O_APPEND | O_BINARY | O_WRONLY, S_IREAD | S_IWRITE);

 if(handle==-1)		//если произошла ошибка открытия файла
  {
   Form1->StatusBar1->Panels->Items[1]->Text = "Ошибка открытия файла";	//вывести сообщение об этом в командной строке
   Form1->Label6->Hide();                                               //спрятать надпись с именем файла
   Form1->CheckBox3->Checked = false;                                   //сбросить и отключить галочку
   Form1->CheckBox3->Enabled = false;
  }
 else { Form1->StatusBar1->Panels->Items[0]->Text = "Файл открыт успешно"; } //иначе вывести в строке состояния сообщение об успешном открытии файла 

 PurgeComm(COMport, PURGE_RXCLEAR);	//очистить принимающий буфер порта

 reader = new ReadThread(false);	//создать и запустить поток чтения байтов
 reader->FreeOnTerminate = true;        //установить это свойство потока, чтобы он автоматически уничтожался после завершения

}

//---------------------------------------------------------------------------

//функция закрытия порта
void COMClose()
{
 if(writer)writer->Terminate();		//если поток записи работает, завершить его; проверка if(writer) обязательна, иначе возникают ошибки
 if(reader)reader->Terminate();         //если поток чтения работает, завершить его; проверка if(reader) обязательна, иначе возникают ошибки
 CloseHandle(COMport);                  //закрыть порт
 COMport=0;				//обнулить переменную для дескриптора порта
 close(handle);				//закрыть файл для записи принимаемых данных
 handle=0;				//обнулить переменную для дескриптора файла
}

//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
Form1->Series3->Clear();
Form1->Series2->Clear();
}
//---------------------------------------------------------------------------

