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
#include "motor_class.h"
#include <string.h>
#include <stdio.h>

#define DEBUG_LED_TIMEOUT	500
#define OPEN_DELAY			1500

// состояния автомата ручного управления
#define MC_IDLE			0
#define MC_MOVE_DOWN	1
#define MC_MOVE_UP		2

// состояния автомата автоматического управления
#define AC_INIT						0
#define AC_OPENING					1
#define AC_OPENING_TEMP_DOWN		2
#define AC_OPEN						3
#define AC_CLOSING					4
#define AC_CLOSING_TEMP_UP			5
#define AC_CLOSE					6

UART_Class* pUART1;
UART_Class* pUART2;
UART_Class* pUART3;
UART_Class* pUART4;
UART_Class* pUART5;


void GeneralInit(void);
void MainControl(void);
void AutoControl (void);
void SensorDebug(void);
UART_Class DbgUART;
uint8_t chManualControlState;
uint8_t chAutoControlState;
uint8_t chSensorDebug;
MotorClass Motor;
uint32_t iOpenTimer;

int main(void) {

	uint32_t iDebugLedTimer;

	Motor.Init();
    DbgUART.UART_Init(USART2);
    Delay.ms(100);
    uint32_t flag=0;
    GeneralInit();


    //sprintf(str,"Hello word %в  \n",56);
   // DbgUART.FIFO_TxData.WriteData(24,(uint8_t*) str);
    DbgUART.SendPrintF("Hello word %d \n",24);
    //DbgUART.SendPrintF("00000000001111111111222222222233333333334444444444555555555566666666667777777777");
    //DbgUART.SendPrintF("8888888888");
    //DbgUART.SendPrintF("00000000001111111111222222222233333333334444444444555555555566666666667777777777");
    Delay.Reset(&iDebugLedTimer);
    Motor.Stop();
   // Motor.Downward();
    // ==== Main cycle ====
    chManualControlState=MC_IDLE;
    while(1)
    {
    	SensorDebug();
    	MainControl();
    	//Motor.Task();
    	if (Delay.Elapsed(&iDebugLedTimer,DEBUG_LED_TIMEOUT))
    	{
    		if (flag==0)
    			{
    				Led1On();
    				//Motor.Downward();
    				flag=1;
    				//DbgUART.SendByte('o');
    			}
    			else
    				{
    					Led1Off();
    					//Motor.Upward();
    					flag=0;
    					//DbgUART.SendByte('f');
    				}
    	}
        //i2cMgr.Task();
       // ESnd.Task();
        //ESns.Task();
       // EUSB.Task();
        //Leds.Task();
       // ELock.Task();
       // EKeyboard.Task();
        //EIRSirc.Task();
        //Lcd.Task();
    } // while(1)
    return 0;
}

void SensorDebug()
{
	if (Sensor1Pressed())
	{
		if (chSensorDebug==1) return;
		chSensorDebug=1;
		DbgUART.SendPrintF("Sens 1 - activated \n");
	}
	else
	{
		if (chSensorDebug==0) return;
		chSensorDebug=0;
		DbgUART.SendPrintF("Sens 1 - deactivated \n");
	}

}
void MainControl ()
{
	switch (chManualControlState)
	{
	case MC_IDLE: // ожидаем нажатия кнопки
		AutoControl();
		if (KeyDownPressed())
			{
				chManualControlState=MC_MOVE_DOWN;
				DbgUART.SendPrintF("key_Down PRESSED \n");
			}
		if (KeyUpPressed())
			{
				chManualControlState=MC_MOVE_UP;
				DbgUART.SendPrintF("key_UP  PRESSED\n");
			}
		break;
	case MC_MOVE_DOWN: // дверь опускается
		if (!KeyDownPressed()) // кнопка отжата
		{
			DbgUART.SendPrintF("key_Down RELISE \n");
			Motor.Stop();
			chManualControlState=MC_IDLE;
		}
		if (StopDown1Pressed()) // сработал концевой выключатель
		{
			DbgUART.SendPrintF("STOP_Down 1  \n");
			Motor.Stop();
			chManualControlState=MC_IDLE;
			chAutoControlState=AC_CLOSE;  // запоминаем положение двери
		}
		if (StopDown2Pressed()) // сработал концевой выключатель
		{
			DbgUART.SendPrintF("STOP_Down 2  \n");
			Motor.Stop();
			chManualControlState=MC_IDLE;
			chAutoControlState=AC_CLOSE;  // запоминаем положение двери
		}
		if (chManualControlState==MC_MOVE_DOWN) Motor.Downward();
		break;
	case MC_MOVE_UP: // дверь поднимается
		if (!KeyUpPressed()) // кнопка отжата
		{
			Motor.Stop();
			DbgUART.SendPrintF("key_Up RELISE \n");
			chManualControlState=MC_IDLE;
		}
		if (StopUp1Pressed()) // сработал концевой выключатель
		{
			DbgUART.SendPrintF("STOP_Up 1  \n");
			Motor.Stop();
			chManualControlState=MC_IDLE;
			chAutoControlState=AC_OPEN;  // запоминаем положение двери
		}
		if (StopUp2Pressed()) // сработал концевой выключатель
		{
			DbgUART.SendPrintF("STOP_Up 2  \n");
			Motor.Stop();
			chManualControlState=MC_IDLE;
			chAutoControlState=AC_OPEN;  // запоминаем положение двери
		}
		if (chManualControlState==MC_MOVE_UP) Motor.Upward();
		break;
	}

}

