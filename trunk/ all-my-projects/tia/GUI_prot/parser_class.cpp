//---------------------------------------------------------------------------


#pragma hdrstop

#include "parser_class.h"

void Parser_Class::AddData ( DWORD  dData)
{
    EnterCriticalSection(&pCritSec);
          stdBuf.push_back(dData);
      if (stdBuf.size()>iBufSizeMax) stdBuf.pop_front();
    LeaveCriticalSection (&pCritSec);
}

bool Parser_Class::ParsString (AnsiString *pStr)
{
        DWORD   dData;
        AnsiString s=*pStr;
        int iPosChar=s.Pos(sHeader);
        if (iPosChar!=0)
        {
                dData= sHeader.Length();
                dData= s.Length() ;
                dData=s.Length()-iPosChar-sHeader.Length()-1;
                s=s.SubString(iPosChar+sHeader.Length(),s.Length()-iPosChar-sHeader.Length());
                dData=s.ToDouble();
                AddData(dData);
               return true;
        }  // if (iPosChar!=0)
        return false;
}

bool  Parser_Class::GetData (DWORD *pdData )
{
        bool bRes=false;
        if (stdBuf.size()==0)  return false;    // в буфере нет данных
     EnterCriticalSection(&pCritSec);
        *pdData = stdBuf.front();
         stdBuf.pop_front();
   LeaveCriticalSection (&pCritSec);
    return true;
}

void Parser_Class::ProcessData (void)
{
     DWORD dData;
     while (GetData(&dData)) // пока есть данные
     {
        if  (Callback!=NULL)  Callback(dData);
        dwDataCounter++;
     }
}

Parser_Class::Parser_Class (ftVoid_dw pFunc, char* pcHeaderText,unsigned int iBufSize)
{
        dwDataCounter=0;
        InitializeCriticalSection(&pCritSec);
        //InitializeCriticalSectionAndSpinCount(&pCritSec,4000);
        SetHeader(pcHeaderText);
        SetCallback(pFunc);
        SetBufsize(iBufSize);
}

Parser_Class::~Parser_Class(void)
{
     DeleteCriticalSection(&pCritSec);
}



//---------------------------------------------------------------------------

#pragma package(smart_init)
