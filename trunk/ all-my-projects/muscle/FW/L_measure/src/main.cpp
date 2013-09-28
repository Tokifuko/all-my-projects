/**
  ******************************************************************************
  * @file    main.c
  * @author  Microcontroller Division
  * @version V1.0.3
  * @date    May-2013
  * @brief   Main program body
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  */
 
/* Includes ------------------------------------------------------------------*/

#include "stm32l1xx.h"
#include "discover_board.h"
#include "stm32l_discovery_lcd.h"
#include "tiny_sprintf.h"
#include "delay_util.h"
#include "UARTClass.h"
#include "i2c_mgr.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define DEBUG_SWD_PIN  1  /* needs to be set to 1 to enable SWD debug pins, set to 0 for power consumption measurement*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

char strDisp[20] ;

volatile bool flag_UserButton;


RCC_ClocksTypeDef RCC_Clocks;
UART_Class* pUART1;
UART_Class* pUART2;
UART_Class* pUART3;
UART_Class* pUART4;
UART_Class* pUART5;
UART_Class DbgUART;

//__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
uint32_t TimeDelay;
uint32_t DbgDelay;



/* Private function prototypes -----------------------------------------------*/
void  RCC_Configuration(void);
void  Init_GPIOs (void);
void clearUserButtonFlag(void);
void MesureCurStop(void);
void MesureCurUpward(void);
void MesureCurDownward(void);
void MesureCurToggle(void);
void CallBackI2C(void);
char chMeasureCurFlag;
#define MEASURE_CUR_STOP	0
#define MEASURE_CUR_UP		1
#define MEASURE_CUR_DOWN	2
#define SWITCH_DELAY		1
/*******************************************************************************/
I2C_Cmd_t I2C_command;
uint8_t chflagI2C;
/**
  * @brief main entry point.
  * @par Parameters None
  * @retval void None
  * @par Required preconditions: None
  */
                                  
int main(void)
{
	/*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32l1xx_md.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32l1xx.c file
*/
  /* Configure Clocks for Application need */
  RCC_Configuration();
  uint8_t rxBuf[3];
  uint8_t txBuf[16];
  uint8_t chByte[2];
  int16_t* iCurentAdcValue=(int16_t*)chByte; // теперь тут будет лежать последнее измеренное число
  /* Configure RTC Clocks */
//  RTC_Configuration();

  /* Enable debug features in low power modes (Sleep, STOP and STANDBY) */
#ifdef  DEBUG_SWD_PIN
  DBGMCU_Config(DBGMCU_SLEEP | DBGMCU_STOP | DBGMCU_STANDBY, ENABLE);
#endif
  
  /* Configure SysTick IRQ and SysTick Timer to generate interrupts */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 500);

  /* Init I/O ports */
  Init_GPIOs();
  
  /* Initializes the LCD glass */
  //LCD_GLASS_Configure_GPIO();
  //LCD_GLASS_Init();
  RCC_AHBPeriphClockCmd(LD_GPIO_PORT_CLK , ENABLE);
  RCC_AHBPeriphClockCmd(LD_GPIO_PORT_CLK 		| P_GATE1_GPIO_PORT_CLK |
		  	  	  	  P_GATE2_GPIO_PORT_CLK 	| N_GATE1_GPIO_PORT_CLK |
		  	  	  	  N_GATE2_GPIO_PORT_CLK		, ENABLE);

  Delay.Init();
  DbgUART.UART_Init(USART3);
  i2cMgr.SetDbgUART(&DbgUART);
  i2cMgr.Init();

  // Setup i2cCmd

  I2C_command.Address=0x48;
  I2C_command.DataToRead.Length = 4;
  I2C_command.DataToRead.Buf=rxBuf;
  I2C_command.DataToWrite.Buf = txBuf;
  I2C_command.DataToWrite.Length = 0;
  I2C_command.Callback=CallBackI2C;
 // DbgUART.SendPrintF("Hello word %d \n",24);
  //DbgUART.SendByte('a');
  //DbgUART.SendByte('a');
  /* Display Welcome message */ 

