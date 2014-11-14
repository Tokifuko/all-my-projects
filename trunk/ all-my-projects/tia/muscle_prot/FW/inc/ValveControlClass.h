/*
 * ValveControlUnit.h
 *
 *  Created on: 30 июля 2014 г.
 *      Author: Stefan
 */

#ifndef VALVECONTROLUNIT_H_
#define VALVECONTROLUNIT_H_

#include "stm32f10x_conf.h"
#include "common.h"

#define TOP_PWM_VALUE				255
#define MIN_CLOSE_DALAY				200 // в милисекундах

#define VALVE_TIM4_CH2_PIN			GPIO_Pin_7
#define VALVE_TIM4_CH2_PORT			GPIOB

#define VALVE_TIM3_CH1_PIN			GPIO_Pin_6
#define VALVE_TIM3_CH1_PORT			GPIOC

#define VALVE_TIM1_CH4_PIN			GPIO_Pin_11
#define VALVE_TIM1_CH4_PORT			GPIOA


class ValvePwmClass
{
private:
	TIM_TypeDef* myTIM;
	uint8_t myChanel;
public:
	void Init(TIM_TypeDef* TIMx,uint8_t bChanel);
	void SetChanel(uint8_t bPwmPower);
	void PauseToClose(uint8_t bNextPwm);
	uint32_t uiIterationCounter;
	void TIM_InterruptHandler(void);
};

class ValveControlClass
{
private:
	ValvePwmClass* pPwm;
	uint8_t bCurCommandPower;
	uint8_t bCurCommandCount;
	uint32_t uiLastIterationNamber;
	void SendState(void);
public:
	void Init(ValvePwmClass* pPwm);
	void Task();
	void GetNewCommand(uint8_t bCommandTime, uint8_t bCommandPower);
	ftVoid_uint32 Callback;
};

extern ValvePwmClass* pTIM1; // no use
extern ValvePwmClass* pTIM3;
extern ValvePwmClass* pTIM4;
// Declare Timer IRQ. Use externC to make it visible from asm file.
extern "C" {
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM1_UP_TIM16_IRQHandler(void);
}


#endif /* VALVECONTROLUNIT_H_ */
