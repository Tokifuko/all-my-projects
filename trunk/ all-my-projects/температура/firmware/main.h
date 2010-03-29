

#define TEMP_OFFSET       26 //��� �������� � �������
#define TEMP_ACCURACY       128 // ���������� �������� ��� ���������� ����������� ��������

#define KEY_TIME_OUT      50 // ����� ��� ������ �� �������� ��������� �������� (0xFF-1)
#define KEY_OFF            0
#define KEY_ON             1

#define FAN_SPEED_OFF         0x00
#define FAN_SPEED_SLOW         0x10
#define FAN_SPEED_MEDI        0xA0
#define FAN_SPEED_FAST        0xFF
#define FAN_SPEED_CONTROL     OCR0B
                        // � ��� 4 ������������� ������ 
#define FAN_MODE_OFFSET       1  // ����� ��� ������������ �������
#define TEMP_OFF              (-5) 
#define TEMP_SLOW             (-2) 
#define TEMP_MEDI             0



#define EEPROM_ADDR         0x0001  //����� ��������� ������������� �������� �����������

#define IDLE_MODE             1      // ����� ������������ ����������
#define SETUP_MODE            2     // ��������� ������, ������ ������������� ��������
#define SHOW_MODE             3     // ��������� ���������� �����������
#define SETUP_MODE_TIMEOUT          10
#define SHOW_MODE_TIMEOUT           120




void key0_event (void);
void key1_event (void);
void temp_chek (void);

void led0_set (unsigned char on_off);
void led1_set (unsigned char on_off);

float f_sr_temp_curent;
unsigned char ch_temp;
unsigned int delay_counter=0;
unsigned char triger;
unsigned char curent_mode=SHOW_MODE;
unsigned char sec_counter=0;
unsigned char set_temp;

