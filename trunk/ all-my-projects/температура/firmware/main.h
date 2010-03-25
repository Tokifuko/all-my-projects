
// дл€ измерени€ температуры включаем внутренний источникопорного напр€жени€ и 
// Selecting the ADC8 channel by writing the MUX5:0 bits in ADMUX
//register to У100010Ф enables the temperature sensor.
//итого 10100010
#define ADC_temp_set      0xA2

// ƒл€ измерени€ тока ADC7 (PA7) 000111 и Internal 1.1V voltage reference
//итого 10000111

#define ADC_curent_set    0x87

void key0_event (void);
void key1_event (void);

void led0_set (unsigned char on_off);
void led1_set (unsigned char on_off);