//  LCD_GLASS_ScrollSentence((uint8_t*)" L-measure ",1,SCROLL_SPEED);
  /* Disable SysTick IRQ and SysTick Timer */
 // SysTick->CTRL  &= ~ ( SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk );

  GPIO_HIGH(LD_GPIO_PORT, LD_GREEN_GPIO_PIN);
  GPIO_LOW(LD_GPIO_PORT, LD_BLUE_GPIO_PIN);
  Delay.Reset(&TimeDelay);
  Delay.Reset(&DbgDelay);
  MesureCurStop();
  MesureCurUpward();
  while(1){
	  i2cMgr.Task();
	  if (Delay.Elapsed(&TimeDelay,1000))
		  {
		  	  GPIO_TOGGLE(LD_GPIO_PORT, LD_BLUE_GPIO_PIN);
		  	MesureCurToggle();
		  	chByte[0]=rxBuf[1];
		  	chByte[1]=rxBuf[0];
		  	DbgUART.SendPrintF("ACD_VAL= %d \n",*iCurentAdcValue);
		  	i2cMgr.AddCmd(I2C_command);

		  }
	  //if (Delay.Elapsed(&DbgDelay,100))  DbgUART.SendByte('a') ;


    if (flag_UserButton == TRUE){
       clearUserButtonFlag();
       GPIO_TOGGLE(LD_GPIO_PORT, LD_GREEN_GPIO_PIN);
       MesureCurUpward();
    }

    
  //  if (CurrentlyDisplayed == Display_TemperatureDegC) {
      /* print average temperature value in °C  */
//      tiny_sprintf(strDisp, "%d °C", temperature_C );
 //   } else {
 //     /* print result of ADC conversion  */
  //    tiny_sprintf(strDisp, "> %d", tempAVG );

 //   }

   // LCD_GLASS_Clear();
   //LCD_GLASS_DisplayString( (unsigned char *) strDisp );

  }

}

void setUserButtonFlag(void)
{
  flag_UserButton = TRUE;
}

void clearUserButtonFlag(void)
{
  flag_UserButton = FALSE;
}

		

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{  
  
  /* Enable HSI Clock */
  RCC_HSICmd(ENABLE);
  
  /*!< Wait till HSI is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
  {}

  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
  
  RCC_MSIRangeConfig(RCC_MSIRange_6);

  RCC_HSEConfig(RCC_HSE_OFF);  
  if(RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET )
  {
    while(1);
  }
 
  /* Enable  comparator clock LCD and PWR mngt */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_LCD | RCC_APB1Periph_PWR, ENABLE);
    
  /* Enable ADC clock & SYSCFG */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_SYSCFG, ENABLE);

}


/**
  * @brief  To initialize the I/O ports
  * @caller main
  * @param None
  * @retval None
  */


void conf_analog_all_GPIOS(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIOs clock */ 	
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | 
                        RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD | 
                        RCC_AHBPeriph_GPIOE | RCC_AHBPeriph_GPIOH, ENABLE);

  /* Configure all GPIO port pins in Analog Input mode (floating input trigger OFF) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_Init(GPIOH, &GPIO_InitStructure);

#if  DEBUG_SWD_PIN == 1
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All & (~GPIO_Pin_13) & (~GPIO_Pin_14);
#endif
  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Disable GPIOs clock */ 	
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | 
                        RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD | 
                        RCC_AHBPeriph_GPIOE | RCC_AHBPeriph_GPIOH, DISABLE);
}

