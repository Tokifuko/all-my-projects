#include <avr/io.h>
#include <avr/interrupt.h>
//#include <UART.h>
#include <my_MNEA.h>
#include <stdlib.h>


//функция принимает и обрабатывает сообщение из UART-a
//заполняет буфер соообщения и подсчитывает контрольную сумму

char MNP_CRC=0;
unsigned char rx_CRC;
unsigned char MNP_message_length=0;
char MNP_message_buffer[MNP_MESSAGE_BUFFER_SIZE];
unsigned char MNP_message_counter=0;
unsigned char MNP_message_mode =MNP_WAIT_START;
char *str="$PPER,0*";
unsigned char debug_counter=0;



void MNP_message_reset ()
{
    MNP_CRC=0;
    MNP_message_length=0;
    MNP_message_counter=0;
    MNP_message_mode=MNP_WAIT_START;
}

char MNP_get_message(void)
{
    if (UART_rx_buffer_overflow)  // было переаолнение буфера
    {               // все сбрасываем, и возвращаем ошибку
        MNP_message_reset();
        UART_rx_overflow_reset();
        return ERR_RX_OVERFLOW;
    }
    char data;
    if (UART_rx_buffer_empty ) return 0;//буфер пустой
    
    data=UART_getchar();
    switch (MNP_message_mode)
    {
        case MNP_WAIT_START:// ждем начала сообщения
            // получено начало сообщения,
            if (data=='$')
            {
                MNP_message_mode=MNP_GET_DATA;  // начинаем принимать данные
                debug_counter++;
                MNP_CRC=0;// все сбрасываем
                MNP_message_length=0;
                MNP_message_counter=0;
            }
            else return ERR_MNP_START_EXPECTED;
            break;
        case MNP_GET_DATA: // тут получаем полезные данные
            // проверяем на отсутствие служебных символов
            if (data=='$') // символ начала нового сообщения
            {
                MNP_message_reset ();
                return ERR_MNP_START_UNEXPECTED;
            }
            if (data==0x0A) // символ перевода строки
            {
                MNP_message_reset ();
                return ERR_MNP_LF_UNEXPECTED;  
            }
            if (data==0x0D)  // символ возврата каретки
            {
                MNP_message_reset ();
                return ERR_MNP_CR_UNEXPECTED;
            }
            
            if (data=='*') // конец принимаемым данным
            {
                MNP_message_mode=MNP_GET_CRC_H; // переключаемся на прием CRC
                return 0;
            }
            
            if (MNP_message_counter>MNP_MESSAGE_BUFFER_SIZE) // если буфер заполнен
            {
                MNP_message_reset ();
                return ERR_MNP_MESSAGE_OVERFLOW; // если буфер сообщения переполнился
            }

            MNP_message_buffer[MNP_message_counter++]=data; //байт в буфер
            MNP_CRC^=data; // считаем CRC
            break;

        case MNP_GET_CRC_H: // здесь приимает старший символ CRC
            // и переводим символ в число
            if ((data >= '0') && (data <= '9')) rx_CRC=(data-'0')<<4;
            else if ((data >= 'A') && (data <= 'F')) rx_CRC=(data-'A'+10)<<4;
                else 
                    {
                        MNP_message_reset ();
                        return ERR_MNP_UNEXPECTED_CRC_CHAR;
                    }
            MNP_message_mode=MNP_GET_CRC_L;
            break;

        case MNP_GET_CRC_L: // здесь приимает младший символ CRC
            if ((data >= '0') && (data <= '9')) rx_CRC+=(data-'0');
            else if ((data >= 'A') && (data <= 'F')) rx_CRC+=(data-'A'+10);
                else
                    {
                        MNP_message_reset ();
                        return ERR_MNP_UNEXPECTED_CRC_CHAR;
                    }
            MNP_CRC^=rx_CRC;// считаем CRC
            if (!(MNP_CRC==0) ) //если не сошелся то ошибку возвращаем
            {
                MNP_message_reset ();
                return ERR_MNP_CRC_ERROR;
            }
            MNP_message_mode=MNP_GET_CR;

            break;

        case MNP_GET_CR: //должен быть символ возврата каретки
            if (data==0x0A) MNP_message_mode=MNP_GET_LF;// символ возврата кареткии
            else return ERR_MNP_CR_EXPECTED;

            break; 
        case MNP_GET_LF: // и в конце должен быть символ перевода строки
            if (data==0x0D) MNP_message_mode=MNP_WAIT_START;// символ перевода строки
            else return ERR_MNP_LF_EXPECTED;
            return MNP_message_parser();
            break;
    }
    return 0;
} 

char MNP_send_message(void)//char *str)
{
    char tx_CRC=0;
    char tx_CRC_H,tx_CRC_L;
    
    while (*str)
    {
 
	if  ((*str!='$')&&(*str!='*')) tx_CRC^=*str;
        UART_putchar(*str);
		str++;
    }

    div_t x;
    x=div(tx_CRC,16);
    tx_CRC_H=x.quot;
    tx_CRC_L=x.rem;
    if ((tx_CRC_H >= 0) && (tx_CRC_H <= 9)) tx_CRC_H=(tx_CRC_H+'0');
    if ((tx_CRC_H >= 0x0A) && (tx_CRC_H <= 0x0F)) tx_CRC_H=(tx_CRC_H+'A'-10);
    UART_putchar(tx_CRC_H);
    if ((tx_CRC_L >= 0) && (tx_CRC_L <= 9)) tx_CRC_L=(tx_CRC_L+'0');
    if ((tx_CRC_L >= 0x0A) && (tx_CRC_L <= 0x0F)) tx_CRC_L=(tx_CRC_L+'A'-10);
    UART_putchar(tx_CRC_L);
    UART_putchar(0x0A);
    UART_putchar(0x0D);

    return 0; //UART_putchar(str++);
}

char MNP_message_parser(void)
{
   MNP_message_reset ();
   MNP_send_message();
   char stop_step=5;
   step++;
   if (step<stop_step) return 1;
   if (step<stop_step) return 1;
    if (MNP_message_buffer[0]!='P') return 1;
    if (MNP_message_buffer[1]!='I') return 1;
    if (MNP_message_buffer[2]!='R') return 1;
    if (MNP_message_buffer[3]!='E') return 1;
    if (MNP_message_buffer[4]!='A') return 1;
    if (MNP_message_buffer[5]!=',') return 1;
    return debug_counter;

}

// переводит символы из строки в число
// H-старший байт, L- младший байт
char str_to_hex(char H, char L)
{
    char res=0;
    if ((H >= '0') && (H <= '9')) res=(H-'0')<<4;
        else if ((H >= 'A') && (H <= 'F')) res=(H-'A'+10)<<4;
    if ((L >= '0') && (L <= '9')) res+=(L-'0')<<4;
    else if ((L >= 'A') && (L <= 'F')) res+=(L-'A'+10)<<4;    
    return res;
}


// находит вхождение одной строки в другую
// начинает с начала и до len
// возвращает 0 - если несовпадает 1-если совпадает
char str_in_str(char *str1, char *str2, char len)
{
    char i;
    while (i<=len)
    {
        if ((*str1++)==(*str2++)) i++;
        else return 0;
    }
    return 1;


}