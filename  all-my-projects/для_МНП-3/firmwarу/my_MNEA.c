#include <avr/io.h>
#include <avr/interrupt.h>
//#include <UART.h>
#include <my_MNEA.h>


//������� ��������� � ������������ ��������� �� UART-a
//��������� ����� ���������� � ������������ ����������� �����

char MNP_CRC=0;
unsigned char rx_CRC;
unsigned char MNP_message_length=0;
char MNP_message_buffer[MNP_MESSAGE_BUFFER_SIZE];
unsigned char MNP_message_counter=0;
unsigned char MNP_message_mode =MNP_WAIT_START;
char str[]="$PPER,0*";

void MNP_message_reset ()
{
    MNP_CRC=0;
    MNP_message_length=0;
    MNP_message_counter=0;
    MNP_message_mode=MNP_WAIT_START;
}

char MNP_get_message(void)
{
    if (UART_rx_buffer_overflow)  // ���� ������������ ������
    {               // ��� ����������, � ���������� ������
        MNP_message_reset();
        UART_rx_overflow_reset();
        return ERR_RX_OVERFLOW;
    }
    char data;
    if (UART_rx_buffer_empty ) return 0;//����� ������
    
    data=UART_getchar();
    switch (MNP_message_mode)
    {
        case MNP_WAIT_START:// ���� ������ ���������
            // �������� ������ ���������,
            if (data=='$')
            {
                MNP_message_mode=MNP_GET_DATA;  // �������� ��������� ������
                MNP_CRC=0;// ��� ����������
                MNP_message_length=0;
                MNP_message_counter=0;
            }
            else return ERR_MNP_START_EXPECTED;
            break;
        case MNP_GET_DATA: // ��� �������� �������� ������
            // ��������� �� ���������� ��������� ��������
            if (data=='$') // ������ ������ ������ ���������
            {
                MNP_message_reset ();
                return ERR_MNP_START_UNEXPECTED;
            }
            if (data==0x0A) // ������ �������� ������
            {
                MNP_message_reset ();
                return ERR_MNP_LF_UNEXPECTED;  
            }
            if (data==0x0D)  // ������ �������� �������
            {
                MNP_message_reset ();
                return ERR_MNP_CR_UNEXPECTED;
            }
            
            if (data=='*') // ����� ����������� ������
            {
                MNP_message_mode=MNP_GET_CRC_H; // ������������� �� ����� CRC
                return 0;
            }
            
            if (MNP_message_counter>MNP_MESSAGE_BUFFER_SIZE) // ���� ����� ��������
            {
                MNP_message_reset ();
                return ERR_MNP_MESSAGE_OVERFLOW; // ���� ����� ��������� ������������
            }

            MNP_message_buffer[MNP_message_counter++]=data; //���� � �����
            MNP_CRC^=data; // ������� CRC
            break;

        case MNP_GET_CRC_H: // ����� �������� ������� ������ CRC
            // � ��������� ������ � �����
            if ((data >= '0') && (data <= '9')) rx_CRC=(data-'0')<<4;
            else if ((data >= 'A') && (data <= 'F')) rx_CRC=(data-'A'+10)<<4;
                else 
                    {
                        MNP_message_reset ();
                        return ERR_MNP_UNEXPECTED_CRC_CHAR;
                    }
            MNP_message_mode=MNP_GET_CRC_L;
            break;

        case MNP_GET_CRC_L: // ����� �������� ������� ������ CRC
            if ((data >= '0') && (data <= '9')) rx_CRC+=(data-'0');
            else if ((data >= 'A') && (data <= 'F')) rx_CRC+=(data-'A'+10);
                else
                    {
                        MNP_message_reset ();
                        return ERR_MNP_UNEXPECTED_CRC_CHAR;
                    }
            MNP_CRC^=rx_CRC;// ������� CRC
            if (!(MNP_CRC==0) ) //���� �� ������� �� ������ ����������
            {
                MNP_message_reset ();
                return ERR_MNP_CRC_ERROR;
            }
            MNP_message_mode=MNP_GET_CR;

            break;

        case MNP_GET_CR: //������ ���� ������ �������� �������
            if (data==0x0A) MNP_message_mode=MNP_GET_LF;// ������ �������� ��������
            else return ERR_MNP_CR_EXPECTED;

            break; 
        case MNP_GET_LF: // � � ����� ������ ���� ������ �������� ������
            if (data==0x0D) MNP_message_mode=MNP_WAIT_START;// ������ �������� ������
            else return ERR_MNP_LF_EXPECTED;
            break;
    }
    return 0;
}

char MNP_send_message(char *str)
{
    char tx_CRC=0;
    char i=0;
    while (str[i++]=='\0')
    {
        tx_CRC^=str[i];
        UART_putchar(str[i]);
    }
    UART_putchar('*');
    


    return 0; //UART_putchar(str++);
}
