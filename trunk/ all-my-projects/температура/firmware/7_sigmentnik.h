/*
переменные для работы с семисигментниками
и объявления функций для работы с семисигментниками
драйверы семесигментников (MBI5168) подключены к SPI-ю.
clk к USCK. SDI к D0. OE к PA0. LE к PA1
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



#define a 2       // Эти макросы содержат числа, соответствующие двойке,
#define b 1       // возведенной в степень, равной номеру "ножки" того
#define c 64      // порта, к которому подключен сегмент индикатора с
#define d 32      // одноименным макросу названием. Для того, чтобы вывести
#define e 16      // какую-либо цифру на индикатор, нужно отправить в порт
#define f 4       // число 255 минус сумму соответствующих сегментам макросов.
#define g 8       // Эти числа позволяют сделать программу независимой от подключения.
#define DP 128    // Измените эти числа, если индикатор выводит букву "зю"

unsigned char DigNumber = 0;
unsigned char Dig[10]; // Массив, в котором хранятся числа, которые нужно
// вывести через порт на индикатор, чтобы он показал цифру, равную номеру
// элемента массива. Числа зависят только от макросов.

//void OE_set (unsigned char on_off);
//void LE_set (unsigned char on_off);
void SPI_DATA_TO_LED (unsigned char data1,unsigned char data2);
void Dig_init(void);
inline void Display_off (void);
inline void Display_on (void);

//#include "7_sigmentnik.cpp"