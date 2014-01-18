/*
 * ad7799.cpp
 *
 *  Created on: 20 дек. 2013 г.
 *      Author: Stefan
 */
#include "ad7799.h"
#include "stm32f10x.h"

#define START_STEP						1
#define CONFIG_STEP						2
#define MODE_SET_STEP					3
#define IDLE_STEP						4
#define RECEIVE_DATA_STEP				5
#define CALIBRATION_MODE_STEP 			6
#define WAIT_RDY_AFTER_CAIBRATION_STEP	7


void AD7799_Class :: Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;


	SPI_MASTER_Buffer_Tx=AD7799_COM_MODE_PSW_ON;

	/* Enable SPI_MASTER DMA clock */
	RCC_AHBPeriphClockCmd(SPI_MASTER_DMA_CLK , ENABLE);

	/* Enable SPI_MASTER clock and GPIO clock for SPI_MASTER  */
	RCC_APB2PeriphClockCmd(SPI_MASTER_GPIO_CLK |
							SPI_MASTER_CLK |
							SPI_MASTER_CS_GPIO_CLK |
							RCC_APB2Periph_AFIO , ENABLE);

	// Disable JTAG
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	/* Enable SPI1 Pins Software Remapping */
	GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);


	/* Configure SPI_MASTER pins: SCK and MOSI */
	GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_SCK | SPI_MASTER_PIN_MOSI;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_CS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SPI_MASTER_CS_GPIO, &GPIO_InitStructure);

	/* Configure SPI_MASTER MISO pin */
	GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_MISO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

	/* SPI_MASTER configuration ------------------------------------------------*/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = CRCPolynomial;
	SPI_Init(SPI_MASTER, &SPI_InitStructure);
	 SPI_Cmd(SPI1, ENABLE);

	/* SPI_MASTER_Rx_DMA_Channel configuration ---------------------------------*/
	DMA_InitStructure_RX.DMA_PeripheralBaseAddr = (uint32_t)SPI_MASTER_DR_Base;
	DMA_InitStructure_RX.DMA_MemoryBaseAddr = (uint32_t)SPI_MASTER_Buffer_Rx;
	DMA_InitStructure_RX.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure_RX.DMA_BufferSize = BufferSize;
	DMA_InitStructure_RX.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure_RX.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure_RX.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure_RX.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure_RX.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure_RX.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure_RX.DMA_M2M = DMA_M2M_Disable;

	/* SPI_MASTER_Tx_DMA_Channel configuration ---------------------------------*/
	DMA_InitStructure_TX.DMA_PeripheralBaseAddr = (uint32_t)SPI_MASTER_DR_Base;
	DMA_InitStructure_TX.DMA_MemoryBaseAddr = (uint32_t)SPI_MASTER_Buffer_Tx;
	DMA_InitStructure_TX.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure_TX.DMA_BufferSize = BufferSize;
	DMA_InitStructure_TX.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure_TX.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure_TX.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure_TX.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure_TX.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure_TX.DMA_Priority = DMA_Priority_Low;
	DMA_InitStructure_TX.DMA_M2M = DMA_M2M_Disable;

	/* Enable SPI_MASTER */
	SPI_Cmd(SPI_MASTER, ENABLE);

	/* enable AD7799 CS pin */
	GPIO_ResetBits(SPI_MASTER_CS_GPIO,SPI_MASTER_PIN_CS );

	/* Enable DMA channels */
	StartTxRx(1);  // first start DMA
	AD7799_state=START_STEP;
	bChangeModeFlag=false;
	bChangeConfigFlag=false;
}
void AD7799_Class :: Task(void)
{
	uint32_t iData;
	if (DMA_GetFlagStatus(SPI_MASTER_Rx_DMA_FLAG))
	{
		switch (AD7799_state)
		{
		case START_STEP:   // reset ad7799
			SPI_MASTER_Buffer_Tx=AD7799_COM_RESET;
			StartTxRx(4);
			AD7799_state=CONFIG_STEP;
			break;
		case CONFIG_STEP:	// write to configuration register
			SPI_MASTER_Buffer_Tx=AD7799_COM_CONFIG;
			StartTxRx(3);
			AD7799_state=MODE_SET_STEP;
			break;
	// --------- zero calibration need ---------------------------------------
		case CALIBRATION_MODE_STEP: //write to mode register calibration command
			SPI_MASTER_Buffer_Tx=AD7799_COM_MODE_INT_CALIBR;
			StartTxRx(3);
			AD7799_state=WAIT_RDY_AFTER_CAIBRATION_STEP;
			break;
		case WAIT_RDY_AFTER_CAIBRATION_STEP:   // wait RDY pin
			if (GPIO_ReadInputDataBit(SPI_MASTER_GPIO, SPI_MASTER_PIN_MISO) == Bit_RESET)
			{
				AD7799_state=MODE_SET_STEP; // and set required mode.
			}
			break;
//--------------------------------------------------------------------------
		case MODE_SET_STEP: //write to mode register
			if (bLedPswOn) SPI_MASTER_Buffer_Tx=AD7799_COM_MODE_PSW_ON;
			else SPI_MASTER_Buffer_Tx=AD7799_COM_MODE_PSW_OFF;
			StartTxRx(3);
			AD7799_state=IDLE_STEP;
			break;
		case IDLE_STEP:   // wait RDY pin
			if (GPIO_ReadInputDataBit(SPI_MASTER_GPIO, SPI_MASTER_PIN_MISO) == Bit_RESET)
			{
				SPI_MASTER_Buffer_Tx=AD7799_COM_GET_DATA;
				StartTxRx(4);
				AD7799_state=RECEIVE_DATA_STEP;
			}
			break;
		case RECEIVE_DATA_STEP: //data process
				AD7799_state=IDLE_STEP;
				//iData=*(uint32_t*) SPI_MASTER_Buffer_Rx;
				//iData=SPI_MASTER_Buffer_Rx[4];
				iData=SPI_MASTER_Buffer_Rx[3];
				iData+=SPI_MASTER_Buffer_Rx[2]<<8;
				iData+=SPI_MASTER_Buffer_Rx[1]<<16;

				if(Callback != 0) Callback(iData);
				if (bChangeModeFlag)   // change mode request
				{
					AD7799_state=MODE_SET_STEP;
					bChangeModeFlag=false;
				}
				if (bChangeConfigFlag) // change config request, change mode perform automatically
				{
					AD7799_state=CONFIG_STEP;
					bChangeConfigFlag=false;
				}
				if (bCalibrationNeed) // zero-calibration request, after calibration, required mode set automatically
				{
					AD7799_state=CALIBRATION_MODE_STEP;
					bCalibrationNeed=false;
				}
			break;
		}

	}
}

