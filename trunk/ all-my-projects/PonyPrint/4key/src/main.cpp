/*
 * File:   main.cpp
 * Author: Kreyl
 *
 * Created on May 27, 2011, 6:37 PM
 */

#include "stm32f10x.h"
#include "GPIO_config.h"
#include "delay_util.h"

//#include "i2c_mgr.h"
#include "common.h"
#include "kl_lib.h"


#include "UARTClass.h"

//#include "motor_class.h"
//#include <string.h>
//#include <stdio.h>
#define DEBUG_LED_TIMEOUT	1000
#define USER_BATTON_TIMEOUT	250

void GeneralInit(void);


UART_Class DbgUART;
UART_Class ComportUART;
UART_Class* pUART1;
UART_Class* pUART2;
UART_Class* pUART3;
UART_Class* pUART4;
UART_Class* pUART5;



//i2cMgr_t i2cMgr;
uint32_t iTemp;


int main(void)
{
	uint32_t iDebugLedTimer;
	uint32_t iUserBattonTimer;
	uint32_t iUserBattonFlag=0;
	uint32_t flag=0;

	uint32_t iButton_A_Timer;
	uint32_t iButton_A_Flag=0;

	uint32_t iButton_B_Timer;
	uint32_t iButton_B_Flag=0;

	uint32_t iButton_C_Timer;
	uint32_t iButton_C_Flag=0;

	uint32_t iButton_D_Timer;
	uint32_t iButton_D_Flag=0;

	uint32_t count;

	Delay.Init();
	GeneralInit();
	DbgUART.UART_Init(USART1);

	//DbgUART.SendPrintF("Hello word %d \n",24);

	Delay.Reset(&iDebugLedTimer);
	Delay.Reset(&iUserBattonTimer);
	iUserBattonFlag=1;
    while(1)
    {
// --------------- user button --------------
    	if (UserButtonPressed())
    	{
    		if (iUserBattonFlag==0)
    		{
    			iUserBattonFlag=1;
    			Delay.Reset(&iUserBattonTimer);
    			DbgUART.SendByte('Z');
    		}
    	}
    	else if (Delay.Elapsed(&iUserBattonTimer,USER_BATTON_TIMEOUT)) iUserBattonFlag=0;

 //-------------------------------------------------------------------------
	// --------------- A button --------------
		if (Button_A_Pressed())
		{
			if (iButton_A_Flag==0)
			{
				iButton_A_Flag=1;
				Delay.Reset(&iButton_A_Timer);
				DbgUART.SendByte('A');
			}
		}
		else if (Delay.Elapsed(&iButton_A_Timer,USER_BATTON_TIMEOUT)) iButton_A_Flag=0;

 //-------------------------------------------------------------------------
	// --------------- B button --------------
		if (Button_B_Pressed())
		{
			if (iButton_B_Flag==0)
			{
				iButton_B_Flag=1;
				Delay.Reset(&iButton_B_Timer);
				DbgUART.SendByte('B');
			}
		}
		else if (Delay.Elapsed(&iButton_B_Timer,USER_BATTON_TIMEOUT)) iButton_B_Flag=0;

	//-------------------------------------------------------------------------
	// --------------- C button --------------
		if (Button_C_Pressed())
		{
			if (iButton_C_Flag==0)
			{
				iButton_C_Flag=1;
				Delay.Reset(&iButton_C_Timer);
				DbgUART.SendByte('C');
			}
		}
		else if (Delay.Elapsed(&iButton_C_Timer,USER_BATTON_TIMEOUT)) iButton_C_Flag=0;

 //-------------------------------------------------------------------------
	// --------------- D button --------------
		if (Button_D_Pressed())
		{
			if (iButton_D_Flag==0)
			{
				iButton_D_Flag=1;
				Delay.Reset(&iButton_D_Timer);
				DbgUART.SendByte('D');
			}
		}
		else if (Delay.Elapsed(&iButton_D_Timer,USER_BATTON_TIMEOUT)) iButton_D_Flag=0;

 //-------------------------------------------------------------------------

 //------------ debug led and e.t.c. ---------------------------------------
    	if (Delay.Elapsed(&iDebugLedTimer,DEBUG_LED_TIMEOUT))
    	{
    		if (flag==0)
    			{

    				BLedDiscOn();
    				flag=1;
    			}
    			else
    			{
    				BLedDiscOff();
    				flag=0;
    			}
    	}
//-------------------------------------------------------------------------
    }
}

void GeneralInit(void) {
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
    /* Configure USER_BUTTON */
    klGpioSetupByMsk(USER_BUTTON_PORT,USER_BUTTON_PIN,GPIO_Mode_IN_FLOATING);

    klGpioSetupByMsk(BUTTON_A_PORT,BUTTON_A_PIN,GPIO_Mode_IPU);
    klGpioSetupByMsk(BUTTON_B_PORT,BUTTON_B_PIN,GPIO_Mode_IPU);
    klGpioSetupByMsk(BUTTON_C_PORT,BUTTON_C_PIN,GPIO_Mode_IPU);
    klGpioSetupByMsk(BUTTON_D_PORT,BUTTON_D_PIN,GPIO_Mode_IPU);


}
