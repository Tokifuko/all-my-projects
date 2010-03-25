/****************************************************************************
 **             - iotiny24.h -
 **
 **     This file declares the internal register addresses for ATtiny24.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright 2005 IAR Systems AB. All rights reserved.
 **
 **     File version: $Revision: 8192 $
 **
 ***************************************************************************/

#ifdef  __IAR_SYSTEMS_ICC__
#ifndef _SYSTEM_BUILD
#pragma system_include
#endif
#endif

#include "iomacro.h"

#if TID_GUARD(0)
#error This file should only be compiled with iccavr or aavr with processor option -v0
#endif /* TID_GUARD(0) */

#ifndef __IOTINY24_H


/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */

/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/

/* NB! vectors are specified as byte addresses */

#define RESET_vect              (0x00) /* External Pin, Power-on Reset, Brown-out Reset,
                                         Watchdog Reset */
#define INT0_vect               (0x02) /* External Interrupt Request 0 */
#define PCINT0_vect             (0x04) /* Pin Change Interrupt Request 0 */
#define PCINT1_vect             (0x06) /* Pin Change Interrupt Request 1 */
#define WDT_vect                (0x08) /* Watchdog Time-out */
#define TIM1_CAPT_vect          (0x0A) /* Timer/Counter1 Capture Event */
#define TIM1_COMPA_vect         (0x0C) /* Timer/Counter1 Compare Match A */
#define TIM1_COMPB_vect         (0x0E) /* Timer/Counter1 Compare Match B */
#define TIM1_OVF_vect           (0x10) /* Timer/Counter0 Overflow */
#define TIM0_COMPA_vect         (0x12) /* Timer/Counter0 Compare Match A */
#define TIM0_COMPB_vect         (0x14) /* Timer/Counter0 Compare Match B */
#define TIM0_OVF_vect           (0x16) /* Timer/Counter0 Overflow */
#define ANA_COMP_vect           (0x18) /* Analog Comparator */
#define ADC_vect                (0x1A) /* ADC Conversion Complete */
#define EE_RDY_vect             (0x1C) /* EEPROM Ready */
#define USI_START_vect          (0x1E) /* USI START */
#define USI_OVF_vect            (0x20) /* USI Overflow */

#ifdef __IAR_SYSTEMS_ASM__   
#ifndef ENABLE_BIT_DEFINITIONS
#define  ENABLE_BIT_DEFINITIONS
#endif /* ENABLE_BIT_DEFINITIONS */
#include "bitdefinitions/iotiny24.inc"
#endif /* __IAR_SYSTEMS_ASM__ */

#endif /* __IOTINY24_H (define part) */


/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */
#if !defined(__IOTINY24_H) || defined(__IAR_SYSTEMS_ASM__)
#define __IOTINY24_H

#pragma language=save
#pragma language=extended

/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/

