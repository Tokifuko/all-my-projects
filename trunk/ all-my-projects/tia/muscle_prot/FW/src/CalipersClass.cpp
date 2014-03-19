/*
 * CalipersClass.cpp
 *
 *  Created on: 09 окт. 2013 г.
 *      Author: Stefan
 */

#include "delay_util.h"
#include "CalipersClass.h"
#include "kl_lib.h"

void calipers_t::Init(void)
{
	  EXTI_InitTypeDef EXTI_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;

	  /* Enable GPIOs clock */

	 // klGpioSetupByMsk(CALIPERS_SCL_PORT,CALIPERS_SCL_PIN,GPIO_Mode_AF_OD);
	  klGpioSetupByMsk(CALIPERS_SCL_PORT,CALIPERS_SCL_PIN,GPIO_Mode_IN_FLOATING);
	  klGpioSetupByMsk(CALIPERS_SDA_PORT,CALIPERS_SDA_PIN,GPIO_Mode_IN_FLOATING);

	  /* Connect EXTI Line to CALIPERS_SCL pin */
	  GPIO_EXTILineConfig(CALIPERS_SCl_EXTI_PORT_SOURCE, CALIPERS_SCL_EXTI_PIN_SOURCE);

	  /* Configure CALIPERS_SCL_EXTI line */
	  EXTI_InitStructure.EXTI_Line = CALIPERS_SCL_EXTI_LINE;
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  EXTI_Init(&EXTI_InitStructure);

	  /* Enable and set CALIPERS_SCL_EXTI Interrupt to the lowest priority */
	  NVIC_InitStructure.NVIC_IRQChannel = CALIPERS_SCL_EXTI_IRQ;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
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

	if (bGetDataFlag)
	{
		bGetDataFlag=false;
		if(Callback != 0) Callback(0);
	}

}
uint8_t calipers_t::GetState(void)
{
	return chSpiState;
}

void calipers_t::SCL_IRQ(void)
{
	uint8_t bPin=GPIO_ReadInputDataBit(CALIPERS_SDA_PORT,CALIPERS_SDA_PIN);

	if (Delay.Elapsed(&dwPoketTimer,15))// прошло время между посылками - началась другая посылка
	{
		  chBitCount=0;
		  iSpiDataRx=0;
		  Delay.Reset(&dwIdleTimer); // чтобы не перейти в режим IDLE
		  chSpiState=SPI_START_RX;
	}
	//Delay.Reset(&dwPoketTimer);
	//Delay.ms(1);
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
		bGetDataFlag=true;
		iTemp=iSpiDataRx;
		return;
	}
	if (!bPin) iSpiDataRx+=(1<<(chBitCount-2));
}

void EXTI9_5_IRQHandler(void)
{
	calipers.SCL_IRQ();
	EXTI_ClearITPendingBit(CALIPERS_SCL_EXTI_LINE);
}
