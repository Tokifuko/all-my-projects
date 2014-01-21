/*
 * ms5803_spi.h
 *
 *  Created on: 20 џэт. 2014 у.
 *      Author: Stefan
 */

#ifndef MS5803_SPI_H_
#define MS5803_SPI_H_

#include "stm32f10x_conf.h"
#include "stm32f10x.h"

#define SPI_MASTER                   SPI2
#define SPI_MASTER_CLK               RCC_APB1Periph_SPI2
#define SPI_MASTER_GPIO              GPIOB
#define SPI_MASTER_GPIO_CLK          RCC_APB2Periph_GPIOB
#define SPI_MASTER_PIN_SCK           GPIO_Pin_13
#define SPI_MASTER_PIN_MISO          GPIO_Pin_14
#define SPI_MASTER_PIN_MOSI          GPIO_Pin_15


#define SPI_MASTER_DMA               DMA1
#define SPI_MASTER_DMA_CLK           RCC_AHBPeriph_DMA1
#define SPI_MASTER_Rx_DMA_Channel    DMA1_Channel4
#define SPI_MASTER_Rx_DMA_FLAG       DMA1_FLAG_TC4
#define SPI_MASTER_Tx_DMA_Channel    DMA1_Channel5
#define SPI_MASTER_Tx_DMA_FLAG        DMA1_FLAG_TC5
#define SPI_MASTER_DR_Base           (SPI2_BASE + 0x0000000C) //0x4001300C


#define BufferSize         5
#define CRCPolynomial      7

typedef void(*ftVoid_Void)(uint32_t);

class MS5803_Class {
private:
//  uint8_t cChar;
//	bool bLedPswOn;
    DMA_InitTypeDef  DMA_InitStructure_TX;
    DMA_InitTypeDef  DMA_InitStructure_RX;
    uint8_t SPI_MASTER_Buffer_Rx[BufferSize];
    uint8_t SPI_MASTER_Buffer_Tx[BufferSize];
//    uint8_t AD7799_state;
//    bool bChangeModeFlag;
//    bool bChangeConfigFlag;
 //   bool bCalibrationNeed;


public:
    ftVoid_Void Callback;
    void Init(void);
    void Task (void);
    void StartTxRx(uint8_t chDataSize);
  /*  void PswPinOn(void);
    void PswPinOff(void);
    void StartZeroCalibration(void);
*/
};

#endif /* MS5803_SPI_H_ */
