/*
 * CalipersClass.h
 *
 *  Created on: 09 окт. 2013 г.
 *      Author: Stefan
 */

#ifndef CALIPERSCLASS_H_
#define CALIPERSCLASS_H_


#include "stm32f10x_conf.h"
#include "stm32f10x.h"
#include "common.h"

#define CALIPERS_SCL_PIN			GPIO_Pin_8
#define CALIPERS_SCL_PORT			GPIOB

#define CALIPERS_SCl_EXTI_PORT_SOURCE			GPIO_PortSourceGPIOB
#define CALIPERS_SCL_EXTI_PIN_SOURCE			GPIO_PinSource8
#define CALIPERS_SCL_EXTI_LINE					EXTI_Line8
#define CALIPERS_SCL_EXTI_IRQ					EXTI9_5_IRQn //EXTI9_5_IRQHandler

#define CALIPERS_SDA_PIN			GPIO_Pin_9
#define CALIPERS_SDA_PORT			GPIOB

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
	bool bGetDataFlag;

public:
	int32_t iSpiDataRx;
	int32_t iTemp;
    ftVoid_uint32 Callback;
    void Init(void);
    void Task(void);
    void SCL_IRQ(void);
    uint8_t GetState(void);
};

extern calipers_t calipers;
extern "C" {

void EXTI9_5_IRQHandler(void);

}


#endif /* CALIPERSCLASS_H_ */
