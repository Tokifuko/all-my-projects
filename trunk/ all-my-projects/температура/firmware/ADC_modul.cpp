#include "ADC_modul.h"


void ADC_init (void)
{
// дл€ измерени€ температуры включаем внутренний источникопорного напр€жени€ и 
// Selecting the ADC8 channel by writing the MUX5:0 bits in ADMUX
//register to У100010Ф enables the temperature sensor.
//итого 10100010
  ADMUX=0xA2;

  ADCSRA_ADEN=1;//ADC Enable
  ADCSRA_ADATE=0; // ADC Auto Trigger Enable
  
  ADCSRA_ADPS2=1; //ADC Prescaler Select Bits
  ADCSRA_ADPS1=1; // включаем делитель на максимум
  ADCSRA_ADPS0=1;
  
  ADCSRB_BIN=0; //Bipolar Input Mode
  ADCSRB_ACME=0;//Analog Comparator Multiplexer Enable
  ADCSRB_ADLAR=0; //ADC Left Adjust Result
  
  ADCSRB_ADTS2=0;//ADC Auto Trigger Source Selections
  ADCSRB_ADTS1=0; // стартуем вручную
  ADCSRB_ADTS0=0; // выбран режим Free Running mode
  DIDR0=0x00;  //Digital input buffers on
  DIDR0_ADC7D=1; //выключаем буфер на входе ADC7
}

unsigned int read_adc(void)
{ 
 unsigned int i;
 delay_us(5);
// Delay needed for the stabilization of the ADC input voltage
//// Start the AD conversion
 //delay_ms(100);
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
i=ADCL;
i+=(ADCH << 8);
 
return i;
}

