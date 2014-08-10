/*
 * uplink_unit.cpp
 *
 *  Created on: 21 марта 2014 г.
 *      Author: Admin
 */

#include "uplink_unit.h"
#include "crc_8_16_32.h"
#include <stdlib.h>

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

void UplinkClass :: Task(void)
{
	// обрабатываем текущие буферы
	uint8_t i=0;
	DataPack_t* dpPack;
	while (i<BUF_NAMBER)
	{
		if (BufArray[i].IsValidCommand()) // в буфере находится команда
		{
			//DbgUART->SendPrintF("IsValidCommand=true n=%d \n",i);
			dpPack=BufArray[i].GetCommand();
			if (Callback!=NULL) Callback(dpPack->Command);
			BufArray[i].Clear();
		}
		i++;
	}
	// обрабатывам входящий байт
	while (!(pUART->FIFO_RxData.IsEmpty()))
	{
		Recive(pUART->FIFO_RxData.SimpleReadByte());
	}

}

void UplinkClass :: Send (DataPack_t* pDataPack)
{
	pDataPack->Pref=DATA_PACK_PREF;
	pDataPack->Reserv=0;
	pDataPack->CRC16=crc16_tbl_buf((unsigned char*)&(pDataPack->Command),CRC16_INIT,DATA_CRC_CALC_SIZE);
	//pDataPack->CRC16=crc16_sft_buf((unsigned char*)&(pDataPack->Command),CRC16_INIT,DATA_CRC_CALC_SIZE);
	pUART->SendBuf(DATA_PACK_SIZE, (uint8_t*)pDataPack);
	return;
}

//DataPack_t* UplinkClass :: GetCommand (void)
//{
//	uint8_t i=0;
//	while (i<BUF_NAMBER)
//	{
//		if (/*IsValidCommand()*/1)
//		{
//			/*gjfgjhfghj*/;
//		}
//		i++;
//	}
//	return NULL;
//}

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
	bEmptyFlag=false;
	// check second prefix byte
	if ((chByteCounter==1) & (chDataByte!=LO_DATA_PACK_PREF_BYTE))
	{
		Clear();
		return;
	}
	// insert data byte in buffer of bytes
	uint8_t* pByte;
	pByte=(uint8_t*)&DataPack;
	pByte=pByte+chByteCounter;
	*pByte=chDataByte;
	chByteCounter++;


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

