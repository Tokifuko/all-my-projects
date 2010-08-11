

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/wdt.h>
#include <stdlib.h>
#include <util/delay.h>
#include "control_unit.h"
#include "/cc/cc1101.h"



unsigned char curent_ind=0;
volatile unsigned char display_digits [DISPLAY_NAMBER];
unsigned char rx_buf [32];
unsigned char rx_buf_counter=0;

void control_unit_init(void)
{
	DDRA=0;		// все кнопки как входы
	PORTA=0xFF;  // подтяг включаем
	
	display_off();
    Dig_init();

}

unsigned char Dig[11];
void Dig_init(void)
{
  Dig[0] = (DISPLAY_a+DISPLAY_b+DISPLAY_c+DISPLAY_d+DISPLAY_e+DISPLAY_f);   		// Если индикатор с общим анодом,
  Dig[1] = (DISPLAY_b+DISPLAY_c);           										// нужно сумму макросов отнять от
  Dig[2] =  (DISPLAY_a+DISPLAY_b+DISPLAY_g+DISPLAY_e+DISPLAY_d);     				// 255. Если с общим катодом, то
  Dig[3] =  (DISPLAY_a+DISPLAY_b+DISPLAY_g+DISPLAY_c+DISPLAY_d);     				// отнимать не нужно.
  Dig[4] = (DISPLAY_f+DISPLAY_g+DISPLAY_b+DISPLAY_c);       						// Имена макросов соответствуют
  Dig[5] = (DISPLAY_a+DISPLAY_f+DISPLAY_g+DISPLAY_c+DISPLAY_d);     				// именам сегментов индикатора
  Dig[6] = (DISPLAY_a+DISPLAY_f+DISPLAY_g+DISPLAY_c+DISPLAY_d+DISPLAY_e);
  Dig[7] = (DISPLAY_a+DISPLAY_b+DISPLAY_c);
  Dig[8] = (DISPLAY_a+DISPLAY_b+DISPLAY_c+DISPLAY_d+DISPLAY_e+DISPLAY_f+DISPLAY_g);
  Dig[9] = (DISPLAY_a+DISPLAY_b+DISPLAY_c+DISPLAY_d+DISPLAY_f+DISPLAY_g);
  Dig[10] = 0;  															  		// отсутствие изображенрия
	Dig[11] =DISPLAY_d;				// анимация для правого
	Dig[12] =DISPLAY_d+DISPLAY_c;
	Dig[13] =DISPLAY_c+DISPLAY_b;
	Dig[14] =DISPLAY_b+DISPLAY_a;
	Dig[15] =DISPLAY_a;
	Dig[16] =0;
	Dig[17] =0;
	Dig[18] =0;

	Dig[19] =DISPLAY_d;			// анимация для левого
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
	DISPLAY_POW_DDR |=(1<<DISPLAY_POW_PIN);  // открываем транзистор питания
    DISPLAY_POW_PORT &=~(1<<DISPLAY_POW_PIN); // транзистор открывается нулем
	
	DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); // данные защелкиваются по 1. поэтому пока LE=0
	DISPLAY_LE_DDR |=(1<<DISPLAY_LE_PIN);  // LE - выход

    DISPLAY_OE_PORT &=~(1<<DISPLAY_OE_PIN); //OE- инверсный, включает индикаторы нулем
    DISPLAY_OE_DDR |=(1<<DISPLAY_OE_PIN);   //Включаем индикаторы, всеравно пуль включен

	DISPLAY_TX_PORT &=~(1<<DISPLAY_TX_PIN);
	DISPLAY_TX_DDR |=(1<<DISPLAY_TX_PIN);	// TX-выход данных

	DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN);	// CLK в ноль. данные принимаются по положительному фронту
	DISPLAY_CLK_DDR |=(1<<DISPLAY_CLK_PIN);  // CLK - выход

}

inline void display_off(void)
{
	DISPLAY_POW_DDR &=~(1<<DISPLAY_POW_PIN);  // закрываем транзистор питания
    DISPLAY_POW_PORT &=~(1<<DISPLAY_POW_PIN); // подтяг там не нужен, на плате резистор есть уже
	
	DISPLAY_LE_DDR &=~ (1<<DISPLAY_LE_PIN);  // отключаем вход
	DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); // подтяг там не нужен
  
    DISPLAY_OE_DDR &=~ (1<<DISPLAY_OE_PIN);   //отключам вход
    DISPLAY_OE_PORT &=~(1<<DISPLAY_OE_PIN); //подтяга не будет
	
	DISPLAY_TX_DDR &=~ (1<<DISPLAY_TX_PIN);	// отключаем вход данных
    DISPLAY_TX_PORT &=~(1<<DISPLAY_TX_PIN); //подтяга не будет

	DISPLAY_CLK_DDR &=~(1<<DISPLAY_CLK_PIN);  // CLK - вход
	DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN);	// CLK в ноль. данные принимаются по положительному фронту
}