void AutoControl (void)
{
	switch (chAutoControlState)
	{
	case AC_INIT:
		chAutoControlState=AC_OPENING;
		Motor.Upward();
		DbgUART.SendPrintF("Auto Control Init  \n");
		break;
	case AC_OPENING:
		if (WarningUpPressed())
		{
			Motor.Downward();
			chAutoControlState=AC_OPENING_TEMP_DOWN;
			DbgUART.SendPrintF("War Up go to temp_down  \n");
		}
		if (StopUp1Pressed() | StopUp2Pressed())
		{
			DbgUART.SendPrintF("Stop Up. new state - OPEN  \n");
			Motor.Stop();
			chAutoControlState=AC_OPEN;
			Delay.Reset(&iOpenTimer);
		}
		break;
	case AC_OPENING_TEMP_DOWN:
		if (WarningDownPressed())
		{
			DbgUART.SendPrintF("War down. go to Movw UP  \n");
			Motor.Upward();
			chAutoControlState=AC_OPENING;
		}
		if (StopDown1Pressed() | StopDown2Pressed())
		{
			DbgUART.SendPrintF("stop down, temp down complite, move UP  \n");
			Motor.Upward();
			chAutoControlState=AC_OPENING;
		}
		break;
	case AC_OPEN: // дверь открыта
		if (Delay.Elapsed(&iOpenTimer,OPEN_DELAY))
		{
			chAutoControlState=AC_CLOSING;
			Motor.Downward();
			DbgUART.SendPrintF("Open Timeout Elapsed, go to CLOSING \n");
		}
		break;
	case AC_CLOSING: // начинаем закрываться
		if (WarningDownPressed())
		{
			Motor.Upward();
			chAutoControlState=AC_CLOSING_TEMP_UP;
			DbgUART.SendPrintF("War DOWN go to temp_up  \n");
		}
		if (StopDown1Pressed() | StopDown2Pressed())
		{
			DbgUART.SendPrintF("Stop Down. new state - CLOSE  \n");
			Motor.Stop();
			chAutoControlState=AC_CLOSE;
			//Delay.Reset(&iOpenTimer);
		}
		break;
	case AC_CLOSING_TEMP_UP:
		if (WarningUpPressed())
		{
			DbgUART.SendPrintF("War UP. go to Move Down  \n");
			Motor.Downward();
			chAutoControlState=AC_CLOSING;
		}
		if (StopUp1Pressed() | StopUp2Pressed())
		{
			DbgUART.SendPrintF("stop Up, temp Up complite, move down  \n");
			Motor.Downward();
			chAutoControlState=AC_CLOSING;
		}
		break;
	case AC_CLOSE: // дверь закрыта

		break;
	}
}

