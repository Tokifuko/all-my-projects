

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <util/delay.h>
#include "control_unit.h"




unsigned char curent_ind=0;
volatile unsigned char display_digits [DISPLAY_NAMBER];
unsigned char rx_buf [32];
unsigned char rx_buf_counter=0;

void control_unit_init(void)
{
	DDRA=0;		// ��� ������ ��� �����
	PORTA=0xFF;  // ������ ��������
	
	display_off();
    Dig_init();

}

unsigned char Dig[27];
void Dig_init(void)
{
  Dig[0] = (DISPLAY_a+DISPLAY_b+DISPLAY_c+DISPLAY_d+DISPLAY_e+DISPLAY_f);   		// ���� ��������� � ����� ������,
  Dig[1] = (DISPLAY_b+DISPLAY_c);           										// ����� ����� �������� ������ ��
  Dig[2] =  (DISPLAY_a+DISPLAY_b+DISPLAY_g+DISPLAY_e+DISPLAY_d);     				// 255. ���� � ����� �������, ��
  Dig[3] =  (DISPLAY_a+DISPLAY_b+DISPLAY_g+DISPLAY_c+DISPLAY_d);     				// �������� �� �����.
  Dig[4] = (DISPLAY_f+DISPLAY_g+DISPLAY_b+DISPLAY_c);       						// ����� �������� �������������
  Dig[5] = (DISPLAY_a+DISPLAY_f+DISPLAY_g+DISPLAY_c+DISPLAY_d);     				// ������ ��������� ����������
  Dig[6] = (DISPLAY_a+DISPLAY_f+DISPLAY_g+DISPLAY_c+DISPLAY_d+DISPLAY_e);
  Dig[7] = (DISPLAY_a+DISPLAY_b+DISPLAY_c);
  Dig[8] = (DISPLAY_a+DISPLAY_b+DISPLAY_c+DISPLAY_d+DISPLAY_e+DISPLAY_f+DISPLAY_g);
  Dig[9] = (DISPLAY_a+DISPLAY_b+DISPLAY_c+DISPLAY_d+DISPLAY_f+DISPLAY_g);
  Dig[10] = 0;  															  		// ���������� ������������
	Dig[11] =DISPLAY_d;				// �������� ��� �������
	Dig[12] =DISPLAY_d+DISPLAY_c;
	Dig[13] =DISPLAY_c+DISPLAY_b;
	Dig[14] =DISPLAY_b+DISPLAY_a;
	Dig[15] =DISPLAY_a;
	Dig[16] =0;
	Dig[17] =0;
	Dig[18] =0;

	Dig[19] =DISPLAY_d;			// �������� ��� ������
	Dig[20] =0;
	Dig[21] =0;
	Dig[22] =0;
	Dig[23] =DISPLAY_a;
	Dig[24] =DISPLAY_a+DISPLAY_f;
	Dig[25] =DISPLAY_f+DISPLAY_e;
	Dig[26] =DISPLAY_e+DISPLAY_d;	
}


inline void display_on(void)
{
	DISPLAY_POW_DDR |=(1<<DISPLAY_POW_PIN);  // ��������� ���������� �������
    DISPLAY_POW_PORT &=~(1<<DISPLAY_POW_PIN); // ���������� ����������� �����
	
	DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); // ������ ������������� �� 1. ������� ���� LE=0
	DISPLAY_LE_DDR |=(1<<DISPLAY_LE_PIN);  // LE - �����

    DISPLAY_OE_PORT &=~(1<<DISPLAY_OE_PIN); //OE- ���������, �������� ���������� �����
    DISPLAY_OE_DDR |=(1<<DISPLAY_OE_PIN);   //�������� ����������, �������� ���� �������

	DISPLAY_TX_PORT &=~(1<<DISPLAY_TX_PIN);
	DISPLAY_TX_DDR |=(1<<DISPLAY_TX_PIN);	// TX-����� ������

	DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN);	// CLK � ����. ������ ����������� �� �������������� ������
	DISPLAY_CLK_DDR |=(1<<DISPLAY_CLK_PIN);  // CLK - �����

}

