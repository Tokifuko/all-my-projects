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
#include "common.h"




#define BufferSize         5
#define CRCPolynomial      7

//typedef void(*ftVoid_Void)(uint32_t);

class MS5803_Class {
private:
    DMA_InitTypeDef  DMA_InitStructure_TX;
    DMA_InitTypeDef  DMA_InitStructure_RX;
    uint8_t SPI_MASTER_Buffer_Rx[BufferSize];
    uint8_t SPI_MASTER_Buffer_Tx[BufferSize];
    uint16_t MS5803_coefficients[8];
    uint8_t MS5803_coefficients_counter;
    uint8_t MS5803_state;
    uint8_t MS5803_OSR; //conversion speed 0-4
    bool bWaitDevReadyFlag;
    bool bResetFlag;
    bool bSignMinus_dT;
    bool bSignMinus_SENS;
    bool bSignMinus_PPES;
    int32_t dT;
    int32_t TEMP;
    int64_t OFF;
    uint64_t SENS;
    int32_t Presure;
    int32_t counter;

public:

    ftVoid_Void Callback;
    void Init(void);
    void Task (void);
    void StartTxRx(uint8_t chDataSize);
    void SetOSR(uint8_t chOSR); // set conversion speed 0-4
    uint32_t GetTemp(void);
    uint32_t GetPres(void);
    void SendReset (void);
  /*  void PswPinOn(void);
    void PswPinOff(void);
    void StartZeroCalibration(void);
*/
};

#endif /* MS5803_SPI_H_ */