void GeneralInit(void) {
    // Disable JTAG
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    // Configure two bits for preemption priority
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

    // Init peripheral
    //i2cMgr.Init();
    Delay.Init();

    RCC_APB2PeriphClockCmd(
    		LED_1_CLK |
    		LED_2_CLK |
    		LED_3_CLK |
    		KEY_DOWN_CLK |
    		KEY_UP_CLK |
    		STOP_UP_1_CLK |
    		STOP_UP_2_CLK |
    		STOP_DOWN_1_CLK |
    		STOP_DOWN_2_CLK |
    		WARNING_DOWN_CLK |
    		WARNING_UP_CLK |
    		SENSOR_1_CLK |
    		SENSOR_2_CLK|
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

    // кнопки ручного управления
    /* Configure KEY_DOWN_PIN as INPUT PULLUP */
    GPIO_InitStructure.GPIO_Pin =  KEY_DOWN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( KEY_DOWN_PORT, &GPIO_InitStructure );
    /* Configure KEY_UP_PIN as INPUT PULLUP */
    GPIO_InitStructure.GPIO_Pin =  KEY_UP_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( KEY_UP_PORT, &GPIO_InitStructure );

    // концевые выключатели
    /* Configure STOP_UP_1_PIN as INPUT PULLUP */
    GPIO_InitStructure.GPIO_Pin =  STOP_UP_1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( STOP_UP_1_PORT, &GPIO_InitStructure );
    /* Configure STOP_UP_2_PIN as INPUT PULLUP */
    GPIO_InitStructure.GPIO_Pin =  STOP_UP_2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( STOP_UP_2_PORT, &GPIO_InitStructure );
    /* Configure STOP_DOWN_1_PIN as INPUT PULLUP */
    GPIO_InitStructure.GPIO_Pin =  STOP_DOWN_1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( STOP_DOWN_1_PORT, &GPIO_InitStructure );
    /* Configure STOP_DOWN_2_PIN as INPUT PULLUP */
    GPIO_InitStructure.GPIO_Pin =  STOP_DOWN_2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( STOP_DOWN_2_PORT, &GPIO_InitStructure );

    // Датчики нажатия на кошку
    /* Configure WARNING_DOWN_PIN as INPUT PULLUP */
    GPIO_InitStructure.GPIO_Pin =  WARNING_DOWN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( WARNING_DOWN_PORT, &GPIO_InitStructure );
    /* Configure WARNING_UP_PIN as INPUT PULLUP */
    GPIO_InitStructure.GPIO_Pin =  WARNING_UP_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( WARNING_UP_PORT, &GPIO_InitStructure );

    // Датчики ldb;tybz
    /* Configure WARNING_DOWN_PIN as INPUT_FLOATING */
    GPIO_InitStructure.GPIO_Pin =  SENSOR_1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( SENSOR_1_PORT, &GPIO_InitStructure );
    /* Configure WARNING_UP_PIN as INPUT_FLOATING */
    GPIO_InitStructure.GPIO_Pin =  SENSOR_2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init( SENSOR_2_PORT, &GPIO_InitStructure );


    //ROW_1_ON();
    // Leds
    //Leds.Init();
    // Sensors
    //ESns.Init();
  //  EIRSirc.Init();

    // Sound
    //SD.Init();
    //Vs.Init();
    //ESnd.Init();
    //ELock.Init();
    //EKeyboard.Init();
    //EUSB.Init();


    // LCD
    //Lcd.Init();
    //Lcd.DrawImage(0,0, ImageLogo, NotInverted);    // Artifact
//    ERock.Init();

    // Read initial charge
//    ERock.H.Counter = ReadInt32("Init", "HCounter", "rock.ini");
//    ERock.H.Value   = ReadInt32("Init", "HValue",   "rock.ini");
//    ERock.E.Counter = ReadInt32("Init", "ECounter", "rock.ini");
//    ERock.E.Value   = ReadInt32("Init", "EValue",   "rock.ini");
//    ERock.C.Counter = ReadInt32("Init", "CCounter", "rock.ini");
//    ERock.C.Value   = ReadInt32("Init", "CValue",   "rock.ini");
//    ERock.ChooseType();

    //ESnd.Play("magnet.wav");
}
