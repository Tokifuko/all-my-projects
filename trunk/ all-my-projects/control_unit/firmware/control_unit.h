/* 
 * File:   UART1_to_SPI.h
 * Author: ?????????????
 *
 * Created on 27 ������ 2010 �., 19:19
 */

#ifndef _CONTROL_UNIT_H
#define	_CONTROL_UNIT_H

#ifdef	__cplusplus
extern "C" {
#endif

    // ���������� ����������� LED1 �� ����� ������
#define DISPLAY_LED_DDR     DDRC
#define DISPLAY_LED_PORT    PORTC
#define DISPLAY_LED_PIN     PC7

    // ��� LATCH_EN �� ��������� ����������������
#define DISPLAY_LE_DDR      DDRD
#define DISPLAY_LE_PORT     PORTD
#define DISPLAY_LE_PIN      PD6

    // ��� OE. ��������-��������� ���������������
#define DISPLAY_OE_DDR      DDRD
#define DISPLAY_OE_PORT     PORTD
#define DISPLAY_OE_PIN      PD7

    // CLK �� USART. �� �������� ����������������
#define DISPLAY_CLK_DDR     DDRB
#define DISPLAY_CLK_PORT    PORTB
#define DISPLAY_CLK_PIN     PB0


    // ����� TX �� ����� ������ � USART-�
#define DISPLAY_TX_DDR     DDRD
#define DISPLAY_TX_PORT    PORTD
#define DISPLAY_TX_PIN     PD1

    // ������� ���������� �� ����� ����� ����������
#define DISPLAY_POW_DDR     DDRD
#define DISPLAY_POW_PORT    PORTD
#define DISPLAY_POW_PIN     PD4

	// � ��� 8 ������ ����������� �� ���� �
#define  KEY_0_STATE 		((PINA>>PINA0) & 1)
#define  KEY_1_STATE 		((PINA>>PINA1) & 1)
#define  KEY_2_STATE 		((PINA>>PINA2) & 1)
#define  KEY_3_STATE 		((PINA>>PINA3) & 1)
#define  KEY_4_STATE 		((PINA>>PINA4) & 1)
#define  KEY_5_STATE 		((PINA>>PINA5) & 1)
#define  KEY_6_STATE 		((PINA>>PINA6) & 1)
#define  KEY_7_STATE 		((PINA>>PINA7) & 1)

	// ����� ����������� 4 �����.
#define DISPLAY_NAMBER      4


#define DISPLAY_a 32       // ��� ������� �������� �����, ��������������� ������,
#define DISPLAY_b 16       // ����������� � �������, ������ ������ "�����" ����
#define DISPLAY_c 4      // �����, � �������� ��������� ������� ���������� �
#define DISPLAY_d 2      // ����������� ������� ���������. ��� ����, ����� �������
#define DISPLAY_e 1      // �����-���� ����� �� ���������, ����� ��������� � ����
#define DISPLAY_f 128       // ����� 255 ����� ����� ��������������� ��������� ��������.
#define DISPLAY_g 64       // ��� ����� ��������� ������� ��������� ����������� �� �����������.
#define DISPLAY_DP 8    // �������� ��� �����, ���� ��������� ������� ����� "��"

//unsigned char DigNumber = 0;
extern unsigned char Dig[27]; // ������, � ������� �������� �����, ������� �����
// ������� ����� ���� �� ���������, ����� �� ������� �����, ������ ������
// �������� �������. ����� ������� ������ �� ��������.

void control_unit_init(void); // ���� ��� ��� �������������������
void Dig_init(void);
void display_on(void);
void display_off(void);
void display_LED_on(void);
void display_LED_off (void);

void display_repaint(void);
void display_byte_transmit(char);
void display_char_out(unsigned char ind ,unsigned char char_data );
void display_animation(unsigned char ind ,unsigned char animation_step );




extern volatile unsigned char display_digits [DISPLAY_NAMBER];



#ifdef	__cplusplus
}
#endif

#endif	/* _CONTROL_UNIT_H */

