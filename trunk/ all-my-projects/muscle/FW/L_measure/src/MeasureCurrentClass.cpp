/*
 * MeasureCurrentClass.cpp
 *
 *  Created on: 30 сент. 2013 г.
 *      Author: Stefan
 *      for current measurement
 *
 */

#include "stm32l1xx.h"
#include "discover_board.h"
#include "MeasureCurrentClass.h"
#include "delay_util.h"

char chMeasureCurFlag;
void MesureCurInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	  RCC_AHBPeriphClockCmd(N_GATE2_GPIO_PORT_CLK 	| P_GATE1_GPIO_PORT_CLK |
			  	  	  	  P_GATE2_GPIO_PORT_CLK 	| N_GATE1_GPIO_PORT_CLK , ENABLE);
	  /* Configure the MOSFET driver pins */

	  GPIO_InitStructure.GPIO_Pin = P_GATE1_GPIO_PIN ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(P_GATE1_GPIO_PORT, &GPIO_InitStructure);
	  GPIO_HIGH(P_GATE1_GPIO_PORT, P_GATE1_GPIO_PIN);

	  GPIO_InitStructure.GPIO_Pin = P_GATE2_GPIO_PIN ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(P_GATE2_GPIO_PORT, &GPIO_InitStructure);
	  GPIO_HIGH(P_GATE2_GPIO_PORT, P_GATE2_GPIO_PIN);

	  GPIO_InitStructure.GPIO_Pin = N_GATE1_GPIO_PIN ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(N_GATE1_GPIO_PORT, &GPIO_InitStructure);
	  GPIO_LOW(N_GATE1_GPIO_PORT, N_GATE1_GPIO_PIN);

	  GPIO_InitStructure.GPIO_Pin = N_GATE2_GPIO_PIN ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	  GPIO_Init(N_GATE2_GPIO_PORT, &GPIO_InitStructure);
	  GPIO_LOW(N_GATE2_GPIO_PORT, N_GATE2_GPIO_PIN);


}

void MesureCurStop(void)
{
	GPIO_HIGH(P_GATE1_GPIO_PORT, P_GATE1_GPIO_PIN);
	GPIO_HIGH(P_GATE2_GPIO_PORT, P_GATE2_GPIO_PIN);
	GPIO_LOW(N_GATE1_GPIO_PORT, N_GATE1_GPIO_PIN);
	GPIO_LOW(N_GATE2_GPIO_PORT, N_GATE2_GPIO_PIN);
	chMeasureCurFlag=MEASURE_CUR_STOP;
}

void MesureCurUpward(void)
{
		// off R-arm
	GPIO_HIGH(P_GATE2_GPIO_PORT, P_GATE2_GPIO_PIN);
	GPIO_LOW(N_GATE2_GPIO_PORT, N_GATE2_GPIO_PIN);
	// ждем закрытия транзисторов
	Delay.ms(SWITCH_DELAY);
	// on L-arm
	GPIO_LOW(P_GATE1_GPIO_PORT, P_GATE1_GPIO_PIN);
	GPIO_HIGH(N_GATE1_GPIO_PORT, N_GATE1_GPIO_PIN);
	chMeasureCurFlag=MEASURE_CUR_UP;
	}

void MesureCurDownward(void)
{
	// off L-arm
	GPIO_HIGH(P_GATE1_GPIO_PORT,P_GATE1_GPIO_PIN);
    GPIO_LOW(N_GATE1_GPIO_PORT,N_GATE1_GPIO_PIN);
	// ждем закрытия транзисторов
	Delay.ms(SWITCH_DELAY);
	// on R-arm
	GPIO_LOW(P_GATE2_GPIO_PORT,P_GATE2_GPIO_PIN);
    GPIO_HIGH(N_GATE2_GPIO_PORT,N_GATE2_GPIO_PIN);
	chMeasureCurFlag=MEASURE_CUR_DOWN;
}

void MesureCurToggle(void)
{
	switch  (chMeasureCurFlag)
	{
	case MEASURE_CUR_UP:
		MesureCurDownward();
		break;
	case MEASURE_CUR_DOWN:
		MesureCurUpward();
	}

}



