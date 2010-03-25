
// ��� ��������� ����������� �������� ���������� ���������������� ���������� � 
// Selecting the ADC8 channel by writing the MUX5:0 bits in ADMUX
//register to �100010� enables the temperature sensor.
//����� 10100010
#define ADC_temp_set      0xA2

// ��� ��������� ���� ADC7 (PA7) 000111 � Internal 1.1V voltage reference
//����� 10000111

#define ADC_curent_set    0x87

void key0_event (void);
void key1_event (void);

void led0_set (unsigned char on_off);
void led1_set (unsigned char on_off);