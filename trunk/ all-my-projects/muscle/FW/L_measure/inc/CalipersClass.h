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

#define SPI_IDLE					0
#define SPI_START_RX					1
#define SPI_END_RX						2

// ================================ Data types =================================

class calipers_t {
private:

	uint32_t dwPoketTimer;
	uint32_t dwIdleTimer;
	char chBitCount;
	uint8_t chSpiState;

public:
    uint32_t iSpiDataRx;
    ftVoid_Void Callback;
    void Init(void);
    void Task(void);
    void SCL_IRQ(void);
    uint8_t GetState(void);
};

extern calipers_t calipers;
extern "C" {

void EXTI2_IRQHandler(void);

}


#endif /* CALIPERSCLASS_H_ */
