/*
    Класс получает строку  формата "MesHeader Data", сравнивает
MesHeader с заданным значением sHeader и накапливает данные Data в буфере.
Передает данные из буфера в функцию потока, вызвавшего метод ProcessData.
Метод AddData вызывается из одного потока, а метод ProcessData из другого.
*/
//---------------------------------------------------------------------------

#ifndef parser_classH
#define parser_classH

#include <vcl.h>
#include <deque>
#include "crc_8_16_32.h"


using std::deque;



#define DATA_PACK_SIZE	sizeof(DataPack_t) // размер структуры
#define DATA_CRC_CALC_SIZE	DATA_PACK_SIZE-4 // кол-во байт, по которым считается CRC16

#define DATA_PACK_PREF	0xA55A // префикс
#define HI_DATA_PACK_PREF_BYTE	0xA5
#define LO_DATA_PACK_PREF_BYTE	0x5A
#define BUF_NAMBER			4

#define CRC16_INIT		0x00
typedef unsigned char uint8_t ;
typedef signed long int32_t;
typedef unsigned long uint32_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;

struct DataPack_t {
	uint16_t Pref;
        uint16_t CRC16;
	uint8_t Command;
	uint8_t Addr;
	uint16_t Reserv;  // нужен для выравнивания структуры по 32 бита
        uint32_t Data;
};

class SmartBufClass {
private:
	DataPack_t DataPack;
	bool bValidCommand;
	bool bEmptyFlag;
	uint8_t chByteCounter;
public:
	void Insert(uint8_t chDataByte);
	void Process(void);
	void Clear (void);
	bool IsValidCommand (void) {return bValidCommand;};
	bool IsEmpty (void) {return bEmptyFlag;};
	DataPack_t* GetCommand (void) {return &DataPack;};
};

class UplinkClass {
private:
	SmartBufClass BufArray[BUF_NAMBER];
public:
	uint8_t Init(uint16_t iSize);
	void Send (DataPack_t* pDataPack);
	void Recive (uint8_t chDataByte);
	DataPack_t*  GetCommand (void);
};


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
