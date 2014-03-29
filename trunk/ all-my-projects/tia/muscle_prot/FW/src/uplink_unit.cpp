/*
 * uplink_unit.cpp
 *
 *  Created on: 21 марта 2014 г.
 *      Author: Admin
 */

#include "Uplink_unit.h"

uint8_t UplinkClass :: Init(uint16_t iSize)
{
	return 0;
}

void UplinkClass :: Task(void)
{
	return 0;
}

void UplinkClass :: Send (DataPack_t* pDataPack)
{
	pDataPack->Pref=DATA_PACK_PREF;
	// calc CRC16
	//pDataPack->CRC16=
	pUART->SendBuf(DATA_PACK_SIZE, (*uint8_t)pDataPack);
	return;
}