inline void display_LED_on(void)
{
	// светодиод будет зажигаться, если питание на пульт подано.
	// В противном случае светодиод нужно отключать
	DISPLAY_LED_DDR |=(1<<DISPLAY_LED_PIN);   // зажечь
    DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN); // нулем зажигается
}

inline void display_LED_off(void)
{
	// светодиод будет зажигаться, если питание на пульт подано.
	// В противном случае светодиод нужно отключать
	DISPLAY_LED_DDR &=~ (1<<DISPLAY_LED_PIN);   // пин как вход
    DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN); // подтяг не нужен
}

void display_repaint(void)
{
	DISPLAY_LE_DDR |=(1<<DISPLAY_LE_PIN); // LE как выход
	DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); // данные защелкиваются по 1. поэтому пока LE=0
	unsigned char i=0;
	while (i!=DISPLAY_NAMBER)
	{
		// передаем на оередной индикатор, код, соответствующий заданной цифре
		display_byte_transmit(Dig[display_digits[i]]);
		i++;
	}
	DISPLAY_LE_PORT |=(1<<DISPLAY_LE_PIN); // данные защелкиваются по 1.
	DISPLAY_LE_PORT &=~(1<<DISPLAY_LE_PIN); // и обратно LE=0
	DISPLAY_LE_DDR &=~ (1<<DISPLAY_LE_PIN); // отключаем LE

}


void display_byte_transmit(char data_byte)
{
	DISPLAY_TX_DDR |=(1<<DISPLAY_TX_PIN); // TX как выход

	DISPLAY_CLK_DDR |= (1<<DISPLAY_CLK_PIN);  // CLK - выход
	DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN);	// держим пока в нуле
	unsigned char i=0;
	while (i!=8)
	{
		if (data_byte & (1<<i)) DISPLAY_TX_PORT =(1<<DISPLAY_TX_PIN);
			else DISPLAY_TX_PORT &=~(1<<DISPLAY_TX_PIN);

		DISPLAY_CLK_PORT |= (1<<DISPLAY_CLK_PIN); // по положительному фрону данные в драйвер
		i++;
		DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN); // обратно в ноль
	}
	DISPLAY_TX_DDR &=~ (1<<DISPLAY_TX_PIN);	//отключаем TX
	DISPLAY_CLK_PORT &=~ (1<<DISPLAY_CLK_PIN); // отключаем CLK
}


/************************************************************************************
*	display_char_out																*
*	функция выводит число от 0, до 99 на два индикатора верхниие или нижние.		*
*	Входные параметры.																*
*		ind. 0-верхние индикаторы; 1-нижние;										*
*		char_data - исло от 0 до 99		(если больше - выводим 99)					*
************************************************************************************/

void display_char_out(unsigned char ind ,unsigned char char_data )
{
	div_t x;
  	x=div(char_data,100);//отсекаем что больше 100
  	x=div(x.rem,10);
	if (ind>1) ind=1;
	if (DISPLAY_NAMBER<4) ind=0;
	display_digits [ind*2]= x.quot;
	display_digits [1+(ind*2)]=x.rem;
	display_repaint();
}
/************************************************************************************
*	display_animation																*
*	функция выводит шаг анимации на два индикатора верхниие или нижние.				*
*	Входные параметры.																*
*		ind. 0-верхние индикаторы; 1-нижние;										*
*		animation_step - шаг анимации 	(на 8 шагов)								*
************************************************************************************/

void display_animation(unsigned char ind ,unsigned char animation_step )
{
	if (animation_step>7) animation_step=7;
	if (ind>1) ind=1;
	if (DISPLAY_NAMBER<4) ind=0;

	display_digits [1+(ind*2)]=animation_step+11;		// с 11-го символа идет анимация для левого
	display_digits [ind*2]=animation_step+19;	// с 19 для правого индикатора

	display_repaint();
}
