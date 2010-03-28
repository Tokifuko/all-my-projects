/*****************************************************
This program was produced by the
CodeWizardAVR V2.03.4 Standard
Automatic Program Generator
� Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : ATt24_proj
Version : 1
Date    : 09.01.2009
Author  : 
Company : 
Comments: 


Chip type           : ATtiny24
Clock frequency     : 7,378000 MHz
Memory model        : Tiny
External RAM size   : 0
Data Stack size     : 32
*****************************************************/
 

#include <iotiny24.h>
#include <intrinsics.h>
  
   
 
// error ���� 
#define BAD_MODE             1
#define NO_INPUT_CAPTURE     2
#define BAD_CAP_SENS_STEP    3
 
#define LED_PWM     OCR0B
#define MAX_LED_PWM     0x90   // ���� �� ����������� ������ ���������

#define LED_SPEED   512 
#define NOMINAL_I   10000
#define I_SENS      50

#define SLEEP_DELAY 20000   // �������� ����� �������� ��������� ����� � ��������� � ������ �����

#define NOMINAL_CAP      10000
#define CAP_SENS         30
#define KEY_ON      1
#define KEY_OFF     2
#define LED_ON      3
#define LED_OFF     4

#define PA3         3
unsigned int adc_data;
unsigned int delay_count;
unsigned int i_sr_cap;
unsigned char  sleep;
unsigned char mode;
unsigned char error_code;
unsigned char det_count;
unsigned char cap_sens_step;
unsigned char ch_AC_EN;
unsigned char ch_SR_RUN;
unsigned char INT0_FLAG;


void led_driver(void);
void power_down(void);
void power_up(void) ;
void deb(void);

// External Interrupt 0 service routine
//���������� ��� ��������� ������ �� ������  ���/����

#pragma vector = INT0_vect
__interrupt void INT0_vect_isr (void)
{ 

 // GIMSK_INT0=0;    // ��������� ���������� INT0.
 // __delay_cycles(32000);
  
 // PORTB_PORTB1=~PORTB_PORTB1;
 // sleep=0;
power_up();




// GIMSK_INT0=1;    // �������� ���������� �� INT0   

}

// Timer 0 overflow interrupt service routine
/*---------------------------------------------
    �������� ���������� ����������� �������� �����������
    ������������ �������� ������� �������� �������
    � ����������� �� ������� ���������� ��� ��������� �������      
---------------------------------------------------***/


#pragma vector = TIM0_OVF_vect 
__interrupt void TIM0_OVF_vect_isr(void)
{
  delay_count++;
  //OCR1A=adc_data;
   
}

/*-----------------------------------------------------
 � ����������� �� ������� ���������� ��� ��������� �������
-------------------------------------------------------*/
void led_driver(void)
{

  
  
  
switch (mode) 
    {
    case    KEY_ON:                    // ��� ��������� ������� 
        if (LED_PWM<MAX_LED_PWM) LED_PWM++;   //- �������� ��������
            else 
                {
                LED_PWM=0;             //� ����� ����� ���������
                mode=LED_OFF;
                }
        break;
    case    KEY_OFF:                  // ��� ���������� �������
        if (LED_PWM>0) LED_PWM--;     // �������� ����� �������� ����������
          else 
          {
            power_down(); // � �������� �������
           
            mode=LED_ON;
            
          } 
        break;
    case    LED_ON:                    // ����� ��������� �����������
        if (adc_data<(NOMINAL_I-I_SENS)) LED_PWM++;   // ���������� ���
        if (adc_data>(NOMINAL_I+I_SENS)) LED_PWM--;  // � �������� ��������
        if  (LED_PWM>MAX_LED_PWM) LED_PWM=0;  // ���� ��� ���������� �� ����������
        break;
    case    LED_OFF:                  // ����� ����
        if (LED_PWM>0) LED_PWM--;    // �������� ����� ���
        break;
    default :
        error_code=BAD_MODE;
    }   
  
         if (LED_PWM==0)
              {
              TCCR0A_COM0B1 =0; 
               TCCR0A_COM0B0=0;  
              DDRA_DDA7=1;
              PORTA_PORTA7=1;
              }
              else 
              {
                TCCR0A_COM0B1=1;
                TCCR0A_COM0B0=1;            
              DDRA_DDA7=1;      
              }

}



