/*
���������� ��� ������ � �����������������
� ���������� ������� ��� ������ � �����������������
�������� ���������������� (MBI5168) ���������� � SPI-�.
clk � USCK. SDI � D0. OE � PA0. LE � PA1
*/
//#include "iotiny24.h"

#define SPI_OE_DDR     DDRA_DDA0
#define SPI_LE_DDR     DDRA_DDA1
#define SPI_CLK_DDR    DDRA_DDA4
#define SPI_SDI_DDR    DDRA_DDA5

#define SPI_OE        PORTA_PORTA0
#define SPI_LE        PORTA_PORTA1
#define SPI_CLK   PORTA_PORTA4
#define SPI_SDI  PORTA_PORTA5



#define a 2       // ��� ������� �������� �����, ��������������� ������,
#define b 1       // ����������� � �������, ������ ������ "�����" ����
#define c 64      // �����, � �������� ��������� ������� ���������� �
#define d 32      // ����������� ������� ���������. ��� ����, ����� �������
#define e 16      // �����-���� ����� �� ���������, ����� ��������� � ����
#define f 4       // ����� 255 ����� ����� ��������������� ��������� ��������.
#define g 8       // ��� ����� ��������� ������� ��������� ����������� �� �����������.
#define DP 128    // �������� ��� �����, ���� ��������� ������� ����� "��"

unsigned char DigNumber = 0;
unsigned char Dig[10]; // ������, � ������� �������� �����, ������� �����
// ������� ����� ���� �� ���������, ����� �� ������� �����, ������ ������
// �������� �������. ����� ������� ������ �� ��������.

//void OE_set (unsigned char on_off);
//void LE_set (unsigned char on_off);
void SPI_DATA_TO_LED (unsigned char data1,unsigned char data2);
void Dig_init(void);
inline void Display_off (void);
inline void Display_on (void);

//#include "7_sigmentnik.cpp"