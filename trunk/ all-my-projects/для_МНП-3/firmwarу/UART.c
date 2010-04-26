
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <UART.h>

// USART Receiver buffer

char rx_buffer[RX_BUFFER_SIZE];

#if RX_BUFFER_SIZE<256
unsigned char rx_wr_index,rx_rd_index,rx_counter;
#else
unsigned int rx_wr_index,rx_rd_index,rx_counter;
#endif

// USART Receiver interrupt service routine
ISR (USART_RXC_vect) //void usart_rx_isr(void)
{
char status,data; 
status=UCSRA;
data=UDR;
// ��� ������������ ������ ����� ����� ������ ������������������ �� ��� ���,

if (UART_rx_buffer_full==1)  UART_rx_buffer_overflow=1;
if (UART_rx_buffer_overflow ) return;
if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
   {
   rx_buffer[rx_wr_index]=data;
   if (++rx_wr_index == RX_BUFFER_SIZE) rx_wr_index=0;
   UART_rx_buffer_empty=0;
   if (++rx_counter == RX_BUFFER_SIZE)
      {
     // if (rx_counter==255) rx_counter--;  // ���� �� ����������� ��� unsigned char
     // rx_counter=0;
      UART_rx_buffer_full=1;
      };
   };
}

#ifndef _DEBUG_TERMINAL_IO_
// Get a character from the USART Receiver buffer
#define _ALTERNATE_GETCHAR_
//#pragma used+
char UART_getchar(void)
{
char data;
while (rx_counter==0);
data=rx_buffer[rx_rd_index];
if (++rx_rd_index == RX_BUFFER_SIZE) rx_rd_index=0;
cli();
--rx_counter;
sei();
UART_rx_buffer_full=0;
if (rx_counter==0) UART_rx_buffer_empty=1;
return data;
}
//#pragma used-
#endif

// ����� �������� ������ ��� ��� ������������
void UART_rx_overflow_reset(void)
{
    UART_rx_buffer_full=0;
    UART_rx_buffer_empty=1;
    rx_counter=0;
}


char tx_buffer[TX_BUFFER_SIZE];

#if TX_BUFFER_SIZE<256
unsigned char tx_wr_index,tx_rd_index,tx_counter;
#else
unsigned int tx_wr_index,tx_rd_index,tx_counter;
#endif

// USART Transmitter interrupt service routine
ISR(USART_TXC_vect) //void usart_tx_isr(void)
{
if (tx_counter)
   {
   --tx_counter;
   UDR=tx_buffer[tx_rd_index];
   if (++tx_rd_index == TX_BUFFER_SIZE) tx_rd_index=0;
   UART_tx_buffer_full=0;
   }
else UART_tx_buffer_empty=1;
}

#ifndef _DEBUG_TERMINAL_IO_
// Write a character to the USART Transmitter buffer
#define _ALTERNATE_PUTCHAR_
//#pragma used+
void UART_putchar(char c)
{
    while (tx_counter == TX_BUFFER_SIZE); // ��� ����, ���� ����� ������������. � ����� ������ ��� ����� FULL
cli();
if (tx_counter || ((UCSRA & DATA_REGISTER_EMPTY)==0)) // ���� � ������ ���� ����� ��� � ������� ���� ���-�� - ����������� � �����
   {
   tx_buffer[tx_wr_index]=c;// ��������� ������ � �����
   if (++tx_wr_index == TX_BUFFER_SIZE) tx_wr_index=0;
   ++tx_counter;
   UART_tx_buffer_empty=0;  // ����� ��� �� ������
   }
else
   UDR=c;   //���� ����� ������ � ������� ������ �� ����� ����� � ������� �� �������
sei();

if (tx_counter == TX_BUFFER_SIZE) UART_tx_buffer_full=1;
}

//#pragma used-
#endif


void UART_init (void)
{
    // USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 4800
UCSRA=0x00;
UCSRB=0xD8;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x67;
}
