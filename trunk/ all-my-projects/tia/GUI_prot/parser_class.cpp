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
                s=s.SubString(iPosChar+sHeader.Length(),s.Length()-iPosChar-sHeader.Length()-1);
                dData=s.ToDouble();
                AddData(dData);
               return true;
        }  // if (iPosChar!=0)
        return false;
}

bool  Parser_Class::GetData (DWORD *pdData )
{
        bool bRes=false;
     EnterCriticalSection(&pCritSec);
     if (stdBuf.size())
        {
                *pdData = stdBuf.front();
                stdBuf.pop_front();
                bRes=true;
        }
    LeaveCriticalSection (&pCritSec);
    return bRes;
}

void Parser_Class::ProcessData (void)
{
     DWORD dData;
     if (GetData(&dData)==false) return; // нет данных
    if  (Callback!=NULL)  Callback(dData);
}

Parser_Class::Parser_Class (ftVoid_dw pFunc, AnsiString* pHeaderText,unsigned int iBufSize)
{
        InitializeCriticalSection(&pCritSec);
        //InitializeCriticalSectionAndSpinCount(&pCritSec,4000);
        SetHeader(pHeaderText);
        SetCallback(pFunc);
        SetBufsize(iBufSize);
}

Parser_Class::~Parser_Class(void)
{
     DeleteCriticalSection(&pCritSec);
}



//---------------------------------------------------------------------------

#pragma package(smart_init)
