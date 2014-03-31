/*
 * uplink_unit.cpp
 *
 *  Created on: 21 марта 2014 г.
 *      Author: Admin
 */

#include "Uplink_unit.h"

uint8_t UplinkClass :: Init(uint16_t iSize)
{
	uint8_t i=0;
	while (i<BUF_NAMBER)
	{
		BufArray[i].Clear();
	}
	return;// 0;
}

void UplinkClass :: Task(void)
{
	while (pUART->FIFO_RxData.IsEmpty()) Recive(pUART->FIFO_RxData.SimpleReadByte());

	return;// 0;
}

void UplinkClass :: Send (DataPack_t* pDataPack)
{
	pDataPack->Pref=DATA_PACK_PREF;
	// calc CRC16
	//pDataPack->CRC16=
	pUART->SendBuf(DATA_PACK_SIZE, (*uint8_t)pDataPack);
	return;
}

DataPack_t* UplinkClass :: GetCommand (void)
{
	uint8_t i=0;
	while (i<BUF_NAMBER)
	{
		if (/*IsValidCommand()*/)
		{
			/*insert_data*/;
		}
	}
	return NULL;
}

void UplinkClass :: Recive(uint8_t chDataByte)
{
	// add new byte to existence buffer
	uint8_t i=0;
	while (i<BUF_NAMBER)
	{
		if (/* buf_no_empty*/1) /*insert_data*/;
		i++;
	}
	// if got prefix - activation new buffer
	if (chDataByte==HI_DATA_PACK_PREF_BYTE)
	{
		i=0;
		while (i<BUF_NAMBER)
		{
			if (/* buf_empty*/1)
			{
				/*insert_data*/;
				break;
			}
			i++;
		}
	}// if (chDataByte==HI_DATA_PACK_PREF_BYTE)
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
	((uint8_t*) &DataPack)+chByteCounter=chDataByte; // insert data byte in buffer of bytes
	chByteCounter++;
	bEmptyFlag=false;
	// processing data
	if (chByteCounter==DATA_PACK_SIZE)
	{
		// calc crc16
		bValidCommand==true;
		// else clear
	}
}

void SmartBufClass :: Clear(uint8_t chDataByte)
{
	chByteCounter=0;
	bEmptyFlag=true;
	bValidCommand==false;
}
