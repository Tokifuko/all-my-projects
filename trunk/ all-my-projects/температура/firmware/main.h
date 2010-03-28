

#define TEMP_OFFSET       26 //для перевода в градусы
#define TEMP_ACCURACY       128 // количество отсчетов для вычесления скользящего среднего

#define KEY_TIME_OUT      50 // зазор для защиты от дребезга контактов максимум (0xFF-1)
#define KEY_OFF            0
#define KEY_ON             1

#define FAN_SPEED_LOW         0x10
#define FAN_SPEED_MEDI        0xA0
#define FAN_SPEED_FAST        0xFF
#define FAN_SPEED_CONTROL     OCR0B



#define EEPROM_ADDR         0x0001  //здесь храниться переменная  universal_counter






void key0_event (void);
void key1_event (void);
void temp_chek (void);

void led0_set (unsigned char on_off);
void led1_set (unsigned char on_off);

float i_sr_temp_curent;
unsigned int delay_counter=0;
unsigned char triger;
unsigned char universal_counter;

