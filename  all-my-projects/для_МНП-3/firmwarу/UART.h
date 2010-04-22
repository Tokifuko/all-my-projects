#ifndef RXB8
#define RXB8 1
#endif


#ifndef TXB8
#define TXB8 0
#endif

#ifndef UPE
#define UPE 2
#endif

#ifndef DOR
#define DOR 3
#endif

#ifndef FE
#define FE 4
#endif

#ifndef UDRE
#define UDRE 5
#endif

#ifndef RXC
#define RXC 7
#endif

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

#define RX_BUFFER_SIZE 255 // USART Transmitter buffer
#define TX_BUFFER_SIZE 16

char UART_getchar(void);
void UART_putchar(char c);
void UART_init (void);

// ����� ��� �������� �������
char UART_rx_buffer_overflow=0;
char UART_rx_buffer_full=0;
char UART_rx_buffer_empty=1;
char UART_tx_buffer_full=0;
char UART_tx_buffer_empty=1;


