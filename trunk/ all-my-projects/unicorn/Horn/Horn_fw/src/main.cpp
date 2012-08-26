/*
 * File:   main.cpp
 * Author: Kreyl
 *
 * Created on May 27, 2011, 6:37 PM
 */

#include "stm32f10x.h"

#include "delay_util.h"
#include "UARTClass.h"
#include "GPIO_config.h"
#include "i2c_mgr.h"
#include <string.h>
#include <stdio.h>

#define DEBUG_LED_TIMEOUT	400
#define DELAY_I2C_TIMEOUT	10



//#define I2C_SLAVE_ADDR			0x62 // другой будет 0x60.
#define ADC_VALUE_MAS_SIZE 			80 // размер массива, где хранятся значения для подсчета скользящего среднего


UART_Class* pUART1;
UART_Class* pUART2;
UART_Class* pUART3;
UART_Class* pUART4;
UART_Class* pUART5;


void CallBackI2C(void);
void GeneralInit(void);
void MainControl(void);
UART_Class DbgUART;


I2C_Cmd_t I2C_command;
uint8_t chflagI2C;

int main(void) {
	uint32_t iDebugLedTimer;
	uint32_t iI2cDelayTimer;

    DbgUART.UART_Init(USART2);
    i2cMgr.Init();
    i2cMgr.SetDbgUART(&DbgUART);

    Delay.ms(100);
    uint32_t flag=0;
    GeneralInit();



    //sprintf(str,"Hello word %в  \n",56);
   // DbgUART.FIFO_TxData.WriteData(24,(uint8_t*) str);
    DbgUART.SendPrintF("Hello word %d \n",24);
    //DbgUART.SendPrintF("00000000001111111111222222222233333333334444444444555555555566666666667777777777");

    Delay.Reset(&iDebugLedTimer);


    uint8_t rxBuf[3];
    uint8_t txBuf[16];
    uint8_t chByte[2];

    uint16_t iPocketCounter=0; // тут считаем, сколько пакетов в секунду нам удается получить
    int16_t* iCurentAdcValue;
    iCurentAdcValue=(int16_t*)chByte; // теперь тут будет лежать последнее измеренное число
    int16_t AdcValueMas[ADC_VALUE_MAS_SIZE];
    uint16_t iAdcValMasCounter=0;
    int16_t iScolzSredn=0;
    int32_t iAccum=0;
    uint16_t i=0;



    // Setup i2cCmd
    I2C_command.Address=0x48;
    I2C_command.DataToRead.Length = 4;
    I2C_command.DataToRead.Buf=rxBuf;
    I2C_command.DataToWrite.Buf = txBuf;
    I2C_command.DataToWrite.Length = 0;
    I2C_command.Callback=CallBackI2C;


    Led1Off();
    Led2Off();
    Led3Off();
    Led4Off();

    while(1)
    {

    	if ((Delay.Elapsed(&iI2cDelayTimer,DELAY_I2C_TIMEOUT)))
    	{

    			iPocketCounter++;
    			AdcValueMas[iAdcValMasCounter]=*iCurentAdcValue;
    			iAdcValMasCounter++;
    			if (iAdcValMasCounter==ADC_VALUE_MAS_SIZE)iAdcValMasCounter=0;
    			i2cMgr.AddCmd(I2C_command);
    			//DbgUART.SendPrintF("rxBuf contents %X %X %X %X \n", rxBuf[0], rxBuf[1], rxBuf[2], rxBuf[3]);
    			//chflagI2C=0;
    	}
    	if (Delay.Elapsed(&iDebugLedTimer,DEBUG_LED_TIMEOUT))
    	{
    		if (flag==0)
    			{
    				Led1On();
    				flag=1;
    				//DbgUART.SendPrintF("iPocketCounter = %d \n",iPocketCounter);
    				//if (iPocketCounter==0) i2cMgr.AddCmd(I2C_command);
    				iPocketCounter=0;

    				iAccum=0;
    				i=0;
    				while (i<ADC_VALUE_MAS_SIZE)
    				{
    					iAccum+=AdcValueMas[i];
    					i++;
    				}
    				iScolzSredn=iAccum/ADC_VALUE_MAS_SIZE;

    				//DbgUART.SendPrintF("ADC curren value= %d \n",*iCurentAdcValue);



    			}
    			else
    				{
    					//DbgUART.SendPrintF("rxBuf contents %X %X %X %X \n", rxBuf[0], rxBuf[1], rxBuf[2], rxBuf[3]);
    					chByte[0]=rxBuf[1];
    					chByte[1]=rxBuf[0];
    					DbgUART.SendPrintF("ADC curren value= %d  SrZnach = %d \n",*iCurentAdcValue,iScolzSredn);
    					Led1Off();
    					flag=0;
    				}
    	}


    	i2cMgr.Task();


    } // while(1)
    return 0;
}

void CallBackI2C(void)
{
	chflagI2C=1;
}

void GeneralInit(void) {
    // Disable JTAG
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    // Configure two bits for preemption priority
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

    // Init peripheral
    i2cMgr.Init();
    Delay.Init();

    RCC_APB2PeriphClockCmd(
    		LED_1_CLK |
    		LED_2_CLK |
    		LED_3_CLK |
    		LED_4_CLK |
    		WARNING_UP_CLK |
        RCC_APB2Periph_AFIO,
        ENABLE );

    GPIO_InitTypeDef GPIO_InitStructure;

    // светодиоды
    /* Configure LED_1_PIN as Output */
    GPIO_InitStructure.GPIO_Pin =  LED_1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( LED_1_PORT, &GPIO_InitStructure );
    /* Configure LED_2_PIN as Output */
    GPIO_InitStructure.GPIO_Pin =  LED_2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( LED_2_PORT, &GPIO_InitStructure );
    /* Configure LED_3_PIN as Output */
    GPIO_InitStructure.GPIO_Pin =  LED_3_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( LED_3_PORT, &GPIO_InitStructure );
    /* Configure LED_4_PIN as Output */
    GPIO_InitStructure.GPIO_Pin =  LED_4_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( LED_4_PORT, &GPIO_InitStructure );


    GPIO_InitStructure.GPIO_Pin =  WARNING_UP_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( WARNING_UP_PORT, &GPIO_InitStructure );

    GPIO_SetBits(WARNING_UP_PORT,WARNING_UP_PIN);




}

