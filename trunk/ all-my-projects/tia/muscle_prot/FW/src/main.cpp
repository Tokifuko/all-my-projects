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
#include "ms5803_spi.h"
//#include "i2c_mgr.h"
#include "common.h"
#include "kl_lib.h"
#include "CalipersClass.h"
#include "uplink_unit.h"

#include "UARTClass.h"

//#include "motor_class.h"
//#include <string.h>
//#include <stdio.h>
#define DEBUG_LED_TIMEOUT	1000
#define USER_BATTON_TIMEOUT	100

void GeneralInit(void);
void Ad7799Callback(uint32_t iData);
void Ms5803Callback(uint32_t iData);
void CallBackCalipers(uint32_t iData);

UART_Class DbgUART;
UART_Class ComportUART;
UART_Class* pUART1;
UART_Class* pUART2;
UART_Class* pUART3;
UART_Class* pUART4;
UART_Class* pUART5;

AD7799_Class ad7799;
MS5803_Class ms5803;
UplinkClass uplink;
//i2cMgr_t i2cMgr;
uint32_t iTemp;
calipers_t calipers;

int main(void)
{
	uint32_t iDebugLedTimer;
	uint32_t iUserBattonTimer;
	uint32_t flag=0;
	uint32_t iUserBattonFlag=0;
	uint32_t count;
	DataPack_t tTestData;
	/*uint8_t dataBufTxReset[4]={0x1E,0,0,0};
	uint8_t dataBufTxRead[4]={0xA4,0,0,0};
	uint8_t dataBufRx[4]={0,0,0,0};
*/
	Delay.Init();
	GeneralInit();
	DbgUART.UART_Init(USART1);
	ComportUART.UART_Init(USART3);
	ad7799.Init();
	ad7799.Callback=Ad7799Callback;
	ms5803.Init();
	ms5803.Callback=Ms5803Callback;
	ms5803.DbgUART=&DbgUART;

	uplink.Init(0);
	uplink.SetUart(&ComportUART);
	//i2cMgr.Init();
	calipers.Init();
	calipers.Callback=CallBackCalipers;

	DbgUART.SendPrintF("Hello word %d \n",24);

	Delay.Reset(&iDebugLedTimer);
	Delay.Reset(&iUserBattonTimer);
    while(1)
    {
     ad7799.Task();
   	ms5803.Task();
    	//Delay.ms(500);
  	  calipers.Task();
  	uplink.Task();
    	//i2cMgr.Task();
// --------------- user button start callibration process --------------
    	if (UserButtonPressed())
    	{
    		if (iUserBattonFlag==0)
    		{
    			iUserBattonFlag=1;
    			Delay.Reset(&iUserBattonTimer);
    			ad7799.StartZeroCalibration();
    			//i2cMgr.AddCmd(comReset);  // Reset command
				tTestData.Addr=0x11;
				tTestData.Command=0xFF;
				tTestData.Data=0x33445566;
				count =0;
				while (count<20)
				{
					uplink.Send(&tTestData);
					count++;
				}
    		}
    	}
    	else if (Delay.Elapsed(&iUserBattonTimer,USER_BATTON_TIMEOUT))
				{
					iUserBattonFlag=0;
					ad7799.PswPinOff();
				}
 //-------------------------------------------------------------------------
 //------------ debug led and e.t.c. ---------------------------------------
    	if (Delay.Elapsed(&iDebugLedTimer,DEBUG_LED_TIMEOUT))
    	{
    		if (flag==0)
    			{
    				BLedDiscOn();
    				flag=1;

    				//GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    				ms5803.SendReset();
    				//i2cMgr.AddCmd(comRead);
    				ad7799.PswPinOn();


    			}
    			else
    			{
    				//GPIO_SetBits(GPIOB,GPIO_Pin_12);
    				//i2cMgr.AddCmd(comReadStart);
    				//DbgUART.SendPrintF("Temp=%d \n",ms5803.GetTemp());

    			  //  Delay.ms(100);
    				BLedDiscOff();
    				flag=0;
    				ad7799.PswPinOff();
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
    GPIO_InitStructure.GPIO_Pin = USER_BUTTON_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( USER_BUTTON_PORT, &GPIO_InitStructure );
}

void Ad7799Callback(uint32_t iData)
{
	DataPack_t sDataPack;
	sDataPack.Addr=DATA_PACK_ADDR_TENZO;
	sDataPack.Data=iData;
	uplink.Send(&sDataPack);
	/*iTemp++;
	if (iTemp>100)
	{
		//DbgUART.SendPrintF("Tenzo=%d \n",iData);

	iTemp=0;
	}
*/
	DbgUART.SendPrintF("Tenzo=%d \n",iData);
}
void Ms5803Callback(uint32_t iData)
{
	DbgUART.SendPrintF("Pres=%d \n",(int32_t) iData);
	DataPack_t sDataPack;
	sDataPack.Addr=DATA_PACK_ADDR_PRES;
	sDataPack.Data=iData;
	uplink.Send(&sDataPack);
}

void CallBackCalipers(uint32_t iData)
{
	DbgUART.SendPrintF("Calip=%d \n",iData);
	DataPack_t sDataPack;
	sDataPack.Addr=DATA_PACK_ADDR_LENGTH;
	sDataPack.Data=iData;
	uplink.Send(&sDataPack);
	//ComportUART.SendPrintF("Calip2=%d \n",i);
	//ComportUART.SendByte('a');
}

