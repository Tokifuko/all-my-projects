#include <avr/io.h>
#include <avr/interrupt.h>
#include <UART.h>
#include <my_MNEA.h>


//функция принимает и обрабатывает сообщение из UART-a
//заполняет буфер соообщения и подсчитывает контрольную сумму

char MNP_CRC=0;
unsigned char MNP_message_length=0;
char MNP_message_buffer[MNP_MESSAGE_BUFFER_SIZE];
unsigned char MNP_message_counter=0;
unsigned char MNP_message_mode =MNP_WAIT_START;

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
    if (!(UART_rx_buffer_empty )) // есть что-то в буфере
    {
        data=UART_getchar();
        switch (data)
        {
            case '$': // пришло начало нового сообщения
                if(MNP_message_mode=MNP_WAIT_START) MNP_message_mode=MNP_WAIT_END; // начинаем принимать сообщение, пока не придет конец
                else // если мы не в режиме ожидания начаа нового пакета
                {
                    MNP_message_reset(); // все сбрасываем и возвращаем ошибку
                    return ERR_MNP_START_UNEXPECTED;
                }                    
                break;
            case '*': //пришел конец сообщения. начинаем принимать CRC
                if (MNP_message_mode=MNP_WAIT_END) //конец ожидаем
                {   
                    //ок. тут нужно обработать полученый пакет
                    // сверить CRC
                    // по сумма по исключаещему или должна быть равна нулю
                    if (MNP_CRC)  // если CRC не равна нулю
                    {
                        MNP_message_reset ();
                        return ERR_MNP_CRC;
                    }

                    // передать сообщение на обработку парсеру
                    MNP_message_mode=MNP_WAIT_END; // готовы начинать принимать новое сообщение

                }
                else // если мы не в режиме ожидания конца текущего пакета
                {
                    MNP_message_reset(); // все сбрасываем и возвращаем ошибку
                    return ERR_MNP_END_UNEXPECTED;
                }                

                break;
            default: // пришли данные
              
                if (MNP_message_counter>MNP_MESSAGE_BUFFER_SIZE) return ERR_MNP_MESSAGE_OVERFLOW; // если буфер сообщения переполнился
                MNP_message_buffer[MNP_message_counter++]=data;
                MNP_CRC^=data;
        }
        
        

    }
    
}
unsigned char CRC_convert(unsigned char H,unsigned char L)
{
  unsigned char res=0;
  if ((H >= '0') && (H <= '9')) res+=(H-'0')<<4;
  if ((H >= 'A') && (H <= 'F')) res+=(H-'A'+10)<<4;
  if ((L >= '0') && (L <= '9')) res+=(L-'0');
  if ((L >= 'A') && (L <= 'F')) res+=(L-'A'+10);
  return res;
}