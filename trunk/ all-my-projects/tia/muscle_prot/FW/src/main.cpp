/*
 * File:   main.cpp
 * Author: Kreyl
 *
 * Created on May 27, 2011, 6:37 PM
 */

#include "stm32f10x.h"
#include "GPIO_config.h"
#include "delay_util.h"
#include "ad7799.h"

#include "UARTClass.h"

//#include "motor_class.h"
//#include <string.h>
//#include <stdio.h>
#define DEBUG_LED_TIMEOUT	1000

void GeneralInit(void);
void Ad7799Callback(uint32_t iData);

UART_Class DbgUART;
UART_Class* pUART1;
UART_Class* pUART2;
UART_Class* pUART3;
UART_Class* pUART4;
UART_Class* pUART5;

AD7799_Class ad7799;
uint32_t iTemp;

int main(void)
{
	uint32_t iDebugLedTimer;
	uint32_t flag=0;

	Delay.Init();
	GeneralInit();
	DbgUART.UART_Init(USART1);
	ad7799.Init();
	ad7799.Callback=Ad7799Callback;
	DbgUART.SendPrintF("Hello word %d \n",24);

	Delay.Reset(&iDebugLedTimer);
    while(1)
    {
    	ad7799.Task();
       // while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        /* Send SPI1 data */
        //SPI_I2S_SendData(SPI1, 0x5555);

    if (Delay.Elapsed(&iDebugLedTimer,DEBUG_LED_TIMEOUT))
    	{
    	//SPI_I2S_SendData(SPI_MASTER,0x5555);

    		if (flag==0)
    			{
    				BLedDiscOn();
    				flag=1;
    				//ad7799.PswPinOn();
    			}
    			else
    			{
    				BLedDiscOff();
    				flag=0;
    				//ad7799.PswPinOff();
    			}
    	}
    }
}

void GeneralInit(void) {
    //Delay.Init();
    RCC_APB2PeriphClockCmd(
    		LED_2_CLK |
    		G_LED_DISC_CLK |
    		B_LED_DISC_CLK |
    		USER_BUTTON_CLK,
      //  RCC_APB2Periph_AFIO,  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        ENABLE );
    // Disable JTAG
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    // светодиоды
    /* Configure LED_2_PIN as Output */
    GPIO_InitStructure.GPIO_Pin =  LED_2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( LED_2_PORT, &GPIO_InitStructure );
    Led2Off();

    GPIO_InitStructure.GPIO_Pin =  G_LED_DISC_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( G_LED_DISC_PORT, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin =  B_LED_DISC_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( B_LED_DISC_PORT, &GPIO_InitStructure );

    // кнопки ручного управления
    /* Configure KEY_DOWN_PIN as INPUT PULLUP */
    GPIO_InitStructure.GPIO_Pin = USER_BUTTON_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( USER_BUTTON_PORT, &GPIO_InitStructure );
}

void Ad7799Callback(uint32_t iData)
{
/*	iTemp++;
	if (iTemp>1)
	{
		DbgUART.SendPrintF("Tenzo=%d \n",iData);

	iTemp=0;
	}
*/
	DbgUART.SendPrintF("Tenzo=%d \n",iData);
}
