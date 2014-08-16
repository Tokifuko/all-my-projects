/*
 * ValveControlUnit.h
 *
 *  Created on: 30 июля 2014 г.
 *      Author: Stefan
 */

#ifndef VALVECONTROLUNIT_H_
#define VALVECONTROLUNIT_H_

#include "stm32f10x_conf.h"

#define TOP_PWM_VALUE	255
#define VALVE_TIM		TIM4
#define VALVE_TIM_CLK		RCC_APB1Periph_TIM4

#define VALVE_CH1_PIN			GPIO_Pin_6
#define VALVE_CH1_PORT			GPIOB
#define VALVE_CH2_PIN			GPIO_Pin_7
#define VALVE_CH2_PORT			GPIOB

class DoubleChanelPwmClass
{
public:
	void Init();
	void SetCh1(uint8_t b){TIM_SetCompare1(VALVE_TIM,b);};
	void SetCh2(uint8_t b){TIM_SetCompare2(VALVE_TIM,b);};
};

class ValveControlClass
{
private:
	uint32_t dwCommandTimer;
	DoubleChanelPwmClass* pPwm;
	uint8_t bPwmChanelNamber;
	uint8_t bCurCommandTime;
	uint8_t bCurCommandPwm;
	bool isValveActiv;
public:
	void Init(DoubleChanelPwmClass* pPwm, uint8_t bPwmChanelNamber);
	void Task();
	void Open(uint8_t bCommandTime, uint8_t bCommandPower);
	void Close();
};


#endif /* VALVECONTROLUNIT_H_ */
