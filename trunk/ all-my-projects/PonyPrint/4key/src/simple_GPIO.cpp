#include "GPIO_config.h"

void Led2On	(void)			{GPIO_ResetBits(LED_2_PORT,LED_2_PIN);}
void Led2Off (void)			{GPIO_SetBits(LED_2_PORT,LED_2_PIN);}
void GLedDiscOff	(void)			{GPIO_ResetBits(G_LED_DISC_PORT,G_LED_DISC_PIN);}
void GLedDiscOn (void)			{GPIO_SetBits(G_LED_DISC_PORT,G_LED_DISC_PIN);}
void BLedDiscOff	(void)			{GPIO_ResetBits(B_LED_DISC_PORT,B_LED_DISC_PIN);}
void BLedDiscOn (void)			{GPIO_SetBits(B_LED_DISC_PORT,B_LED_DISC_PIN);}

bool UserButtonPressed(void) { return (GPIO_ReadInputDataBit(USER_BUTTON_PORT, USER_BUTTON_PIN) == Bit_RESET); }
bool Button_A_Pressed(void) { return (GPIO_ReadInputDataBit(BUTTON_A_PORT, BUTTON_A_PIN) == Bit_RESET); }
bool Button_B_Pressed(void) { return (GPIO_ReadInputDataBit(BUTTON_B_PORT, BUTTON_B_PIN) == Bit_RESET); }
bool Button_C_Pressed(void) { return (GPIO_ReadInputDataBit(BUTTON_C_PORT, BUTTON_C_PIN) == Bit_RESET); }
bool Button_D_Pressed(void) { return (GPIO_ReadInputDataBit(BUTTON_D_PORT, BUTTON_D_PIN) == Bit_RESET); }