/****************************************************************************
 * An example showing the SFR_B() macro call, 
 * the expanded result and usage of this result:
 *
 * SFR_B_R(0x1F,   AVR) Expands to:
 * __io union {
 *             unsigned char AVR;                 // The sfrb as 1 byte
 *             struct {                           // The sfrb as 8 bits
 *                     unsigned char AVR_Bit0:1,
 *                                   AVR_Bit1:1,
 *                                   AVR_Bit2:1,
 *                                   AVR_Bit3:1,
 *                                   AVR_Bit4:1,
 *                                   AVR_Bit5:1,
 *                                   AVR_Bit6:1,
 *                                   AVR_Bit7:1;
 *                    };
 *            } @ 0x1F;
 * Examples of how to use the expanded result:
 * AVR |= (1<<5);
 * or like this:
 * AVR_Bit5 = 1;
 *
 *
 *
 * An example showing the SFR_B_N() macro call, 
 * the expanded result and usage of this result:
 * SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
 *  Expands to:
 *  __io union { 
 *              unsigned char TCCR2; 
 *              struct { 
 *                      unsigned char TCCR2_Bit0:1, 
 *                                    TCCR2_Bit1:1, 
 *                                    TCCR2_Bit2:1, 
 *                                    TCCR2_Bit3:1, 
 *                                    TCCR2_Bit4:1, 
 *                                    TCCR2_Bit5:1, 
 *                                    TCCR2_Bit6:1, 
 *                                    TCCR2_Bit7:1; 
 *                     }; 
 *              struct { 
 *                      unsigned char TCCR2_CS20:1, 
 *                                    TCCR2_CS21:1, 
 *                                    TCCR2_CS22:1, 
 *                                    TCCR2_WGM21:1, 
 *                                    TCCR2_COM20:1, 
 *                                    TCCR2_COM21:1, 
 *                                    TCCR2_WGM20:1, 
 *                                    TCCR2_FOC2:1; 
 *                     }; 
 *             } @ 0x25;
 * Examples of how to use the expanded result:
 * TCCR2 |= (1<<5); 
 * or if ENABLE_BIT_DEFINITIONS is defined   
 * TCCR2 |= (1<<COM21);
 * or like this:
 * TCCR2_Bit5 = 1;
 * or like this:
 * TCCR2_COM21 = 1;
 ***************************************************************************/

