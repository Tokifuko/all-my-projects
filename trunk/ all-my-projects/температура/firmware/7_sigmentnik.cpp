
#include "7_sigmentnik.h"
#include <stdlib.h>

void SPI_init()
{ //выходы как выходы
  SPI_OE_DDR=1; // OE вход драйвера
  SPI_LE_DDR=1; // LE вход драйвера
  SPI_CLK_DDR=1;
  SPI_SDI_DDR=1;
  // Universal Serial Interface initialization
  // Mode: Three Wire (SPI)
  // Clock source: Reg.=ext. pos. edge, Cnt.=USITC
  // USI Counter Overflow Interrupt: Off
  USICR=0x1A;
  Dig_init();
}

void Dig_init()
{
  Dig[0] = (a+b+c+d+e+f);   // Если индикатор с общим анодом,
  Dig[1] = (b+c);           // нужно сумму макросов отнять от
  Dig[2] =  (a+b+g+e+d);     // 255. Если с общим катодом, то
  Dig[3] =  (a+b+g+c+d);     // отнимать не нужно.
  Dig[4] =  (f+g+b+c);       // Имена макросов соответствуют
  Dig[5] =  (a+f+g+c+d);     // именам сегментов индикатора
  Dig[6] =  (a+f+g+c+d+e);
  Dig[7] =  (a+b+c);
  Dig[8] =  (a+b+c+d+e+f+g);
  Dig[9] = (a+b+c+d+f+g);  

}


void Display (unsigned char Number)
{
  div_t x;
  x=div(Number,100);//отсекаем что больше 100
  x=div(x.rem,10);
  SPI_DATA_TO_LED(Dig[x.quot],Dig[x.rem]);
}

inline void Display_on (void)
{
  SPI_OE_DDR=1; // OE вход драйвера как выход
}
inline void Display_off (void)
{
  SPI_OE_DDR=0; // OE вход драйвера в 3-e состояние
}


void SPI_DATA_TO_LED (unsigned char data1,unsigned char data2)
{
  char i;
  SPI_OE=1;
  USIDR=data1;
  i=0;
  while ((i++)<16)USICR_USITC=1;
  USIDR=data2;
  i=0;
  while ((i++)<16)USICR_USITC=1;  

  SPI_LE=1;
  SPI_LE=0;
  SPI_OE=0;
}

