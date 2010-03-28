
#include "iotiny24.h"
unsigned char EEPROM_read(unsigned int ucAddress)
{
/* Wait for completion of previous write */
while(EECR_EEPE)
;
/* Set up address register */
EEAR = ucAddress;
/* Start eeprom read by writing EERE */
EECR_EERE=1;
/* Return data from data register */
return EEDR; 
}

void EEPROM_write(unsigned int ucAddress, unsigned char ucData)
{
/* Wait for completion of previous write */
while(EECR_EEPE)
;
/* Set Programming mode */
//EECR = (0<<EEPM1)|(0<<EEPM0)
EECR_EEPM0=0;EECR_EEPM1=0;
/* Set up address and data registers */
EEAR = ucAddress;
EEDR = ucData;
/* Write logical one to EEMPE */
EECR_EEMPE=1;
/* Start eeprom write by setting EEPE */
EECR_EEPE=1;
}