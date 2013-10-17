/*
 * CalipersClass.cpp
 *
 *  Created on: 09 окт. 2013 г.
 *      Author: Stefan
 */

#include "delay_util.h"
#include "CalipersClass.h"
#include "stm32l1xx_gpio.h"

void calipers_t::Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  EXTI_InitTypeDef EXTI_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;

	  /* Enable GPIOs clock */
	  RCC_AHBPeriphClockCmd(CALIPERS_SCl_CLK, ENABLE);

	  /* Configure SPI CLK  pin as input */
	  GPIO_InitStructure.GPIO_Pin = CALIPERS_SCL_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	  GPIO_Init(CALIPERS_SCL_PORT, &GPIO_InitStructure);

	  /* Enable GPIOs clock */
	  RCC_AHBPeriphClockCmd(CALIPERS_SDA_CLK, ENABLE);

	  /* Configure SPI SDA pin as input */
	  GPIO_InitStructure.GPIO_Pin = CALIPERS_SDA_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	  GPIO_Init(CALIPERS_SDA_PORT, &GPIO_InitStructure);

	  /* Connect SPI CLK EXTI Line to GPIO Pin */
	  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource2);

	  /* Configure SPI CLK and EXTI line */
	  EXTI_InitStructure.EXTI_Line = EXTI_Line2 ;  // PA2 forSPI CLK
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  EXTI_Init(&EXTI_InitStructure);

	  /* Enable and set SPI CLK EXTI Interrupt to the lowest priority */
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn ;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

	  Delay.Reset(&dwPoketTimer);
	  Delay.Reset(&dwIdleTimer);
	  chBitCount=0;
	  chSpiState=SPI_IDLE;
}

void calipers_t::Task(void)
{
	if (Delay.Elapsed(&dwIdleTimer,200)) // очень давно небыло данных от штангена
	{
		chSpiState=SPI_IDLE;
	}

}
uint8_t calipers_t::GetState(void)
{
	return chSpiState;
}

void calipers_t::SCL_IRQ(void)
{
	if (Delay.Elapsed(&dwPoketTimer,15))// прошло время между посылками - началась другая посылка
	{
		  chBitCount=0;
		  iSpiDataRx=0;
		  Delay.Reset(&dwIdleTimer); // чтобы не перейти в режим IDLE
		  chSpiState=SPI_START_RX;
		  if(Callback != 0)Callback();
	}
	//Delay.Reset(&dwPoketTimer);
	chBitCount++;
	//  биты 1,17,18,19,20,21,23 не считаем
	if ((chBitCount==1) |(chBitCount==17)| (chBitCount==18)|(chBitCount==19)|(chBitCount==20)|(chBitCount==21)|(chBitCount==23)) return;
	if (chBitCount==22) // 22 бит - знаковый
	{
		if (!GPIO_ReadInputDataBit(CALIPERS_SDA_PORT,CALIPERS_SDA_PIN)) iSpiDataRx*=-1;
		return;
	}
	if (chBitCount==24) // 24-й тоже не считаем, он последний, возвращаем результат.
	{
		chSpiState=SPI_END_RX;
		if(Callback != 0) Callback();
		return;
	}
	if (!GPIO_ReadInputDataBit(CALIPERS_SDA_PORT,CALIPERS_SDA_PIN)) iSpiDataRx+=(1<<(chBitCount-2));
}

void EXTI2_IRQHandler(void)
{
	calipers.SCL_IRQ();
	EXTI_ClearITPendingBit(EXTI_Line2);
}
