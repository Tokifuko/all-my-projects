/*
 * uplink_unit.h
 *
 *  Created on: 21 марта 2014 г.
 *      Author: Admin
 */

#ifndef UPLINK_UNIT_H_
#define UPLINK_UNIT_H_

#include "UARTClass.h"
#include "common.h"

#define DATA_PACK_SIZE	sizeof(DataPack_t) // размер структуры
#define DATA_CRC_CALC_SIZE	DATA_PACK_SIZE-4 // кол-во байт, по которым считаетс€ CRC16

#define DATA_PACK_PREF	0x5AA5 // префикс
#define HI_DATA_PACK_PREF_BYTE	0x5A
#define LO_DATA_PACK_PREF_BYTE	0xA5
#define BUF_NAMBER			4

#define CRC16_INIT		0x00


/*«начение пол€ Addr:
	2 Ц в Data передаетс€ давление
	4 Ц в Data передаетс€ усилие
	8 Ц в Data передаетс€ длинна
	16 Ц в Data передаетс€ температура
 */
#define DATA_PACK_ADDR_TEST			0x00
#define DATA_PACK_ADDR_PRES			0x02
#define DATA_PACK_ADDR_TENZO		0x04
#define DATA_PACK_ADDR_LENGTH		0x08
#define DATA_PACK_ADDR_TEMP			0x0F

struct DataPack_t {
	uint16_t Pref;
    uint16_t CRC16;
	uint8_t Command;
	uint8_t Addr;
	uint16_t Reserv;  // нужен дл€ выравнивани€ структуры по 32 бита
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
	//void Process(void);
	void Clear (void);
	bool IsValidCommand (void) {return bValidCommand;};
	bool IsEmpty (void) {return bEmptyFlag;};
	DataPack_t* GetCommand (void) {return &DataPack;};
};

class UplinkClass {
private:
	UART_Class* pUART;
	SmartBufClass BufArray[BUF_NAMBER];
public:
	//UART_Class* DbgUART;
	ftVoid_uint32 Callback;
	void SetUart(UART_Class* p) {pUART=p;};
	uint8_t Init(uint16_t iSize);
	void Send (DataPack_t* pDataPack);
	void Recive (uint8_t chDataByte);
	DataPack_t*  GetCommand (void);
	void Task (void);

};




#endif /* UPLINK_UNIT_H_ */
