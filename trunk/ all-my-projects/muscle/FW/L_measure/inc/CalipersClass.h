/*
 * CalipersClass.h
 *
 *  Created on: 09 окт. 2013 г.
 *      Author: Stefan
 */

#ifndef CALIPERSCLASS_H_
#define CALIPERSCLASS_H_


#include "stm32L1xx_conf.h"

#define CALIPERS_SCL_PIN			GPIO_Pin_2
#define CALIPERS_SCL_PIN_SOURCE		GPIO_PinSource2
#define CALIPERS_SCL_PORT			GPIOA
#define CALIPERS_SCl_CLK			RCC_AHBPeriph_GPIOA

#define CALIPERS_SDA_PIN			GPIO_Pin_1
#define CALIPERS_SDA_PIN_SOURCE		GPIO_PinSource1
#define CALIPERS_SDA_PORT			GPIOA
#define CALIPERS_SDA_CLK			RCC_AHBPeriph_GPIOA





typedef void(*ftVoid_Void)(void);

// ================================= Constants =================================


#define SPI_DATA_IDLE					1
#define SPI_DATA_GET_NEW_BYTE			2
#define SPI_DATA_GET_NEW_POKET			3
#define SPI_DATA_GET_NEW_POKET			3

// ================================ Data types =================================

class calipers_t {
private:

	uint32_t dwPoketTimer;
	uint32_t dwByteTimer;
	char chBitCount, chByteCount;

    bool IsError;
    char chRxDta;
   // I2C_Cmd_t *CmdToWrite, *CmdToRead;
   // I2C_Cmd_t Commands[I2C_CMD_QUEUE_LENGTH];
    // Task-based functions

public:
    uint32_t iSpiDataRx;
    char chSpiDataRxSign;
    ftVoid_Void Callback;
    void Init(void);
    void Task(void);
    void SCL_IRQ(void);
};

extern calipers_t calipers;
extern "C" {

void EXTI2_IRQHandler(void);

}


#endif /* CALIPERSCLASS_H_ */