void power_down(void)// �������� ����� ���;
{
        {           
 /*         ADCSRA_ADEN=0; // ���� ADC 
          ADMUX_REFS1=0; // ��������� ���������� ������� ����������
          ADMUX_REFS0=1;
          
          ACSR_ACD=1; // ��������� ����������
       
          // ���� ������ 0
          TCCR0B_CS00=0;
          TCCR0B_CS01=0;
          TCCR0B_CS02=0;
          // ���� ������ 1
          TCCR1B_CS10=0;
          TCCR1B_CS11=0;
          TCCR1B_CS12=0;
*/
         MCUCR_ISC01=0; // The rising edge of INT0 generates an interrupt request.
         MCUCR_ISC00=0;  
         
         GIMSK_INT0=1;    // �������� ���������� �� INT0
  
        // Sleep Mode=
        MCUCR_SM0=0;
        MCUCR_SM1=1;
         MCUCR_SE=1; // Sleep Mode=ON;
        asm ("sleep");
        }

}

void power_up(void)// ������� �� ������ ���
{
      
  // MCUCR_SE=0; // Sleep Mode=OFF;  
   GIMSK_INT0=0;    // ��������� ���������� �� INT0
   
/*

        ADCSRA_ADEN=1; // ��� ADC
        ADMUX_REFS1=1; //��� ���������� ������� ����������
        ADMUX_REFS0=0;    
        ACSR_ACD=0; // �������� ����������
        
          // ��� ������ 0
          TCCR0B_CS00=1;
          TCCR0B_CS01=0;
          TCCR0B_CS02=0;
          // ��� ������ 1
          TCCR1B_CS10=1;
          TCCR1B_CS11=0;
          TCCR1B_CS12=0;
          
   */  
   LED_PWM=0xf0;
    __delay_cycles(32000);
       // LED_PWM=0;
        mode=KEY_ON;
        sleep=0;  
}


/*---------------------------------------------

�������� ����������, ��� ��������� �������.
�������� � 3 �����.
1 - ����� ������������.
2- ������ ������������. �� ����� ��������������
    �������� �� ����������� ������ �������������
    ���������  Analog Comparator Input Capture by Timer/Counter 1: On
    ��������  Input Captur� ������������ ��� �������� �������
3- ����� ����� �����������
    � ����������� �� ������ ���������� ���������� ������� ����� 

--------------------------------------*/


#pragma vector = TIM1_OVF_vect 
__interrupt  void TIM1_OVF_vect_isr(void) // Timer 1 overflow interrupt service routine
{
  
  //PORTB_PORTB1=~PORTB_PORTB1;
  
  
 switch (cap_sens_step) {
        case 1:    // ������� �������
            //TCCR1B=0x01;     //������������ CLK
            PORTA_PORTA3=1;      // PA3 - �����
            DDRA_DDA3=1;     // ������� ����
          TIFR1_ICF1=0;         // ���������� ����  Input Capture

        break;
        case 2 :   // ������ �������
           TIFR1_ICF1=0;         // ���������� ����  Input Capture
          DDRA_DDA3 =0;
          // PORTB_PORTB1=0;    // debug
            ch_AC_EN=1; 
        break;
        
        case 3:   // ������ ���������
          
          if (ch_AC_EN==1) // ���� �� �������� ���������� ������
          {
              ch_AC_EN=0; 
              error_code=NO_INPUT_CAPTURE;
          }
          else   ch_SR_RUN=1;  // ���� ���������� ���������� ����������.

        break;                
          
        default:
            error_code=BAD_CAP_SENS_STEP;
        };
        
   // ��� ��������� ����     
   if  (cap_sens_step<3) cap_sens_step++;
    else cap_sens_step=1;
    
 

}



/*---------------------------------------------
���������� �����������
������� ����� ���������������� ��������� ������, �� ��� ��������...

ch_AC_EN - �������� � 1 �� ����� ������ ������� ������������

--------------------------------------*/
// Analog Comparator interrupt service routine
#pragma vector = ANA_COMP_vect
__interrupt void ANA_COMP_vect_isr(void)
   
{
  // if (ch_AC_EN==0) return; // ���� ������ ���� ��� ����������
 // ch_SR_RUN=1;  // ���� ���������� ���������� ����������� ��������.
  ch_AC_EN=0;              // ���������. ������ �� ��������� �� ���� 2.
}

/*---------------------------------------------*/





/*---------------------------------------------
���������� ����������� ������� 1.
 ��������� ������� ������� ������� �������� �������.

--------------------------------------*/
#pragma vector = TIM1_COMPA_vect
__interrupt  void TIM1_COMPA_vect_isr(void)
{

  //PORTB_PORTB1=1;  // ��� ������

}


/*---------------------------------------------*/



#define ADC_VREF_TYPE 0x80
// ADC interrupt service routine
#pragma vector = ADC_vect
__interrupt  void ADC_vect_isr(void)
{

// Read the AD conversion result
adc_data=ADC;
// Place your code here

}







void deb(void)
{


    
}














