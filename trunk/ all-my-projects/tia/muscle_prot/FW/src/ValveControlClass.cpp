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
#include "delay_util.h"

/**************** Описание работы *************************
 * Таймер делает 10 итераций за секунду.
 * Управляется командой, состоящей из значения скважности и количества итераций.
 * В каждую итерацию он открывает клапан с заданой скважностью
 * Перед началом итерации от отправляет текущую скважность в uplink
 * новая команда отменяет предыдущую.
 * новая команда начинает действовать в конце текущей итерации
 */

/************************   ValvePwmClass   ****************
 *
 ***********************************************************/
void ValvePwmClass::Init(TIM_TypeDef* TIMx,uint8_t bChanel)
{
	 /* -----------------------------------------------------------------------
		TIM4 Configuration: generate 2 PWM signals with 2 different duty cycles:
		The TIM4CLK frequency is set to SystemCoreClock (Hz), to get TIM4 counter
		clock at 4 kHz the Prescaler is computed as following:
		 - Prescaler = (TIM4CLK / TIM4 counter clock) - 1
		SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
		and Connectivity line devices and to 24 MHz for Low-Density Value line and
		Medium-Density Value line devices

		The TIM4 is running at 10 Hz: TIM4 Frequency = TIM4 counter clock/(ARR + 1)
													  = 2.55 kHz / TOP_PWM_VALUE = 10 Hz
		TIM4 Channel1 duty cycle = (TIM4_CCR1/ TIM4_ARR)* 100
		TIM4 Channel2 duty cycle = (TIM4_CCR2/ TIM4_ARR)* 100
	  ----------------------------------------------------------------------- */

	  /* Compute the prescaler value */
		uint16_t PrescalerValue = (uint16_t) (SystemCoreClock / 2550) - 1; // 4000 - 6000

	    NVIC_InitTypeDef NVIC_InitStructure;

    switch ((uint32_t)TIMx)
    {
      case ((uint32_t)TIM1_BASE):
				NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn ;
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
      	  	  if (bChanel==4)klGpioSetupByMsk(VALVE_TIM1_CH4_PORT,VALVE_TIM1_CH4_PIN,GPIO_Mode_AF_PP);
      	  	  pTIM1=this;
    		  break;
      case ((uint32_t)TIM3_BASE):
				NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;
      	  	  GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); // remap to C6, C7, C8, C9
      	  	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
      	  	  if (bChanel==1)klGpioSetupByMsk(VALVE_TIM3_CH1_PORT,VALVE_TIM3_CH1_PIN,GPIO_Mode_AF_PP);
      	  	  pTIM3=this;
    		  break;
      case ((uint32_t)TIM4_BASE):
				NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;
			  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
      	  	  if (bChanel==2)	klGpioSetupByMsk(VALVE_TIM4_CH2_PORT,VALVE_TIM4_CH2_PIN,GPIO_Mode_AF_PP);
      	  	  pTIM4=this;
    		  break;
    }
	  /* Time base configuration */
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_TimeBaseStructure.TIM_Period = TOP_PWM_VALUE;
	  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	  TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	  /* PWM1 Mode configuration */
	  TIM_OCInitTypeDef  TIM_OCInitStructure;
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 0; // off then init
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    switch (bChanel)
    {
    case 1:
	  	TIM_OC1Init(TIMx, &TIM_OCInitStructure);
	  	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
    	break;
    case 2:
	  	TIM_OC2Init(TIMx, &TIM_OCInitStructure);
	  	TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
    	break;
    case 4:
	  	TIM_OC4Init(TIMx, &TIM_OCInitStructure);
	  	TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
    	break;
    }
    // Interrupt config
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ARRPreloadConfig(TIMx, ENABLE);
	  /* TIM enable counter */
	  TIM_Cmd(TIMx, ENABLE);

	  TIM_ClearFlag(TIMx, TIM_FLAG_Update);
	  /* TIM IT enable */
	  TIM_ITConfig(TIMx,TIM_IT_Update, ENABLE);

	  myTIM=TIMx;
	  myChanel=bChanel;
}

void ValvePwmClass::SetChanel(uint8_t bPwmPower)
{
    switch (myChanel)
    {
    case 1:
	  	TIM_SetCompare1(myTIM,bPwmPower);
    	break;
    case 2:
	  	TIM_SetCompare2(myTIM,bPwmPower);
    	break;
    case 4:
    	TIM_SetCompare4(myTIM,bPwmPower);
    	break;
    }
}

void ValvePwmClass::PauseToClose(uint8_t bNextPwm)
{
    switch (myChanel)
    {
    case 1:
    	TIM_OC1PreloadConfig(myTIM, TIM_OCPreload_Disable); // выключается система прелоадет-регистров
    	SetChanel(0);										// напрямую записывается ноль в значение PWM
    	TIM_SetCounter(myTIM,TOP_PWM_VALUE-MIN_CLOSE_DALAY);// Счетчик устанавливается в обратный отсчет паузы
    	TIM_OC1PreloadConfig(myTIM, TIM_OCPreload_Enable); // включаем  прелоадет регистр, следующее значение в PWM будет записано при переполнении счетчика
    	break;
    case 2:
    	TIM_OC2PreloadConfig(myTIM, TIM_OCPreload_Disable);
    	SetChanel(0);
    	TIM_SetCounter(myTIM,TOP_PWM_VALUE-MIN_CLOSE_DALAY);
    	TIM_OC2PreloadConfig(myTIM, TIM_OCPreload_Enable);
    	break;
    case 4:
    	TIM_OC4PreloadConfig(myTIM, TIM_OCPreload_Disable);
    	SetChanel(0);
    	TIM_SetCounter(myTIM,TOP_PWM_VALUE-MIN_CLOSE_DALAY);
    	TIM_OC4PreloadConfig(myTIM, TIM_OCPreload_Enable);
    	break;
    }
    uiIterationCounter=0;
    SetChanel(bNextPwm);
}

void ValvePwmClass::TIM_InterruptHandler(void)
{
	uiIterationCounter++;
}
// ================================ Interrupts =================================
void TIM1_UP_TIM16_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update); // Clear update interrupt
	pTIM1->TIM_InterruptHandler();
}
void TIM4_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);// Clear update interrupt
	pTIM4->TIM_InterruptHandler();
}
void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);// Clear update interrupt
	pTIM3->TIM_InterruptHandler();
}

/**************************************************************************************/

/**********************  ValveControlClass ********************************************/
// содержит логику управления клапаном
/**************************************************************************************/
void ValveControlClass::Init(ValvePwmClass* pPwm)
{
	this->pPwm=pPwm;
	uiLastIterationNamber=pPwm->uiIterationCounter;
}

void ValveControlClass::Task(void)
{
	if (uiLastIterationNamber!=(pPwm->uiIterationCounter)) // был один импульс PWM ( прошло 0.1 сек)
	{
		uiLastIterationNamber=pPwm->uiIterationCounter;
		if (Callback!=0)Callback(bCurCommandPower); //тут отправляем значение Power  через uplink

		if (bCurCommandPower!=0)
		{
			if (uiLastIterationNamber>=bCurCommandCount )
			{
				pPwm->SetChanel(0); // отключаем выход (сработает в следующем цикле)
				bCurCommandPower=0;
			}
		}
	}
}
void ValveControlClass::GetNewCommand(uint8_t bCommandNamber, uint8_t bCommandPower)
{
	bCurCommandPower=bCommandPower;
	bCurCommandCount=bCommandNamber;
	pPwm->PauseToClose(bCurCommandPower);
}

/**************************************************************************************/
