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

#define VALVE_CH1_PIN			GPIO_Pin_7
#define VALVE_CH1_PORT			GPIOB
#define VALVE_CH2_PIN			GPIO_Pin_6
#define VALVE_CH2_PORT			GPIOB

class ValveControlClass
{
private:
	uint32_t i;
public:
	void Init();
	void Task();
	void SetCh1(uint8_t b);

};


#endif /* VALVECONTROLUNIT_H_ */