void  Init_GPIOs (void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  conf_analog_all_GPIOS();   /* configure all GPIOs as analog input */
  
  /* Enable GPIOs clock */ 	
  RCC_AHBPeriphClockCmd(LD_GPIO_PORT_CLK | USERBUTTON_GPIO_CLK, ENABLE);
  RCC_AHBPeriphClockCmd(LD_GPIO_PORT_CLK 		| P_GATE1_GPIO_PORT_CLK |
		  	  	  	  P_GATE2_GPIO_PORT_CLK 	| N_GATE1_GPIO_PORT_CLK |
		  	  	  	  N_GATE2_GPIO_PORT_CLK		, ENABLE);
  /* USER button and WakeUP button init: GPIO set in input interrupt active mode */
  
  /* Configure User Button pin as input */
  GPIO_InitStructure.GPIO_Pin = USERBUTTON_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(USERBUTTON_GPIO_PORT, &GPIO_InitStructure);

  /* Connect Button EXTI Line to Button GPIO Pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);

  /* Configure User Button and IDD_WakeUP EXTI line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0 ;  // PA0 for User button AND IDD_WakeUP
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set User Button and IDD_WakeUP EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure); 

/* Configure the GPIO_LED pins  LD3 & LD4*/
  GPIO_InitStructure.GPIO_Pin = LD_GREEN_GPIO_PIN | LD_BLUE_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(LD_GPIO_PORT, &GPIO_InitStructure);
  GPIO_LOW(LD_GPIO_PORT, LD_GREEN_GPIO_PIN);	
  GPIO_LOW(LD_GPIO_PORT, LD_BLUE_GPIO_PIN);



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



/* Disable all GPIOs clock */ 	
 /** RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB |
                        RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOD | 
                        RCC_AHBPeriph_GPIOE | RCC_AHBPeriph_GPIOH, DISABLE);
*/
  RCC_AHBPeriphClockCmd(LD_GPIO_PORT_CLK 		| P_GATE1_GPIO_PORT_CLK |
		  	  	  	  P_GATE2_GPIO_PORT_CLK 	| N_GATE1_GPIO_PORT_CLK |
		  	  	  	  N_GATE2_GPIO_PORT_CLK		, ENABLE);

}  /*
void insertionSort(uint16_t *numbers, uint32_t array_size) 
{
  
	uint32_t i, j;
	uint32_t index;

  for (i=1; i < array_size; i++) {
    index = numbers[i];
    j = i;
    while ((j > 0) && (numbers[j-1] > index)) {
      numbers[j] = numbers[j-1];
      j = j - 1;
    }
    numbers[j] = index;
  }
}
//*/
//uint32_t interquartileMean(uint16_t *array, uint32_t numOfSamples)
//{
//    uint32_t sum=0;
//    uint32_t  index, maxindex;
//    /* discard  the lowest and the highest data samples */
//	maxindex = 3 * numOfSamples / 4;
//    for (index = (numOfSamples / 4); index < maxindex; index++){
//            sum += array[index];
//    }
//	/* return the mean value of the remaining samples value*/
//    return ( sum / (numOfSamples / 2) );
//}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif


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
	GPIO_LOW(N_GATE2_GPIO_PORT, N_GATE2_GPIO_PIN);
	GPIO_HIGH(P_GATE2_GPIO_PORT, P_GATE2_GPIO_PIN);
	// ждем закрытия транзисторов
	Delay.ms(SWITCH_DELAY);
	// on L-arm
	GPIO_HIGH(N_GATE1_GPIO_PORT, N_GATE1_GPIO_PIN);
	GPIO_LOW(P_GATE1_GPIO_PORT, P_GATE1_GPIO_PIN);
	chMeasureCurFlag=MEASURE_CUR_UP;
}

void MesureCurDownward(void)
{
	// off L-arm
	GPIO_LOW(N_GATE1_GPIO_PORT,N_GATE1_GPIO_PIN);
	GPIO_HIGH(P_GATE1_GPIO_PORT,P_GATE1_GPIO_PIN);
	// ждем закрытия транзисторов
	Delay.ms(SWITCH_DELAY);
	// on R-arm
	GPIO_HIGH(N_GATE2_GPIO_PORT,N_GATE2_GPIO_PIN);
	GPIO_LOW(P_GATE2_GPIO_PORT,P_GATE2_GPIO_PIN);
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

void CallBackI2C(void)
{
	chflagI2C=1;
	DbgUART.SendPrintF("CALL BACK \n");
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
