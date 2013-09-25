#include "stm32l1xx.h"
#include "UARTClass.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "tiny_sprintf.h"
void UART_Class :: UART_Init(USART_TypeDef* UART)
{
	if (FIFO_TxData.Init(UART3_BUF_SIZE)!=FIFO_NO_ERROR) return;
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    USART_ClockInitTypeDef USART_ClockInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    pUART=UART;
    eco_in_flag=0;
    eco_out_flag=0;
    switch ((uint32_t)UART)
    {
      case ((uint32_t)USART1_BASE):
          pUART1=this; // глобальный указатель - для обработки прерываний именно этого обьекта
          break;

      case ((uint32_t)USART2_BASE):

		  /* Enable GPIO &  USARTx clock */
		  RCC_AHBPeriphClockCmd (USART2_GPIO_CLK, ENABLE );
		  RCC_APB1PeriphClockCmd( USART2_CLK, ENABLE );

		  /* Configure pin: RX */
		  GPIO_InitStructure.GPIO_Pin = USART2_RxPin;
		  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		  GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
		  GPIO_InitStructure.GPIO_PuPd= GPIO_PuPd_NOPULL;
		  GPIO_Init(USART2_GPIO, &GPIO_InitStructure);

		  /* Configure pin: TX */
		  GPIO_InitStructure.GPIO_Pin = USART2_TxPin;
		  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
		  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
		  GPIO_Init(USART2_GPIO, &GPIO_InitStructure);

		  /* настройка порта */
		  USART_InitStructure.USART_BaudRate = UART2_BAUD_RATE;
		  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		  USART_InitStructure.USART_StopBits = UART2_BITS;
		  USART_InitStructure.USART_Parity = UART2_PARITY;
		  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		  USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
		  USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
		  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
		  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

		   /* Enable the USARTy Interrupt */
		  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
          pUART2=this; // глобальный указатель - для обработки прерываний именно этого обьекта
          break;

      case ((uint32_t)USART3_BASE):/* Initialize USART3  для связи PC*/
		  /* Enable GPIO &  USARTx clock */
		  RCC_AHBPeriphClockCmd (USART3_GPIO_CLK, ENABLE );
		  RCC_APB1PeriphClockCmd( USART3_CLK, ENABLE );

		  /* Configure pin: RX */
		  GPIO_InitStructure.GPIO_Pin = USART3_RxPin;
		  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		  GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
		  GPIO_InitStructure.GPIO_PuPd= GPIO_PuPd_NOPULL;
		  GPIO_Init(USART3_GPIO, &GPIO_InitStructure);
		  GPIO_PinAFConfig(USART3_GPIO,GPIO_PinSource11,GPIO_AF_USART3);

		  /* Configure pin: TX */
		  GPIO_InitStructure.GPIO_Pin = USART3_TxPin;
		  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
		  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
		  GPIO_Init(USART3_GPIO, &GPIO_InitStructure);
		  GPIO_PinAFConfig(USART3_GPIO,GPIO_PinSource10,GPIO_AF_USART3);

		  /* настройка порта */
		  USART_InitStructure.USART_BaudRate = UART3_BAUD_RATE;
		  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		  USART_InitStructure.USART_StopBits = UART3_BITS;
		  USART_InitStructure.USART_Parity = UART3_PARITY;
		  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		  USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
		  USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
		  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
		  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

		   /* Enable the USARTy Interrupt */
		  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
          pUART3=this; // глобальный указатель - для обработки прерываний именно этого обьекта
          break;

    case ((uint32_t)UART4_BASE):
          pUART4=this; // глобальный указатель - для обработки прерываний именно этого обьекта
          break;

    case ((uint32_t)UART5_BASE):
          pUART5=this; // глобальный указатель - для обработки прерываний именно этого обьекта
          break;

    default:
        return;
        break;
    }

    USART_Init(UART, &USART_InitStructure);
    USART_ClockInit( UART, &USART_ClockInitStructure );

    /* Disable USART Receive and Transmit interrupts */
    USART_ITConfig(UART, USART_IT_RXNE, DISABLE);
    USART_ITConfig(UART, USART_IT_TXE, DISABLE);

	/* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    NVIC_Init(&NVIC_InitStructure);

    /* Enable USART Receive interrupt */
   // USART_ITConfig( UART, USART_IT_RXNE, ENABLE );

    /* Enable the USART */
    USART_Cmd(UART, ENABLE);
}

void  UART_Class ::SendByte(char chData)
{
	FIFO_TxData.WriteByte(chData);
	UART_StartTx();
}

void UART_Class ::SendPrintF(const char *fmt, ...)
{
  char bp[PRINTF_BUF_SIZE]; // строка, хранит текст сообщения
  int count;
  va_list argp;
  va_start(argp, fmt);
  count=tiny_vsprintf(bp, fmt, argp);
  va_end(argp);
  FIFO_TxData.WriteData(count,(uint8_t*) bp);
  UART_StartTx();
}

void UART_Class :: UART_StartTx(void){USART_ITConfig( pUART, USART_IT_TXE, ENABLE );}
void UART_Class :: UART_StartRx(void){USART_ITConfig( pUART, USART_IT_RXNE, ENABLE );}
void UART_Class :: UART_StopTx(void){USART_ITConfig( pUART, USART_IT_TXE, DISABLE );}
void UART_Class :: UART_StopRx(void){USART_ITConfig( pUART, USART_IT_RXNE, DISABLE );}
void UART_Class :: UART_Enable(void) {USART_Cmd(pUART, ENABLE);}
void UART_Class :: UART_Disable(void) {USART_Cmd(pUART, DISABLE);}

void UART_Class :: UART_InterruptHandler(void)
{
	if( USART_GetITStatus( pUART, USART_IT_TXE ) == SET )
	{
		/* The interrupt was caused by the THR becoming empty.  Are there any
		more characters to transmit? */
		if (FIFO_TxData.IsEmpty())
		{
			USART_ITConfig( pUART, USART_IT_TXE, DISABLE );
		}
		else
		{
			/* A character was retrieved from the FIFO so can be sent to the THR now. */
			USART_SendData( pUART, FIFO_TxData.SimpleReadByte() );
			  //  if (eco_out_flag) xQueueSendFromISR( xQueue_UART_Rx, &cChar, &xHigherPriorityTaskWoken );
		}
	}

	if( USART_GetITStatus( pUART, USART_IT_RXNE ) == SET )
	{
	      cChar = USART_ReceiveData( pUART );
	      /* пока получение не требуется
	       *
             if(xQueueSendFromISR( xQueue_UART_Rx, &cChar, &xHigherPriorityTaskWoken ) == pdTRUE )
              {
                  if (eco_in_flag)
                  {
                      xQueueSendFromISR( xQueue_UART_Tx, &cChar, &xHigherPriorityTaskWoken );
                      UART_StartTx();
                  }
              }
              else
              {
                  USART_ITConfig( pUART, USART_IT_RXNE, DISABLE );
              }
              */
	}
}

void USART2_IRQHandler(void)
{
	pUART2->UART_InterruptHandler();
}
void USART3_IRQHandler(void)
{
	pUART3->UART_InterruptHandler();
}