inline void display_off(void)
{
	DISPLAY_POW_DDR &=~(1<<DISPLAY_POW_PIN);  // ��������� ���������� �������
    DISPLAY_POW_PORT &=~(1<<DISPLAY_POW_PIN); // ������ ��� �� �����, �� ����� �������� ���� ���
	
	DISPLAY_LE_DDR &=~ (1<<DISPLAY_LE_PIN);  // ��������� ����
	DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); // ������ ��� �� �����
  
    DISPLAY_OE_DDR &=~ (1<<DISPLAY_OE_PIN);   //�������� ����
    DISPLAY_OE_PORT &=~(1<<DISPLAY_OE_PIN); //������� �� �����
	
	DISPLAY_TX_DDR &=~ (1<<DISPLAY_TX_PIN);	// ��������� ���� ������
    DISPLAY_TX_PORT &=~(1<<DISPLAY_TX_PIN); //������� �� �����

	DISPLAY_CLK_DDR &=~(1<<DISPLAY_CLK_PIN);  // CLK - ����
	DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN);	// CLK � ����. ������ ����������� �� �������������� ������
}

inline void display_LED_on(void)
{
	// ��������� ����� ����������, ���� ������� �� ����� ������.
	// � ��������� ������ ��������� ����� ���������
	DISPLAY_LED_DDR |=(1<<DISPLAY_LED_PIN);   // ������
    DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN); // ����� ����������
}

inline void display_LED_off(void)
{
	// ��������� ����� ����������, ���� ������� �� ����� ������.
	// � ��������� ������ ��������� ����� ���������
	DISPLAY_LED_DDR &=~ (1<<DISPLAY_LED_PIN);   // ��� ��� ����
    DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN); // ������ �� �����
}

void display_repaint(void)
{
	DISPLAY_LE_DDR |=(1<<DISPLAY_LE_PIN); // LE ��� �����
	DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); // ������ ������������� �� 1. ������� ���� LE=0
	unsigned char i=0;
	while (i!=DISPLAY_NAMBER)
	{
		// �������� �� �������� ���������, ���, ��������������� �������� �����
		display_byte_transmit(Dig[display_digits[i]]);
		i++;
	}
	DISPLAY_LE_PORT |=(1<<DISPLAY_LE_PIN); // ������ ������������� �� 1.
	DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); // � ������� LE=0
	DISPLAY_LE_DDR &=~ (1<<DISPLAY_LE_PIN); // ��������� LE

}


void display_byte_transmit(char data_byte)
{
	DISPLAY_TX_DDR |=(1<<DISPLAY_TX_PIN); // TX ��� �����

	DISPLAY_CLK_DDR |= (1<<DISPLAY_CLK_PIN);  // CLK - �����
	DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN);	// ������ ���� � ����
	unsigned char i=0;
	while (i!=8)
	{
		if (data_byte & (1<<i)) DISPLAY_TX_PORT =(1<<DISPLAY_TX_PIN);
			else DISPLAY_TX_PORT &=~(1<<DISPLAY_TX_PIN);

		DISPLAY_CLK_PORT |= (1<<DISPLAY_CLK_PIN); // �� �������������� ����� ������ � �������
		i++;
		DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN); // ������� � ����
	}
	DISPLAY_TX_DDR &=~ (1<<DISPLAY_TX_PIN);	//��������� TX
	DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN); // ��������� CLK
}


/************************************************************************************
*	display_char_out																*
*	������� ������� ����� �� 0, �� 99 �� ��� ���������� �������� ��� ������.		*
*	������� ���������.																*
*		ind. 0-������� ����������; 1-������;										*
*		char_data - ���� �� 0 �� 99		(���� ������ - ������� 99)					*
************************************************************************************/

void display_char_out(unsigned char ind ,unsigned char char_data )
{
	div_t x;
  	x=div(char_data,100);//�������� ��� ������ 100
  	x=div(x.rem,10);
	if (ind>1) ind=1;
	if (DISPLAY_NAMBER<4) ind=0;
	display_digits [ind*2]= x.quot;
	display_digits [1+(ind*2)]=x.rem;
	display_repaint();
}
/************************************************************************************
*	display_animation																*
*	������� ������� ��� �������� �� ��� ���������� �������� ��� ������.				*
*	������� ���������.																*
*		ind. 0-������� ����������; 1-������;										*
*		animation_step - ��� �������� 	(�� 8 �����)								*
************************************************************************************/

void display_animation(unsigned char ind ,unsigned char animation_step )
{
	if (animation_step>7) animation_step=7;
	if (ind>1) ind=1;
	if (DISPLAY_NAMBER<4) ind=0;

	display_digits [1+(ind*2)]=animation_step+11;		// � 11-�� ������� ���� �������� ��� ������
	display_digits [ind*2]=animation_step+19;	// � 19 ��� ������� ����������

	display_repaint();
}
