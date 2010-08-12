/* 
 * File:   UART1_to_SPI.h
 * Author: ?????????????
 *
 * Created on 27 Апрель 2010 г., 19:19
 */

#ifndef _CONTROL_UNIT_H
#define	_CONTROL_UNIT_H

#ifdef	__cplusplus
extern "C" {
#endif

    // управление светодиодом LED1 на плате пульта
#define DISPLAY_LED_DDR     DDRC
#define DISPLAY_LED_PORT    PORTC
#define DISPLAY_LED_PIN     PC7

    // пин LATCH_EN на драйверах семисегментников
#define DISPLAY_LE_DDR      DDRD
#define DISPLAY_LE_PORT     PORTD
#define DISPLAY_LE_PIN      PD6

    // пин OE. Включает-выключает семисигментники
#define DISPLAY_OE_DDR      DDRD
#define DISPLAY_OE_PORT     PORTD
#define DISPLAY_OE_PIN      PD7

    // CLK от USART. на драйверы семисигментников
#define DISPLAY_CLK_DDR     DDRB
#define DISPLAY_CLK_PORT    PORTB
#define DISPLAY_CLK_PIN     PB0


    // Выход TX на плату пульта с USART-а
#define DISPLAY_TX_DDR     DDRD
#define DISPLAY_TX_PORT    PORTD
#define DISPLAY_TX_PIN     PD1

    // питание подаваемое на пульт через транзистор
#define DISPLAY_POW_DDR     DDRD
#define DISPLAY_POW_PORT    PORTD
#define DISPLAY_POW_PIN     PD4

	// у нас 8 кнопок подключеных на порт А
#define  KEY_0_STATE 		((PINA>>PINA0) & 1)
#define  KEY_1_STATE 		((PINA>>PINA1) & 1)
#define  KEY_2_STATE 		((PINA>>PINA2) & 1)
#define  KEY_3_STATE 		((PINA>>PINA3) & 1)
#define  KEY_4_STATE 		((PINA>>PINA4) & 1)
#define  KEY_5_STATE 		((PINA>>PINA5) & 1)
#define  KEY_6_STATE 		((PINA>>PINA6) & 1)
#define  KEY_7_STATE 		((PINA>>PINA7) & 1)

	// всего индикаторов 4 штуки.
#define DISPLAY_NAMBER      4


#define DISPLAY_a 32       // Эти макросы содержат числа, соответствующие двойке,
#define DISPLAY_b 16       // возведенной в степень, равной номеру "ножки" того
#define DISPLAY_c 4      // порта, к которому подключен сегмент индикатора с
#define DISPLAY_d 2      // одноименным макросу названием. Для того, чтобы вывести
#define DISPLAY_e 1      // какую-либо цифру на индикатор, нужно отправить в порт
#define DISPLAY_f 128       // число 255 минус сумму соответствующих сегментам макросов.
#define DISPLAY_g 64       // Эти числа позволяют сделать программу независимой от подключения.
#define DISPLAY_DP 8    // Измените эти числа, если индикатор выводит букву "зю"

//unsigned char DigNumber = 0;
extern unsigned char Dig[27]; // Массив, в котором хранятся числа, которые нужно
// вывести через порт на индикатор, чтобы он показал цифру, равную номеру
// элемента массива. Числа зависят только от макросов.

void control_unit_init(void); // чтоб все тут проинициализировать
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

