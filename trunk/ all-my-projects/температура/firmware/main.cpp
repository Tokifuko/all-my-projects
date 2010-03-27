/*****************************************************
This program was produced by the
CodeWizardAVR V2.04.6 Evaluation
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 25.03.2010
Author  : Freeware, for evaluation and non-commercial use only
Company : 
Comments: 


Chip type               : ATtiny24
AVR Core Clock frequency: 4,000000 MHz
Memory model            : Tiny
External RAM size       : 0
Data Stack size         : 32
*****************************************************/

#include "iotiny24.h"
#include "main.h"
#include "delay.h" 
#include "7_sigmentnik.cpp"
#include "ADC_modul.cpp"



void led0_set (unsigned char on_off)
{
  if (on_off==1)DDRA_DDA2=1;
  else DDRA_DDA2=0;
}



void key0_event (void)
{
  led0_set (1);
}

void temp_chek (void)
{
  int sum=0;
  char i=0;
  temp[temp_counter]=read_adc(ADC_temp_set);
  if ((temp_counter++)>TEMP_ARRAY)temp_counter=0;
  while ((i++)<=TEMP_ARRAY)sum+=temp[i];
  temp_curent=(sum/TEMP_ARRAY)-TEMP_OFFSET;
}
// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1

CLKPR=0x80;
CLKPR=0x00;


// Input/Output Ports initialization
// Port A initialization
// Func7=Out Func6=Out Func5=In Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func3=In Func2=In Func1=In Func0=In 
// State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Fast PWM top=FFh
// OC0A output: Disconnected
// OC0B output: Non-Inverted PWM
TCCR0A=0x23;
TCCR0B=0x00;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// External Interrupt(s) initialization
// INT0: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-11: Off
MCUCR=0x00;
GIMSK=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x00;
// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
ADCSRB=0x00;


SPI_init();
ADC_init();
unsigned int i=30;
  
while (1)  
      {
      // Place your code here
    Display(temp_curent);
    temp_chek();    
        led0_set(0);
       delay_ms(10); 
     
        i=i/8;
       //SPI_DATA_TO_LED(0x00);
       led0_set(1);
       delay_ms(10);
      }
}
