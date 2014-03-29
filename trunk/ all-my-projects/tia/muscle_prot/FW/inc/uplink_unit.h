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
#define DATA_PACK_PREF	0xA55A // префикс

struct DataPack_t {
	uint16_t Pref;
    uint16_t CRC16;
	uint8_t Command;
	uint8_t Addr;
    uint32_t Data
}


class UplinkClass {
private:
	UART_Class* pUART;
public:
	void SetUart(UART_Class* p) {pUART=p;};
	uint8_t Init(uint16_t iSize);
	void Send (DataPack_t* pDataPack);
	void Task (void);

};

#endif /* UPLINK_UNIT_H_ */
