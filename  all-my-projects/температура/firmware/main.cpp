/*****************************************************
This program was produced by the
CodeWizardAVR V2.04.6 Evaluation
Automatic Program Generator
� Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
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
#include "EEPROM_func.cpp"

// Timer 0 overflow interrupt service routine
#pragma vector = TIM0_OVF_vect 
__interrupt void TIM0_OVF_vect_isr(void)
{
  delay_counter++;
  if (delay_counter>7000)delay_counter=0;
  
  if (delay_counter==0)
  {
    sec_counter++;    
    if (triger==1) triger=0;
      else triger=1;
  }
   
}


void led0_set (unsigned char on_off)
{
  if (on_off==1)DDRA_DDA2=1;
  else DDRA_DDA2=0;
}

void led1_set (unsigned char on_off)
{
  if (on_off==1)DDRA_DDA3=1;
  else DDRA_DDA3=0;
}



void key0_event (void)          // ������ T+
{
  if (curent_mode==SETUP_MODE) 
  {
    set_temp++;                         // � ������ ��������� ����������� ���������� �������� 
    if (set_temp>99)set_temp=99;
    EEPROM_write(EEPROM_ADDR,set_temp); // ���������� ������������� ��������
  }
   
  if (curent_mode==IDLE_MODE)curent_mode=SHOW_MODE;
    else curent_mode=SETUP_MODE;
  sec_counter=0;
  led1_set(1); // �������� ���������. ������ �� �� ������� sec_counter
}

void key1_event (void)      // ������ T-
{
  if (curent_mode==SETUP_MODE) 
  {
    set_temp--;  // � ������ ��������� ����������� �������� �������� 
    if (set_temp<1)set_temp=1;
    EEPROM_write(EEPROM_ADDR,set_temp); // ���������� ������������� ��������
  }
  if (curent_mode==IDLE_MODE)curent_mode=SHOW_MODE;
    else curent_mode=SETUP_MODE;
  sec_counter=0;
  led1_set(1); // �������� ���������. ������ �� �� ������� sec_counter
}


void temp_chek (void)
{
  float x;
  // ���������� �������� ����������� ��������
    x=read_adc();  
    if (x<f_sr_temp_curent) f_sr_temp_curent-=(f_sr_temp_curent-x)/TEMP_ACCURACY;
    else f_sr_temp_curent+=(x-f_sr_temp_curent)/TEMP_ACCURACY;
    ch_temp=f_sr_temp_curent-TEMP_OFFSET;
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
DDRA_DDA7=1;

// Port B initialization
// Func3=In Func2=In Func1=In Func0=In 
// State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 4000,000 kHz
// Mode: Fast PWM top=FFh
// OC0A output: Disconnected
// OC0B output: Inverted PWM
TCCR0A=0x23;
TCCR0B=0x01;
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
TIMSK0=0x01;
// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
ADCSRB=0x00;

 
SPI_init(); 
ADC_init();

unsigned char key0_counter=50;
unsigned char key1_counter=50;
unsigned char key0_state=KEY_OFF;
unsigned char key1_state=KEY_OFF;

// Global enable interrupts
SREG_I=1;
set_temp=EEPROM_read(EEPROM_ADDR);
FAN_SPEED_CONTROL=FAN_SPEED_OFF;
f_sr_temp_curent=40+TEMP_OFFSET;
ch_temp=40;
while (1)  
    {
//-----------��������� ������ KEY_0 PINB2-----------------
      if (PINB_PINB2) key0_counter--;
        else key0_counter++;
      if (key0_counter>KEY_TIME_OUT) // ������ ������ 
      { 
        key0_counter=KEY_TIME_OUT;
        if (key0_state==KEY_OFF) 
        {
          key0_state=KEY_ON;
          key0_event(); // ��� �������������� ������� ������- ��������� �������
        }
      }
      if (key0_counter<1) // ������ ������ 
      { 
        key0_counter=1;
        if (key0_state==KEY_ON) key0_state=KEY_OFF;
      }          
//----------------------------------------------------------------
//-----------��������� ������ KEY_1 PINB1-----------------
      if (PINB_PINB1) key1_counter--;
        else key1_counter++;
      if (key1_counter>KEY_TIME_OUT) // ������ ������ 
      { 
        key1_counter=KEY_TIME_OUT;
        if (key1_state==KEY_OFF) 
        {
          key1_state=KEY_ON;
          key1_event(); // ��� �������������� ������� ������- ��������� �������
        }
      }
      if (key1_counter<1) // ������ ������ 
      { 
        key1_counter=1;
        if (key1_state==KEY_ON) key1_state=KEY_OFF;
      }          
//---------------------------------------------------------------- 
//------���������� �������� � ������ ������� �  ������������ ������� �� �������---      
    switch (curent_mode) 
    {
      case    IDLE_MODE:                     
        Display_off();
      //  led0_set(triger);
        break;
      case    SETUP_MODE:                    
        if (sec_counter>SETUP_MODE_TIMEOUT) curent_mode=SHOW_MODE;
        if (triger)Display_on(); // ������ �������
          else Display_off();
        Display(set_temp);      // �� ������� ����������� ������������
       // led0_set(0);
        break;
      case    SHOW_MODE:  
        Display_on();
        if (sec_counter>SHOW_MODE_TIMEOUT) curent_mode=IDLE_MODE;
        Display(ch_temp); // �� ������� ������� ������������
       // led0_set(1);
        break;        
    }
//---------------------------------------------------------------------------
 
// ���������� ������������ � ����������� �� ������� ����������� � �������� �����������
    switch (FAN_SPEED_CONTROL) 
    {
      case    FAN_SPEED_OFF:
        //if (ch_temp>42)FAN_SPEED_CONTROL=FAN_SPEED_SLOW;//(set_temp+TEMP_OFF+FAN_MODE_OFFSET))//�������� ����>����+(-5)+1
        if (ch_temp>=(set_temp+TEMP_OFF+FAN_MODE_OFFSET))//�������� ����>����+(-5)+1
          FAN_SPEED_CONTROL=FAN_SPEED_SLOW;
          led0_set(0);led1_set(0);
        break; 
        
      case    FAN_SPEED_SLOW:
        if (ch_temp<=(set_temp+TEMP_OFF-FAN_MODE_OFFSET))
          FAN_SPEED_CONTROL=FAN_SPEED_OFF;
        if (ch_temp>=(set_temp+TEMP_SLOW+FAN_MODE_OFFSET))
          FAN_SPEED_CONTROL=FAN_SPEED_MEDI;
        led0_set(1);led1_set(0);
        break;
         
      case    FAN_SPEED_MEDI:
        if (ch_temp<=(set_temp+TEMP_SLOW-FAN_MODE_OFFSET))
          FAN_SPEED_CONTROL=FAN_SPEED_SLOW;
        if (ch_temp>=(set_temp+TEMP_MEDI+FAN_MODE_OFFSET))
          FAN_SPEED_CONTROL=FAN_SPEED_FAST;
        led0_set(0);led1_set(1);
        break;
        
      case    FAN_SPEED_FAST:
        if (ch_temp<=(set_temp+TEMP_MEDI-FAN_MODE_OFFSET))
          FAN_SPEED_CONTROL=FAN_SPEED_MEDI;
        led0_set(1);led1_set(1);
        break;        
    }
//-------------------------------------------------------------------    

    temp_chek();     
 // if (sec_counter==1) led1_set(0); // ����� ������� ������ ����� ��� ������� ����� ����


    }
}
