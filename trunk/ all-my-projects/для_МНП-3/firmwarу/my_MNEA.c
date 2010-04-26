#include <avr/io.h>
#include <avr/interrupt.h>
//#include <UART.h>
#include <my_MNEA.h>
#include <stdlib.h>
#include <string.h>

//������� ��������� � ������������ ��������� �� UART-a
//��������� ����� ���������� � ������������ ����������� �����

char MNP_CRC=0;
unsigned char rx_CRC;
unsigned char MNP_message_length=0;
char MNP_message_buffer[MNP_MESSAGE_BUFFER_SIZE];
unsigned char MNP_message_counter=0;
unsigned char MNP_message_mode =MNP_WAIT_START;
unsigned char g_day=0;
unsigned char g_month=0;
unsigned char g_yaer=0;
unsigned char g_minute=0;
unsigned char g_hour=0;
unsigned char g_sec=0;
unsigned char g_m_sec=0;
unsigned char GL_valid_flag=0;
unsigned char GP_valid_flag=0;
unsigned char GN_valid_flag=0;
unsigned char sattelite_system=GL_and_GP;


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
               // debug_counter++;
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

/*
char MNP_send_message(void)//char *str)
{
    char tx_CRC=0;
    char tx_CRC_H,tx_CRC_L;
    UART_putchar('$');
    
    while (*str)
    {
 
	tx_CRC^=*str;
        UART_putchar(*str);
		str++;
    }
    UART_putchar('*');

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
*/

char MNP_message_parser(void)
{
    char* res;
    switch (sattelite_system) //����� ������������� �������?
    {
        case GL_only: 
            res=strstr(MNP_message_buffer,GLRMS_message); // ������� ��������� �� �������
            if (res!=NULL) GL_valid_flag=MNP_RMS_message_parser();
            break;
        case GP_only:
            res=strstr(MNP_message_buffer,GPRMS_message); // ������� ��������� �� GPS
            if (res!=NULL) GP_valid_flag=MNP_RMS_message_parser();
            break;
        case GL_and_GP:
            res=strstr(MNP_message_buffer,GNRMS_message); // ������� ��������� �� ������� + GPS
            if (res!=NULL) GN_valid_flag=MNP_RMS_message_parser();
            break;            
    }
    MNP_message_reset (); //��������� � ����� ������ ���������
   
   return 1;
}

// ��������� ������� �� ������ � �����
// H-������� ����, L- ������� ����
char str_to_hex(char H, char L)
{
    char res=0;
    if ((H >= '0') && (H <= '9')) res=(H-'0')<<4;
        else if ((H >= 'A') && (H <= 'F')) res=(H-'A'+10)<<4;
    if ((L >= '0') && (L <= '9')) res+=(L-'0');
    else if ((L >= 'A') && (L <= 'F')) res+=(L-'A'+10);
    return res;
}
char str_to_dec(char H, char L)
{
    char res=0;
    if ((H >= '0') && (H <= '9')) res=(H-'0')*10;
    if ((L >= '0') && (L <= '9')) res+=(L-'0');
    return res;
}

// ������������ GxRMS ���������
// ��������� �� ���� ���� � �����, �������� ���� ��������
char MNP_RMS_message_parser(void)
{
    char* param;
    param=MNP_get_param(2);

    if (*param=='V') return 0; // ������� �� �����
    if (*param=='A') return 0; // �������� � ���������� ������
   // if (*param=='D') return 0; // �������� � ��������������� ������   

    param=MNP_get_param(1);
    g_hour=str_to_dec(*param,*(param+1));
    g_minute=str_to_dec(*(param+2),*(param+3));
    g_sec=str_to_dec(*(param+4),*(param+5));
    g_m_sec=str_to_dec(*(param+7),*(param+8));

    param=MNP_get_param(9);
    g_day=str_to_dec(*param,*(param+1));
    g_month=str_to_dec(*(param+2),*(param+3));
    g_yaer=str_to_dec(*(param+4),*(param+5));
    return 1;
}

char* MNP_get_param(char par_number)
{
    char i=0;
    char *res;
    res=MNP_message_buffer;
   // par_number++;
    while (i<par_number)
    {
        res=strchr(res,',');
        res++;
        i++;
    }
    return res;
}