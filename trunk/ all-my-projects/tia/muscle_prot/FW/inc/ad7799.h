/*
 * ad7799.h
 *
 *  Created on: 20 дек. 2013 г.
 *      Author: Stefan
 */

#ifndef AD7799_H_
#define AD7799_H_



#include "stm32f10x_conf.h"
#include "stm32f10x.h"

#define AD7799_COM_CONFIG 			{0x10,0x07,0x30,0x00}  //g=128
//#define AD7799_COM_CONFIG 			{0x10,0x06,0x30,0x00}		// g=64
//#define AD7799_COM_MODE_PSW_ON  	{0x08,0x00,0x01,0x00}  // f=420Hz
//#define AD7799_COM_MODE_PSW_OFF  	{0x08,0x10,0x01,0x00}	// f=420Hz
//#define AD7799_COM_MODE_PSW_ON  	{0x08,0x00,0x0a,0x00}	// f=16.7Hz
//#define AD7799_COM_MODE_PSW_OFF  	{0x08,0x10,0x0a,0x00}	// f=16.7Hz
#define AD7799_COM_MODE_PSW_ON  	{0x08,0x10,0x04,0x00}	// f=62Hz
#define AD7799_COM_MODE_PSW_OFF  	{0x08,0x00,0x04,0x00}	// f=62Hz
#define AD7799_COM_MODE_INT_CALIBR 	{0x08,0x80,0x04,0x00}	// f=62Hz

#define AD7799_COM_GET_STATUS  		{0x40,0x00,0x00,0x00}
#define AD7799_COM_GET_DATA  		{0x58,0x00,0x00,0x00}
#define AD7799_COM_RESET  			{0xff,0xff,0xff,0xff}

#define SPI_MASTER                   SPI1
#define SPI_MASTER_CLK               RCC_APB2Periph_SPI1
#define SPI_MASTER_GPIO              GPIOB
#define SPI_MASTER_GPIO_CLK          RCC_APB2Periph_GPIOB
#define SPI_MASTER_PIN_SCK           GPIO_Pin_3
#define SPI_MASTER_PIN_MISO          GPIO_Pin_4
#define SPI_MASTER_PIN_MOSI          GPIO_Pin_5
#define SPI_MASTER_CS_GPIO           GPIOC
#define SPI_MASTER_CS_GPIO_CLK       RCC_APB2Periph_GPIOC
#define SPI_MASTER_PIN_CS            GPIO_Pin_12

#define SPI_MASTER_DMA               DMA1
#define SPI_MASTER_DMA_CLK           RCC_AHBPeriph_DMA1
#define SPI_MASTER_Rx_DMA_Channel    DMA1_Channel2
#define SPI_MASTER_Rx_DMA_FLAG       DMA1_FLAG_TC2
#define SPI_MASTER_Tx_DMA_Channel    DMA1_Channel3
#define SPI_MASTER_Tx_DMA_FLAG        DMA1_FLAG_TC3
#define SPI_MASTER_DR_Base           (SPI1_BASE + 0x0000000C) //0x4001300C

#define BufferSize         5
#define CRCPolynomial      7

typedef void(*ftVoid_Void)(uint32_t);

class AD7799_Class {
private:
	uint8_t cChar;
	bool bLedPswOn;
    DMA_InitTypeDef  DMA_InitStructure_TX;
    DMA_InitTypeDef  DMA_InitStructure_RX;
    uint8_t SPI_MASTER_Buffer_Rx[BufferSize];
    uint8_t SPI_MASTER_Buffer_Tx[BufferSize];
    uint8_t AD7799_state;
    bool bChangeModeFlag;
    bool bChangeConfigFlag;
    bool bCalibrationNeed;


public:
    ftVoid_Void Callback;
    void Init(void);
    void Task (void);
    void StartTxRx(uint8_t chDataSize);
    void PswPinOn(void);
    void PswPinOff(void);
    void StartZeroCalibration(void);

};

#endif /* AD7799_H_ */
