/*
    ����� �������� ������  ������� "MesHeader Data", ����������
MesHeader � �������� ��������� sHeader � ����������� ������ Data � ������.
�������� ������ �� ������ � ������� ������, ���������� ����� ProcessData.
����� AddData ���������� �� ������ ������, � ����� ProcessData �� �������.
*/
//---------------------------------------------------------------------------

#ifndef parser_classH
#define parser_classH

#include <vcl.h>
#include <deque>


using std::deque;

typedef void(*ftVoid_dw)(DWORD );

class Parser_Class {
private:
        deque <DWORD > stdBuf;
        AnsiString sHeader;
        ftVoid_dw Callback;
        CRITICAL_SECTION pCritSec;
        unsigned int iBufSizeMax;


public:
        void SetCallback (ftVoid_dw pFunc){Callback=pFunc;};
        void SetHeader (char* pcHeader){sHeader=pcHeader;};
        void SetBufsize (unsigned int iBufSize=255){iBufSizeMax=iBufSize;};
        bool ParsString (AnsiString *pStr);
        void AddData (DWORD   dData);
        bool  GetData (DWORD *pdData );
        void ProcessData (void);
        DWORD dwDataCounter;
        Parser_Class (ftVoid_dw pFunc, char* pcHeaderText,unsigned int iBufSize=255);
        ~Parser_Class(void);
};



//---------------------------------------------------------------------------
#endif
