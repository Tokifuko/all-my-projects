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


// Read the 8 most significant bits
// of the AD conversion result
unsigned char read_adc(unsigned char adc_input)
{
 ADMUX=ADC_temp_set;
//ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
//// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCH;
}
 


// USI counter overflow interrupt service routine
//interrupt [USI_OVF] void usi_ovf_isr(void)
//{
// Place your code here

//}

void led0_set (unsigned char on_off)
{
  
  
  if (on_off==1)
  {
    DDRA_DDA2=1;
    //DDRA|=(1<<PA2);
    //PORTA&=~(1<<PA2);
    PORTA_PORTA2=0;
  }

  else
  {
    DDRA_DDA2=0;
    //PORTA|=(1<<PA2);
    //DDRA&=~(1<<PA2);
    PORTA_PORTA2=1;
  }
}

void OE_set (unsigned char on_off)
{ 
  
    DDRA_DDA0=1;
  
  if (on_off==1)PORTA_PORTA0=1;
  else PORTA_PORTA0=0;
}
void LE_set (unsigned char on_off)
{
    DDRA_DDA1=1;  
  if (on_off==1)   PORTA_PORTA1=1;
  else    PORTA_PORTA1=0;
}

void key0_event (void)
{
  led0_set (1);
}

void SPI_DATA_TO_LED (char data)
{
  USIDR=data;
  OE_set(1);
  char i=0;
  while (i!=16)
  {
    i++;
    USICR_USITC=1;
  }
  LE_set(1);
  LE_set(0);
  OE_set(0);
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
DDRA=0xFF;

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

// Universal Serial Interface initialization
// Mode: Three Wire (SPI)
// Clock source: Reg.=ext. pos. edge, Cnt.=USITC
// USI Counter Overflow Interrupt: On
USICR=0x5A;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
ADCSRB=0x00;

// ADC initialization
// ADC Clock frequency: 1000,000 kHz
// ADC Bipolar Input Mode: Off
// ADC Auto Trigger Source: Free Running
// Only the 8 most significant bits of
// the AD conversion result are used
// Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
// ADC4: On, ADC5: On, ADC6: On, ADC7: On
DIDR0=0x00;
ADCSRA=0xA2;
ADCSRB&=0x68;
ADCSRB|=0x10;

while (1) 
      {
      // Place your code here
SPI_DATA_TO_LED(0xFF);
        
        //led0_set(0);
       delay_ms(100);
       //SPI_DATA_TO_LED(0x00);
      // delay_ms(100);
      }
}
