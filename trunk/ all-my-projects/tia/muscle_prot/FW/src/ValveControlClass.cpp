/*
 * ValveControlUnit.cpp
 *
 *  Created on: 30 июля 2014 г.
 *      Author: Stefan
 */
#include "ValveControlClass.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "kl_lib.h"

void ValveControlClass::Init(void)
{
	  RCC_APB1PeriphClockCmd(VALVE_TIM_CLK, ENABLE);

	  /* GPIOA and GPIOB clock enable */
	  klGpioSetupByMsk(VALVE_CH1_PORT,VALVE_CH1_PIN,GPIO_Mode_AF_PP);
	  klGpioSetupByMsk(VALVE_CH2_PORT,VALVE_CH2_PIN,GPIO_Mode_AF_PP);
	 /* -----------------------------------------------------------------------
	    TIM4 Configuration: generate 2 PWM signals with 2 different duty cycles:
	    The TIM4CLK frequency is set to SystemCoreClock (Hz), to get TIM4 counter
	    clock at 24 MHz the Prescaler is computed as following:
	     - Prescaler = (TIM4CLK / TIM4 counter clock) - 1
	    SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
	    and Connectivity line devices and to 24 MHz for Low-Density Value line and
	    Medium-Density Value line devices

	    The TIM4 is running at 93,75 KHz: TIM4 Frequency = TIM4 counter clock/(ARR + 1)
	                                                  = 24 MHz / TOP_PWM_VALUE = 93.75 KHz
	    TIM4 Channel1 duty cycle = (TIM4_CCR1/ TIM4_ARR)* 100
	    TIM4 Channel2 duty cycle = (TIM4_CCR2/ TIM4_ARR)* 100
	  ----------------------------------------------------------------------- */

	  /* Compute the prescaler value */
		uint16_t PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;

	  /* Time base configuration */
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_TimeBaseStructure.TIM_Period = TOP_PWM_VALUE;
	  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	  TIM_TimeBaseInit(VALVE_TIM, &TIM_TimeBaseStructure);

	  /* PWM1 Mode configuration: Channel1 */
	  TIM_OCInitTypeDef  TIM_OCInitStructure;
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 0; // off then init
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  TIM_OC1Init(VALVE_TIM, &TIM_OCInitStructure);
	  TIM_OC1PreloadConfig(VALVE_TIM, TIM_OCPreload_Enable);

	  /* PWM1 Mode configuration: Channel2 */
	  TIM_OC2Init(VALVE_TIM, &TIM_OCInitStructure);
	  TIM_OC2PreloadConfig(VALVE_TIM, TIM_OCPreload_Enable);

	  TIM_ARRPreloadConfig(VALVE_TIM, ENABLE);

	  /* TIM3 enable counter */
	  TIM_Cmd(VALVE_TIM, ENABLE);
}
void ValveControlClass::SetCh1(uint8_t b)
{
	TIM_SetCompare1(VALVE_TIM,b);
}

void ValveControlClass::Task(void)
{

}