SFR_B_N(0x3F, SREG, I, T, H, S, V, N, Z, C)
SFR_W_N(0x3D, SP, Dummy15, Dummy14, Dummy13, Dummy12, Dummy11, Dummy10, SP9, SP8, SP7, SP6, SP5, SP4, SP3, SP2, SP1, SP0)
SFR_B_R(0x3C, OCR0B)
SFR_B_N(0x3B, GIMSK, Dummy7, INT0, PCIE1, PCIE0, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0x3A, GIFR, Dummy7, INTF0, PCIF1, PCIF0, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0x39, TIMSK0, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCIE0B, OCIE0A, TOIE0)
SFR_B_N(0x38, TIFR0, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCF0B, OCF0A, TOV0)
SFR_B_N(0x37, SPMCSR, Dummy7, Dummy6, Dummy5, CTPB, RFLB, PGWRT, PGERS, SPMEN)
SFR_B_R(0x36, OCR0A)
SFR_B_N(0x35, MCUCR, Dummy7, PUD, SE, SM1, SM0, Dummy2, ISC01, ISC00)
SFR_B_N(0x34, MCUSR, Dummy7, Dummy6, Dummy5, Dummy4, WDRF, BORF, EXTRF, PORF)
SFR_B_N(0x33, TCCR0B, FOC0A, FOC0B, Dummy5, Dummy4, WGM02, CS02, CS01, CS00)
SFR_B_R(0x32, TCNT0)
SFR_B_N(0x31, OSCCAL, CAL7, CAL6, CAL5, CAL4, CAL3, CAL2, CAL1, CAL0)
SFR_B_N(0x30, TCCR0A, COM0A1, COM0A0, COM0B1, COM0B0, Dummy3, Dummy2, WGM01, WGM00)
SFR_B_N(0x2F, TCCR1A, COM1A1, COM1A0, COM1B1, COM1B0, Dummy3, Dummy2, WGM11, WGM10)
SFR_B_N(0x2E, TCCR1B, ICNC1, ICES1, Dummy5, WGM13, WGM12, CS12, CS11, CS10)
SFR_W_R(0x2C, TCNT1)
SFR_W_R(0x2A, OCR1A)
SFR_W_R(0x28, OCR1B)
SFR_B_R(0x27, DWDR)
SFR_B_N(0x26, CLKPR, CLKPCE, Dummy6, Dummy5, Dummy4, CLKPS3, CLKPS2, CLKPS1, CLKPS0)
SFR_W_R(0x24, ICR1)
SFR_B_N(0x23, GTCCR, TSM, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, PSR10)
SFR_B_N(0x22, TCCR1C, FOC1A, FOC1B, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0x21, WDTCSR, WDIF, WDIE, WDP3, WDCE, WDE, WDP2, WDP1, WDP0)
SFR_B_N(0x20, PCMSK1, Dummy7, Dummy6, Dummy5, Dummy4, PCINT11, PCINT10, PCINT9, PCINT8)
SFR_W_N(0x1E, EEAR, Dummy15, Dummy14, Dummy13, Dummy12, Dummy11, Dummy10, Dummy9, EEAR8, EEAR7, EEAR6, EEAR5, EEAR4, EEAR3, EEAR2, EEAR1, EEAR0)
SFR_B_R(0x1D, EEDR)
SFR_B_N(0x1C, EECR, Dummy7, Dummy6, EEPM1, EEPM0, EERIE, EEMWE, EEWE, EERE)
SFR_B_N(0x1B, PORTA, PORTA7, PORTA6, PORTA5, PORTA4, PORTA3, PORTA2, PORTA1, PORTA0)
SFR_B_N(0x1A, DDRA, DDA7, DDA6, DDA5, DDA4, DDA3, DDA2, DDA1, DDA0)
SFR_B_N(0x19, PINA, PINA7, PINA6, PINA5, PINA4, PINA3, PINA2, PINA1, PINA0)
SFR_B_N(0x18, PORTB, Dummy7, Dummy6, Dummy5, Dummy4, PORTB3, PORTB2, PORTB1, PORTB0)
SFR_B_N(0x17, DDRB, Dummy7, Dummy6, Dummy5, Dummy4, DDB3, DDB2, DDB1, DDB0)
SFR_B_N(0x16, PINB, Dummy7, Dummy6, Dummy5, Dummy4, PINB3, PINB2, PINB1, PINB0)
SFR_B_R(0x15, GPIOR2)
SFR_B_R(0x14, GPIOR1)
SFR_B_R(0x13, GPIOR0)
SFR_B_N(0x12, PCMSK0, PCINT7, PCINT6, PCINT5, PCINT4, PCINT3, PCINT2, PCINT1, PCINT0)
SFR_B_R(0x10, USIBR)
SFR_B_R(0x0F, USIDR)
SFR_B_N(0x0E, USISR, USISIF, USIOIF, USIPF, USIDC, USICNT3, USICNT2, USICNT1, USICNT0)
SFR_B_N(0x0D, USICR, USISIE, USIOIE, USIWM1, USIWM0, USICS1, USICS0, USICLK, USITC)
SFR_B_N(0x0C, TIMSK1, Dummy7, Dummy6, ICIE1, Dummy4, Dummy3, OCIE1B, OCIE1A, TOIE1)
SFR_B_N(0x0B, TIFR1, Dummy7, Dummy6, ICF1, Dummy4, Dummy3, OCF1B, OCF1A, TOV1)
SFR_B_N(0x08, ACSR, ACD, ACBG, ACO, ACI, ACIE, ACIC, ACIS1, ACIS0)
SFR_B_N(0x07, ADMUX, REFS1, REFS0, MUX5, MUX4, MUX3, MUX2, MUX1, MUX0)
SFR_B_N(0x06, ADCSRA, ADEN, ADSC, ADATE, ADIF, ADIE, ADPS2, ADPS1, ADPS0)
SFR_W_R(0x04, ADC)
SFR_B_N(0x03, ADCSRB, BIN, ACME, Dummy5, ADLAR, Dummy3, ADTS2, ADTS1, ADTS0)
SFR_B_N(0x01, DIDR0, ADC7D, ADC6D, ADC5D, ADC4D, ADC3D, ADC2D, ADC1D, ADC0D)
SFR_B_N(0x00, PRR, Dummy7, Dummy6, Dummy5, Dummy4, PRTIM1, PRTIM0, PRUSI, PRADC)

#pragma language=restore

#ifndef __IAR_SYSTEMS_ASM__
#include "bitdefinitions/iotiny24.inc"
#endif

#endif /* __IOTINY24_H (SFR part) */
