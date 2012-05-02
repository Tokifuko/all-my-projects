/*управление двигателем и измерение силы тока */

#ifndef MOTOR_CLASS_H
#define MOTOR_CLASS_H

#include "stm32f10x_conf.h"


#define MOTOR_A1_PIN  		GPIO_Pin_12
#define MOTOR_A1_GPIO     	GPIOB
#define MOTOR_A1_GPIO_CLK 	RCC_APB2Periph_GPIOB

#define MOTOR_A2_PIN  		GPIO_Pin_13
#define MOTOR_A2_GPIO     	GPIOB
#define MOTOR_A2_GPIO_CLK 	RCC_APB2Periph_GPIOB

#define MOTOR_B1_PIN  		GPIO_Pin_14
#define MOTOR_B1_GPIO     	GPIOB
#define MOTOR_B1_GPIO_CLK 	RCC_APB2Periph_GPIOB

#define MOTOR_B2_PIN  		GPIO_Pin_15
#define MOTOR_B2_GPIO     	GPIOB
#define MOTOR_B2_GPIO_CLK 	RCC_APB2Periph_GPIOB

#define MOTOR_STOP			1
#define MOTOR_UPWARD		2
#define MOTOR_DOWNWARD		3

#define SWITCH_DELAY		20 //ms

class MotorClass {
private:
	uint32_t iTimeoutDelay;
	uint8_t chState;
	uint16_t  iCurrentConsumption;
public:
	void Init(void);
	void Task (void);
	uint16_t  GetCurrentConsumption(void){ return iCurrentConsumption; };
	uint8_t  GetMotorState(void){ return chState; };
	void Stop(void);
	void Upward (void);
	void Downward (void);
    // ~MotorClass(void); // деструктор
};

#endif /* MOTOR_CLASS_H */
