
// для измерения температуры включаем внутренний источникопорного напряжения и 
// Selecting the ADC8 channel by writing the MUX5:0 bits in ADMUX
//register to “100010” enables the temperature sensor.
//итого 10100010
#define ADC_temp_set      0xA2

// Для измерения тока ADC7 (PA7) 000111 и Internal 1.1V voltage reference
//итого 10000111
#define ADC_curent_set    0x87

#define TEMP_OFFSET       26 //для перевода в градусы
#define TEMP_ACCURACY       128 // количество отсчетов для вычесления скользящего среднего

#define KEY_TIME_OUT      50 // зазор для защиты от дребезга контактов максимум (0xFF-1)
#define KEY_OFF            0
#define KEY_ON             1

void key0_event (void);
void key1_event (void);
void temp_chek (void);

void led0_set (unsigned char on_off);
void led1_set (unsigned char on_off);

float i_sr_temp_curent;


/* Port A Data Register - PORTA */
#define    PA4      4
#define    PA3      3
#define    PA2      2
#define    PA1      1
#define    PA0      0