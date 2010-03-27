
// дл€ измерени€ температуры включаем внутренний источникопорного напр€жени€ и 
// Selecting the ADC8 channel by writing the MUX5:0 bits in ADMUX
//register to У100010Ф enables the temperature sensor.
//итого 10100010
#define ADC_temp_set      0xA2

// ƒл€ измерени€ тока ADC7 (PA7) 000111 и Internal 1.1V voltage reference
//итого 10000111

#define ADC_curent_set    0x87
#define TEMP_OFFSET       26 //дл€ перевода в градусы
#define TEMP_ARRAY       16

void key0_event (void);
void key1_event (void);
void temp_chek (void);

void led0_set (unsigned char on_off);
void led1_set (unsigned char on_off);
unsigned char temp[TEMP_ARRAY];
unsigned char temp_counter;
unsigned char temp_curent;


/* Port A Data Register - PORTA */
#define    PA4      4
#define    PA3      3
#define    PA2      2
#define    PA1      1
#define    PA0      0