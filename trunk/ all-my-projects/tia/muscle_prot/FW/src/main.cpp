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
#include "i2c_mgr.h"
#include "common.h"
#include "kl_lib.h"

#include "UARTClass.h"

//#include "motor_class.h"
//#include <string.h>
//#include <stdio.h>
#define DEBUG_LED_TIMEOUT	1000
#define USER_BATTON_TIMEOUT	100

void GeneralInit(void);
void Ad7799Callback(uint32_t iData);
void Ms5803Callback(uint32_t iData);


UART_Class DbgUART;
UART_Class* pUART1;
UART_Class* pUART2;
UART_Class* pUART3;
UART_Class* pUART4;
UART_Class* pUART5;

AD7799_Class ad7799;
MS5803_Class ms5803;
//i2cMgr_t i2cMgr;
uint32_t iTemp;


int main(void)
{
	uint32_t iDebugLedTimer;
	uint32_t iUserBattonTimer;
	uint32_t flag=0;
	uint32_t iUserBattonFlag=0;
	uint8_t dataBufTxReset[4]={0x1E,0,0,0};
	uint8_t dataBufTxRead[4]={0xA4,0,0,0};
	uint8_t dataBufRx[4]={0,0,0,0};

	Delay.Init();
	GeneralInit();
	DbgUART.UART_Init(USART1);
	//ad7799.Init();
	//ad7799.Callback=Ad7799Callback;
	ms5803.Init();
	ms5803.Callback=Ms5803Callback;
	ms5803.DbgUART=&DbgUART;
	//i2cMgr.Init();

	DbgUART.SendPrintF("Hello word %d \n",24);

	Delay.Reset(&iDebugLedTimer);
	Delay.Reset(&iUserBattonTimer);
	//i2cMgr.SetDbgUART(&DbgUART);
	//ad7799.PswPinOff();
	I2C_Cmd_t comReset,comRead, comReadStart;

	comReset.Address = 0x77;
	comReset.DataToWrite.Length = 1;
	comReset.DataToWrite.Buf=dataBufTxReset;
	comReset.DataToRead.Length = 0;
	comReset.DataToRead.Buf = dataBufRx;
	comReset.Callback=Ms5803Callback;
	//i2cMgr.AddCmd(comReset);  // Reset command

	comRead.Address = 0x77;
	comRead.DataToWrite.Length = 1;
	comRead.DataToWrite.Buf=dataBufTxRead;
	comRead.DataToRead.Length = 0;
	comRead.DataToRead.Buf = dataBufRx;
	comRead.Callback=Ms5803Callback;

	comReadStart.Address = 0x77;
	comReadStart.DataToWrite.Length = 0;
	comReadStart.DataToWrite.Buf=dataBufTxRead;
	comReadStart.DataToRead.Length = 3;
	comReadStart.DataToRead.Buf = dataBufRx;
	comReadStart.Callback=Ms5803Callback;




//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//    GPIO_InitTypeDef GPIO_InitStructure;
//    // светодиоды
//    /* Configure LED_2_PIN as Output */
//    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//    GPIO_Init( GPIOB, &GPIO_InitStructure );
//	GPIO_SetBits(GPIOB,GPIO_Pin_12);


	uint32_t x1,x2, resL,resH;
	int64_t x64,y64;
	int32_t x32,y32;
	uint128_t z128;
	int32_t i32;
	int64_t i64;
	int128_t i128;

    while(1)
    {
    	//ad7799.Task();
    	ms5803.Task();
    	//i2cMgr.Task();
// --------------- user button start callibration process --------------
    	if (UserButtonPressed())
    	{
    		if (iUserBattonFlag==0)
    		{
    			iUserBattonFlag=1;
    			Delay.Reset(&iUserBattonTimer);
    		//	ad7799.StartZeroCalibration();
    			//i2cMgr.AddCmd(comReset);  // Reset command
    		//	DbgUART.SendPrintF("size of double %d  \n",sizeof(double));
    		//	DbgUART.SendPrintF("size of long %d  \n",sizeof(long));
    		//	Delay.ms(100);
    		//	DbgUART.SendPrintF("size of uint64_t %d  \n",sizeof(uint64_t));
    			//y64=0x0123456789ABCDEF;

    			//Delay.ms(100);
    			//DbgUART.SendPrintF("%16x \n", y64);
//    			x64=0xFEDCBA9876543210;
//    			y64=0xFEDCBA9876543210;
//    			z128.h=0;
//    			z128.l=0;
//    		    uint32_t  * a_ptr = (uint32_t*)&x64;
//    		    uint32_t  * b_ptr = (uint32_t*)&y64;
//    		    uint64_t * r_ptr = (uint64_t*)(void*)&z128;
//
//
//
//    		    DbgUART.SendPrintF(" %#8x and  %#8x \n",*(a_ptr+1), *a_ptr);
//    		    Delay.ms(100);
//    		    DbgUART.SendPrintF("mult");
//    		    Delay.ms(100);
//    		    DbgUART.SendPrintF(" %#8x and  %#8x \n",*(b_ptr+1), *b_ptr);
//
//				mult128_64_x_64(a_ptr, b_ptr, r_ptr);
//				a_ptr=(uint32_t*)(void*)&z128;
//				Delay.ms(1000);
//				DbgUART.SendPrintF(" %#8x %#8x %#8x %#8x \n",*(a_ptr+3),*(a_ptr+2),*(a_ptr+1), *a_ptr);


/*
				i64=0xFEDCBA9876543210;
				DbgUART.SendPrintF(" %#16llX %lld \n", i64, i64);
				i64=i64*(-1);
				Delay.ms(100);
				DbgUART.SendPrintF(" %#16llX %lld\n", i64, i64);
				i64=i64<<8;
				Delay.ms(100);
				DbgUART.SendPrintF(" %#16llX %lld\n", i64, i64);
				i64=i64*(-1);
				Delay.ms(100);
				DbgUART.SendPrintF(" %#16llX %lld\n", i64, i64);*/
				x32=0xfedcba98;
				y32=0x100;
				Delay.ms(100);
				DbgUART.SendPrintF(" %#X %d\n", x32, x32);
				Delay.ms(100);
				DbgUART.SendPrintF(" %#X %d\n", y32, y32);
				i64=0x0123456789abcdef;
				i64=i64*(-1);
				//smult64_32_x_32(&x32,&y32,&i64);

				Delay.ms(100);
				DbgUART.SendPrintF(" %#16llX %lld\n", i64, i64);
				Delay.ms(100);
				i128.h=i64;
				i128.l=i64;
				DbgUART.SendPrintF(" %#16llX %16llX\n", i128.h, i128.l);
				Delay.ms(100);
				sign_Shift_128bits_right(&i128,8);
				DbgUART.SendPrintF(" %#16llX %16llX\n", i128.h, i128.l);

				Delay.ms(100);
				i32=i64;
				DbgUART.SendPrintF(" %#16X \n", i32);
				i32=i32*(-1);
				DbgUART.SendPrintF(" %#16X \n", i32);

				//i64=0xFEDCBA9876543210;

				//DbgUART.SendPrintF(" %#8x %#8x %#8x %#8x \n",*(a_ptr+3),*(a_ptr+2),*(a_ptr+1), *a_ptr);
/*
    			x1=0x77777777;
    			x2=0x55555555;
    			y64=x1*x2;
    			resL=0;
    			resH=0;
    			z128.h=0;
    			z128.l=0;
    			mult64_32_x_32(&x1,&x2,&resL,&resH);
    			DbgUART.SendPrintF(" %16x and  %16x \n", resL,resH);
    			//y64=0x0123456789ABCDEF;
    			//y64=y64>>8;
    			Delay.ms(100);
    			mult64_32_x_32(&x1,&x2,(uint32_t*) &y64,((uint32_t*) &y64)+1);
    			DbgUART.SendPrintF("%x x %x = %x%x \n", x1,x2, *(((uint32_t*) &y64)+1),*((uint32_t*) &y64));
    			Delay.ms(1000);
    			//DbgUART.SendPrintF("%16x, %16x \n",*((uint32_t*) &y64), *(((uint32_t*) &y64)+1));
*/

    /*			CalibrationData CB_DATA = {46546,42845,29751,29457,32745,29059}; //static values from data sheet
    			    MeasurementData MM_DATA = {4311550,8387300}; //static values from data sheet
    			    CalculatedValues values;

    			    calculateTemperature(ms5803.CB_DATA, ms5803.MM_DATA, &(ms5803.values));
    			    //calculateTemperatureCompensatedPressure(CB_DATA, MM_DATA, &values);
    			    //doSecondOrderTemperatureCompensation(&values);

    			   // DbgUART.SendPrintF("dT %i\n", values.dT);
    			    DbgUART.SendPrintF("TEMP %i\n", ms5803.values.TEMP);
    			   // DbgUART.SendPrintF("OFF %" PRId64 "\n", values.OFF);
    			   // DbgUART.SendPrintF("SENS %" PRId64 "\n", values.SENS);
    			   // DbgUART.SendPrintF("P %i\n", values.P);
    			    Delay.ms(100);

/*    			    if(values.dT == 4580 && values.TEMP == 2015 && values.OFF == 2808943914ULL && values.SENS == 1525751591ULL && values.P == 10005) {
    			    	DbgUART.SendPrintF("Calculated values are correct.\n");
    			    } else {
    			    	DbgUART.SendPrintF("Check algorithm. Values are incorrect.\n");
    			    }*/


    		}
    	}
    	else if (Delay.Elapsed(&iUserBattonTimer,USER_BATTON_TIMEOUT))
				{
					iUserBattonFlag=0;
				//	ad7799.PswPinOff();
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
    				//ad7799.PswPinOn();
    			}
    			else
    			{
    				//GPIO_SetBits(GPIOB,GPIO_Pin_12);
    				//i2cMgr.AddCmd(comReadStart);
    				DbgUART.SendPrintF("Temp=%d \n",ms5803.GetTemp());

    			    Delay.ms(100);
    				BLedDiscOff();
    				flag=0;
    				//ad7799.PswPinOff();
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
/*	iTemp++;
	if (iTemp>1)
	{
		DbgUART.SendPrintF("Tenzo=%d \n",iData);

	iTemp=0;
	}
*/
	DbgUART.SendPrintF("Tenzo=%d \n",iData);
}
void Ms5803Callback(uint32_t iData)
{
	DbgUART.SendPrintF("Data=%X \n",(int32_t) iData);
}

