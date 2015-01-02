/*
 * uplink_unit.h
 *
 *  Created on: 21 ����� 2014 �.
 *      Author: Admin
 */

#ifndef UPLINK_UNIT_H_
#define UPLINK_UNIT_H_

#include "UARTClass.h"
#include "common.h"

#define DATA_PACK_SIZE	sizeof(DataPack_t) // ������ ���������
#define DATA_CRC_CALC_SIZE	DATA_PACK_SIZE-4 // ���-�� ����, �� ������� ��������� CRC16

#define DATA_PACK_PREF	0x5AA5 // �������, ������� � �������� ������� ����
#define HI_DATA_PACK_PREF_BYTE	0xA5
#define LO_DATA_PACK_PREF_BYTE	0x5A
#define BUF_NAMBER			4

#define CRC16_INIT		0x00


/*�������� ���� Command:
	2 � � Data ���������� ��������
	4 � � Data ���������� ������
	8 � � Data ���������� ������
	16 � � Data ���������� �����������
	0x42 � ��������� �������� ������� IN_VALVE
	0�44 � ��������� ������� ������� OUT_VALVE
��������
	0x12 � ���������� ������� ���������� ����������� �������� (IN_VALVE)
	0�14 � ���������� ������� ���������� ���������� �������� (OUT_VALVE)
	0�22 � ������ ��������� IN_VALVE
	0�24 � ������ ��������� OUT_VALVE

 */
#define DATA_PACK_COMMAND_TEST				0x00
#define DATA_PACK_COMMAND_PRES				0x02
#define DATA_PACK_COMMAND_TENZO				0x04
#define DATA_PACK_COMMAND_LENGTH			0x08
#define DATA_PACK_COMMAND_TEMP				0x0F
#define DATA_PACK_COMMAND_IN_VALVE_STAT		0x42
#define DATA_PACK_COMMAND_OUT_VALVE_STAT	0x44
#define DATA_PACK_COMMAND_ADC_ERROR			0x81

#define DATA_PACK_COMMAND_IN_VALVE_SET		0x12
#define DATA_PACK_COMMAND_OUT_VALVE_SET		0x14
#define DATA_PACK_COMMAND_IN_VALVE_GET		0x22
#define DATA_PACK_COMMAND_OUT_VALVE_GET		0x24

struct DataPack_t {
	uint16_t Pref;
    uint16_t CRC16;
	uint8_t Command;
	uint8_t Addr;
	uint16_t Reserv;  // ����� ��� ������������ ��������� �� 32 ����
    uint32_t Data;
};

typedef void (*ftVoid_pDataPack)(DataPack_t* pDataPack);

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
	ftVoid_pDataPack Callback;
	void SetUart(UART_Class* p) {pUART=p;};
	uint8_t Init(uint16_t iSize);
	void Send (DataPack_t* pDataPack);
	void Recive (uint8_t chDataByte);
	DataPack_t*  GetCommand (void);
	void Task (void);

};




#endif /* UPLINK_UNIT_H_ */
