/* класс дл€ работы с UART-ом
  содержит все необходимые функции */


#ifndef UARTCLASS_H
#define UARTCLASS_H


// Library configuration file.
#include "stm32f10x_conf.h"
#include "FIFOClass.h"
#include <stdio.h>

#define USART1_CLK      	RCC_APB2Periph_USART1
#define USART1_TxPin   		GPIO_Pin_9
#define USART1_RxPin   		GPIO_Pin_10
#define USART1_GPIO     	GPIOA
#define USART1_GPIO_CLK 	RCC_APB2Periph_GPIOA


#define USART2_CLK      	RCC_APB1Periph_USART2
#define USART2_TxPin   		GPIO_Pin_2
#define USART2_RxPin   		GPIO_Pin_3
#define USART2_GPIO     	GPIOA
#define USART2_GPIO_CLK 	RCC_APB2Periph_GPIOA

#define USART3_CLK      	RCC_APB1Periph_USART3
#define USART3_TxPin   		GPIO_Pin_10				// remap!!!!!!
#define USART3_RxPin   		GPIO_Pin_11
#define USART3_GPIO     	GPIOC
#define USART3_GPIO_CLK 	RCC_APB2Periph_GPIOC

#define UART1_BUF_SIZE 				FIFO_SIZE// Ќ≈ ћ≈Ќя“№ не работает malloc
#define UART1_BAUD_RATE             115200
#define UART1_PARITY                USART_Parity_No
#define UART1_BITS                  USART_StopBits_2

#define UART2_BUF_SIZE 				FIFO_SIZE// Ќ≈ ћ≈Ќя“№ не работает malloc
#define UART2_BAUD_RATE             115200
#define UART2_PARITY                USART_Parity_No
#define UART2_BITS                  USART_StopBits_2

#define UART3_BUF_SIZE 				FIFO_SIZE// Ќ≈ ћ≈Ќя“№ не работает malloc
#define UART3_BAUD_RATE             115200
#define UART3_PARITY                USART_Parity_No
#define UART3_BITS                  USART_StopBits_2

#define PRINTF_BUF_SIZE		255
//
//typedef struct
//{
//    signed portCHAR* pData;
//    portBASE_TYPE   iSize;
//} MessageBuf_t;

class UART_Class {
private:
    USART_TypeDef* pUART;
    uint8_t cChar;

public:
    uint16_t        eco_in_flag; // флаг включающий эхо (то что входит - подаетс€ на выход)
    uint16_t        eco_out_flag;// флаг включающий эхо (то что выходит - подаетс€ на вход)
    FIFO_Class FIFO_TxData;
    void UART_Init(USART_TypeDef* UART);
    void UART_StartTx(void);
    void UART_StartRx(void);
    void UART_StopTx(void);
    void UART_StopRx(void);
    void UART_Enable(void);
    void UART_Disable(void);
    void SendPrintF(const char *fmt, ...);
    void SendByte(char chData);

    void UART_InterruptHandler(void);
    void UART_DeInit();
    // ~UART_Class(void); // деструктор
};

extern UART_Class* pUART1;
extern UART_Class* pUART2;
extern UART_Class* pUART3;
extern UART_Class* pUART4;
extern UART_Class* pUART5;

// Declare IRQ. Use externC to make it visible from asm file.
extern "C" {
void USART1_IRQHandler(void);
//void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
//void USART4_IRQHandler(void);
//void USART5_IRQHandler(void);
}

#endif /* UARTCLASS_H */
