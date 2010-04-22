#include <avr/io.h>
#include <avr/interrupt.h>
//#include <UART.h>
#include <my_MNEA.h>
#include <stdlib.h>


//������� ��������� � ������������ ��������� �� UART-a
//��������� ����� ���������� � ������������ ����������� �����

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
                debug_counter++;
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

// ��������� ������� �� ������ � �����
// H-������� ����, L- ������� ����
char str_to_hex(char H, char L)
{
    char res=0;
    if ((H >= '0') && (H <= '9')) res=(H-'0')<<4;
        else if ((H >= 'A') && (H <= 'F')) res=(H-'A'+10)<<4;
    if ((L >= '0') && (L <= '9')) res+=(L-'0')<<4;
    else if ((L >= 'A') && (L <= 'F')) res+=(L-'A'+10)<<4;    
    return res;
}


// ������� ��������� ����� ������ � ������
// �������� � ������ � �� len
// ���������� 0 - ���� ����������� 1-���� ���������
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