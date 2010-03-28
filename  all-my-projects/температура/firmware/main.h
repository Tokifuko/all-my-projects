
// ��� ��������� ����������� �������� ���������� ���������������� ���������� � 
// Selecting the ADC8 channel by writing the MUX5:0 bits in ADMUX
//register to �100010� enables the temperature sensor.
//����� 10100010
#define ADC_temp_set      0xA2

// ��� ��������� ���� ADC7 (PA7) 000111 � Internal 1.1V voltage reference
//����� 10000111
#define ADC_curent_set    0x87

#define TEMP_OFFSET       26 //��� �������� � �������
#define TEMP_ACCURACY       128 // ���������� �������� ��� ���������� ����������� ��������

#define KEY_TIME_OUT      50 // ����� ��� ������ �� �������� ��������� �������� (0xFF-1)
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