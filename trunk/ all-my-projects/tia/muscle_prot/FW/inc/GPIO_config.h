#ifndef SIMPLE_LED_H
#define SIMPLE_LED_H
#include "stm32f10x_conf.h"
/* светодиоды, понятно */
#define LED_2_PORT             GPIOC
#define LED_2_CLK              RCC_APB2Periph_GPIOC
#define LED_2_PIN              GPIO_Pin_6
void Led2On	(void);
void Led2Off (void);

//Green led on the discovery board
#define G_LED_DISC_PORT             GPIOC
#define G_LED_DISC_CLK              RCC_APB2Periph_GPIOC
#define G_LED_DISC_PIN              GPIO_Pin_9
void GLedDiscOn	(void);
void GLedDiscOff (void);
//Blue led on the discovery board
#define B_LED_DISC_PORT             GPIOC
#define B_LED_DISC_CLK              RCC_APB2Periph_GPIOC
#define B_LED_DISC_PIN              GPIO_Pin_8
void BLedDiscOn	(void);
void BLedDiscOff (void);

/* User button on the discovery board*/
#define USER_BUTTON_PORT          GPIOA
#define USER_BUTTON_CLK           RCC_APB2Periph_GPIOA
#define USER_BUTTON_PIN           GPIO_Pin_0
bool UserButtonPressed(void);


#endif /* SIMPLE_LED_H */
