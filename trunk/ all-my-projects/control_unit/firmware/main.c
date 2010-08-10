#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "control_unit.h"

// Declare your global variables here
unsigned char dat;

int main(void)
{

unsigned char i=0;
unsigned char j=0;


// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
PORTA=0xFF;
DDRA=0x00;
PORTD=0x00;
DDRD=0x00;

DDRC=0;//0xF0;
PORTC=0;//0xF0;
sei();  // Global enable interrupts

control_unit_init();
display_on();

while (1)
      {


        _delay_ms(75);
      	i++;
        j++;
	 	if (i>7) i=0;
        if (j>199) j=0;
      //	display_digits[0]=i;
      //	display_digits[1]=i;
      //	display_digits[2]=i;
      //	display_digits[3]=i;
	  display_animation(0,i);
	 	//display_char_out(1,i);
                display_char_out(1,j/2);
		//display_digits[2]=10;
		//display_digits[3]=10;
      	//display_repaint();
		
       }
}