void AD7799_Class :: StartTxRx(uint8_t chDataSize)
{
	/* SPI_MASTER_Tx_DMA_Channel configuration ---------------------------------*/
	DMA_DeInit(SPI_MASTER_Tx_DMA_Channel);
	DMA_InitStructure_TX.DMA_BufferSize = chDataSize;
	DMA_Init(SPI_MASTER_Tx_DMA_Channel, &DMA_InitStructure_TX);
	/* SPI_MASTER_Rx_DMA_Channel configuration ---------------------------------*/
	DMA_DeInit(SPI_MASTER_Rx_DMA_Channel);
	DMA_InitStructure_RX.DMA_BufferSize = chDataSize;
	DMA_Init(SPI_MASTER_Rx_DMA_Channel, &DMA_InitStructure_RX);

	/* Enable SPI_MASTER DMA Rx request */
	SPI_I2S_DMACmd(SPI_MASTER, SPI_I2S_DMAReq_Rx, ENABLE);
	/* Enable SPI_MASTER DMA Tx request */
	SPI_I2S_DMACmd(SPI_MASTER, SPI_I2S_DMAReq_Tx, ENABLE);

	/* Enable DMA channels */
	DMA_Cmd(SPI_MASTER_Rx_DMA_Channel, ENABLE);
	DMA_Cmd(SPI_MASTER_Tx_DMA_Channel, ENABLE);


}
void AD7799_Class :: PswPinOn(void)
{
	bLedPswOn=true;
	bChangeModeFlag=true;
}

void AD7799_Class ::  PswPinOff(void)
{
	bLedPswOn=false;
	bChangeModeFlag=true;
}

void AD7799_Class :: StartZeroCalibration(void)
{
	bCalibrationNeed=true;
	bChangeModeFlag=true;
}