void main(void)
{
// Declare your local variables here
unsigned char mask;
unsigned int x;
unsigned char y;
unsigned int sleep_count;

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;


// Port B initialization
// Func3=In Func2=Out Func1=In Func0=In 
// State3=T State2=0 State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

DDRB_DDB1=1;
PORTB_PORTB1=0;

DDRB_DDB2=0;  // KEY - ��� ����
PORTB_PORTB2=1; // � ����� ���

error_code=0;
// Crystal Oscillator division factor: 1
i_sr_cap=0x7FFF;
CLKPR=0x80;
CLKPR=0x00;
WDTCSR=0x00;


// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 7378,000 kHz
// Mode: Fast PWM top=FFh
// OC0A output: Disconnected
// OC0B output:Non-Inverted PWM 
TCCR0A=0x33;
TCCR0B=0x01;  // clock  clkI/O/(No prescaling)
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 7378,000 kHz
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x01;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
TCCR1B_ICES1=1;

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-11: Off
MCUCR=0x00;
GIMSK=0;  
//GIMSK=0x40;
//GIMSK_INT0=1; // ���� ���0
//GIMSK_PCIE0=1;    // �������� ���������� �� ����� 0.


 
GIFR=0x40;
//GIFR_PCIF0=1; // � ��� ����� ���� ���� �������
PCMSK1=0x00;
PCMSK0=0x00;
//PCMSK0_PCINT0=1; // ���������� ��� PCINT0

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0_TOIE0=1;


// Timer/Counter 1 Interrupt(s) initialization
TIMSK1_TOIE1=1;
TIMSK1_OCIE1A=1;



// Universal Serial Interface initialization
// Mode: Disabled
// Clock source: Register & Counter=no clk.
// USI Counter Overflow Interrupt: Off
USICR=0x00;

// Analog Comparator initialization
// Analog Comparator: On
// Digital input buffers on AIN0: Off, AIN1: Off
DIDR0=0x03;
// Interrupt on RISE Output Edge
// Analog Comparator Input Capture by Timer/Counter 1: On
ACSR=0x0F;
ADCSRB=0x00;

ACSR_ACIC=1;

// ADC initialization
// ADC Clock frequency: 922,250 kHz
// ADC Voltage Reference: 1.1V, AREF discon.
// ADC Bipolar Input Mode: Off
// ADC Auto Trigger Source: None
// Digital input buffers on ADC0: On, ADC1: Off, ADC2: Off, ADC3: Off
// ADC4: Off, ADC5: Off, ADC6: Off, ADC7: Off
DIDR0=0xFF;
ADMUX=0x80;//ADC_VREF_TYPE & 0xff;
ADCSRA=0x8B;
ADCSRB&=0x70;
ADCSRB|=0x10;

// Global enable interrupts
SREG_I=1;

//MCUCR_PUD=1; //all pull up desable

mode=LED_ON;
i_sr_cap=0;

while (1)
{
 ADCSRA_ADSC=1; // ����� ADC
   
    
  
 
 
   DDRA_DDA7=1; 
 
//DDRB_DDB1=1;  

//PORTB_PORTB1=sleep;

if ((ch_SR_RUN==1) & (sleep==0))
{
  x=ICR1;  // ���������� ���� ����������� ��������
    if (x<i_sr_cap) i_sr_cap-=(i_sr_cap-x)/32;
    else i_sr_cap+=(x-i_sr_cap)/32;


  
  if (i_sr_cap>(NOMINAL_CAP+CAP_SENS)) mode=LED_ON;
  if (i_sr_cap<(NOMINAL_CAP-CAP_SENS)) mode=LED_OFF;
  ch_SR_RUN=0;    
    
   //OCR1A=i_sr_cap; 
 // if (i_sr_cap>1000) PORTB_PORTB1=1;
   // else PORTB_PORTB1=0;

}


PORTB_PORTB0=1;   // ������� ���������� ��� �����������.
  DDRB_DDB0=1;   

  
  
  

// ���������� ������������ � ��������� ����� 
if (delay_count>LED_SPEED)
    {

      
  //    GIMSK=0; 

     //   GIMSK_INT0=0;

        
      delay_count=0;
      led_driver();
      //PORTB_PORTB1=~PORTB_PORTB1;
      //OCR1A=adc_data; 
    }    

// ������� ������� ��� �������� � ������ ����� ( ���� ����� �������� �� ������)
if (PINB_PINB2==0) sleep_count++;
  else sleep_count=0;
  

if (sleep==1) sleep_count=0;
  
if (sleep_count>SLEEP_DELAY)
  {
        LED_PWM=MAX_LED_PWM;
        mode=KEY_OFF;
       sleep=1;

  }
  

}
}
