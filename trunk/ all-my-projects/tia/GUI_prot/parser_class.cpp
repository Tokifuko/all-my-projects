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


uint8_t UplinkClass :: Init(uint16_t iSize)
{
	uint8_t i=0;
	while (i<BUF_NAMBER)
	{
		BufArray[i].Clear();
		i++;
	}
	return 0;
}


void UplinkClass :: Send (DataPack_t* pDataPack)
{
	pDataPack->Pref=DATA_PACK_PREF;
	pDataPack->Reserv=0;
	pDataPack->CRC16=crc16_tbl_buf((unsigned char*)&(pDataPack->Command),CRC16_INIT,DATA_CRC_CALC_SIZE);
       //	pUART->SendBuf(DATA_PACK_SIZE, (uint8_t*)pDataPack);
	return;
}

DataPack_t* UplinkClass :: GetCommand (void)
{
	uint8_t i=0;
	while (i<BUF_NAMBER)
	{
		if (BufArray[i].IsValidCommand())
		{
                        BufArray[i].Clear();
			return BufArray[i].GetCommand();
		}
		i++;
	}
	return NULL;
}

void UplinkClass :: Recive(uint8_t chDataByte)
{
	// add new byte to existence buffer
	uint8_t i=0;
	while (i<BUF_NAMBER)
	{
		if (!(BufArray[i].IsEmpty())) BufArray[i].Insert(chDataByte);
		i++;
	}
	// if got prefix - activation new buffer
	if (chDataByte==HI_DATA_PACK_PREF_BYTE)
	{
		i=0;
		while (i<BUF_NAMBER)
		{
			if (BufArray[i].IsEmpty())
			{
				BufArray[i].Insert(chDataByte);
				break;
			}
			i++;
		}//while
	}// if
}


void SmartBufClass :: Insert(uint8_t chDataByte)
{
	if (IsValidCommand()) return; // buffer full
	// check second prefix byte
	if ((chByteCounter==1) & (chDataByte!=LO_DATA_PACK_PREF_BYTE))
	{
		Clear();
		return;
	}
	*((uint8_t*)(&DataPack+chByteCounter))=chDataByte; // insert data byte in buffer of bytes
	chByteCounter++;
	bEmptyFlag=false;
	// processing data
	if (chByteCounter==DATA_PACK_SIZE)
	{
		uint16_t iCRC16;
		iCRC16=crc16_tbl_buf((unsigned char*)&(DataPack.Command),CRC16_INIT,DATA_CRC_CALC_SIZE);
		if (DataPack.CRC16==iCRC16) bValidCommand=true;
			else Clear();
	}
}

void SmartBufClass :: Clear(void)
{
	chByteCounter=0;
	bEmptyFlag=true;
	bValidCommand=false;
}


//---------------------------------------------------------------------------

#pragma package(smart_init)
