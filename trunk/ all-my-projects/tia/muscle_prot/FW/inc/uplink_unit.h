/*
 * uplink_unit.h
 *
 *  Created on: 21 марта 2014 г.
 *      Author: Admin
 */

#ifndef UPLINK_UNIT_H_
#define UPLINK_UNIT_H_

#include "UARTClass.h"

#define DATA_PACK_SIZE	10 // размер структуры
#define DATA_CRC_CALC_SIZE	3 // кол-во 16-и битных чисел, по которым считается CRC16

#define DATA_PACK_PREF	0xA55A // префикс
#define HI_DATA_PACK_PREF_BYTE	0xA5
#define LO_DATA_PACK_PREF_BYTE	0x5A
#define BUF_NAMBER			4

#define CRC16_INIT		0x00

struct DataPack_t {
	uint16_t Pref;
    uint16_t CRC16;
	uint8_t Command;
	uint8_t Addr;
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
	DataPack_t* GetCommand (void) {return &DataPack);
};

class UplinkClass {
private:
	UART_Class* pUART;
	SmartBufClass BufArray[BUF_NAMBER];
public:
	void SetUart(UART_Class* p) {pUART=p;};
	uint8_t Init(uint16_t iSize);
	void Send (DataPack_t* pDataPack);
	void Recive (uint8_t chDataByte);
	DataPack_t*  GetCommand (void);
	void Task (void);

};




#endif /* UPLINK_UNIT_H_ */
