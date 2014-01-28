/*
 * ms5803_spi.cpp
 *
 *  Created on: 20 ���. 2014 �.
 *      Author: Stefan
 */
#include "ms5803_spi.h"

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

#define START_RESET_STEP		1
#define READ_ROM_COEF_STEP		2
#define	CONV_TEMP_STEP			3
#define CONV_PRES_STEP			4
#define	READ_TEMP_STEP			5
#define	READ_PRES_STEP			6
#define CALC_TEMP_STEP			7
#define CALC_PRES_STEP			8

#define MS5803_RESET_COMAND 		0x1E
#define MS5803_READ_COEF_COMAND 	0xA0
#define MS5803_TEMP_CONV_COMAND 	0x40
#define MS5803_PRES_CONV_COMAND		0x50
#define MS5803_ADC_READ_COMAND		0x00

void MS5803_Class :: Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable SPI_MASTER DMA clock */
	RCC_AHBPeriphClockCmd(SPI_MASTER_DMA_CLK , ENABLE);

	/* Enable SPI_MASTER clock and GPIO clock for SPI_MASTER  */
	RCC_APB2PeriphClockCmd(SPI_MASTER_GPIO_CLK |
							RCC_APB2Periph_AFIO , ENABLE);
	RCC_APB1PeriphClockCmd(SPI_MASTER_CLK,ENABLE);

	// Disable JTAG
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	/* Enable SPI1 Pins Software Remapping */
	//GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);


	/* Configure SPI_MASTER pins: SCK */
	GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_SCK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

	/* and MOSI */
	GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_MOSI ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

	/* Configure SPI_MASTER MISO pin */
	GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_MISO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

	/* SPI_MASTER configuration ------------------------------------------------*/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = CRCPolynomial;
	SPI_Init(SPI_MASTER, &SPI_InitStructure);
	SPI_Cmd(SPI_MASTER, ENABLE);

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

	/* Enable DMA channels */
	for (uint8_t i=0; i<BufferSize;i++)
	{
		SPI_MASTER_Buffer_Tx[i]=0;
	}
	SPI_MASTER_Buffer_Tx[0]=0x1E; // RESET_COMAND
	StartTxRx(1);  // first start DMA
	MS5803_state=READ_ROM_COEF_STEP;
	bWaitDevReadyFlag=true;
	MS5803_coefficients_counter=0;

}

void MS5803_Class :: Task(void)
{
	uint32_t iD2=0;
	uint32_t iD1=0;
	if (DMA_GetFlagStatus(SPI_MASTER_Rx_DMA_FLAG))
	{
		if (bWaitDevReadyFlag) // in many cases, after sending command, you need to wait for the device
		{
			if (GPIO_ReadInputDataBit(SPI_MASTER_GPIO, SPI_MASTER_PIN_MISO) != Bit_RESET) return;
			bWaitDevReadyFlag=false;
		}

		switch (MS5803_state)
		{
		case START_RESET_STEP:   // reset MS5803
			SPI_MASTER_Buffer_Tx[0]=MS5803_RESET_COMAND;
			StartTxRx(1);
			MS5803_state=READ_ROM_COEF_STEP;
			bWaitDevReadyFlag=true;
			MS5803_coefficients_counter=0;
			break;
		case READ_ROM_COEF_STEP:	// read 8 coefficients
			if (MS5803_coefficients_counter!=0) // save received coefficient
			{
				MS5803_coefficients[MS5803_coefficients_counter-1]=SPI_MASTER_Buffer_Rx[2]+(SPI_MASTER_Buffer_Rx[1]<<8);
			}
			if (MS5803_coefficients_counter!=7) // get next coefficient
			{
				SPI_MASTER_Buffer_Tx[0]=MS5803_READ_COEF_COMAND+(MS5803_coefficients_counter<<2);
				StartTxRx(3);
				MS5803_coefficients_counter++;
			}
			else MS5803_state=CONV_TEMP_STEP; //successfully received coefficients, go next step
			break;
		case CONV_PRES_STEP:   // send command to start ADC conversion D1
			SPI_MASTER_Buffer_Tx[0]=MS5803_PRES_CONV_COMAND+(MS5803_OSR<<2);
			StartTxRx(1);
			bWaitDevReadyFlag=true;
			MS5803_state=READ_PRES_STEP;
			break;
		case CONV_TEMP_STEP:   // send command to start ADC conversion D2
			SPI_MASTER_Buffer_Tx[0]=MS5803_TEMP_CONV_COMAND+(MS5803_OSR<<2);
			StartTxRx(1);
			bWaitDevReadyFlag=true;
			MS5803_state=READ_TEMP_STEP;
			break;
		case READ_TEMP_STEP: // read ADC data after conversion
			SPI_MASTER_Buffer_Tx[0]=MS5803_ADC_READ_COMAND;
			StartTxRx(4);
			MS5803_state=CALC_TEMP_STEP;
			break;
		case CALC_TEMP_STEP:
			iD2=SPI_MASTER_Buffer_Rx[3]+(SPI_MASTER_Buffer_Rx[2]<<8)+(SPI_MASTER_Buffer_Rx[1]<<16);
			dT=iD2-(MS5803_coefficients[5]<<8);
			TEMP=2000+((dT*MS5803_coefficients[6])>>23);   // !!!!!!!!!!!!!!! data type conversion !!!!!!!!!!!!!!!!
			MS5803_state=CONV_PRES_STEP;
			break;
		case READ_PRES_STEP: // read ADC data after conversion
			SPI_MASTER_Buffer_Tx[0]=MS5803_ADC_READ_COMAND;
			StartTxRx(4);
			MS5803_state=CALC_PRES_STEP;
			break;
		case CALC_PRES_STEP:
			iD1=SPI_MASTER_Buffer_Rx[3]+(SPI_MASTER_Buffer_Rx[2]<<8)+(SPI_MASTER_Buffer_Rx[1]<<16);
			OFF=(MS5803_coefficients[5]<<18)+((MS5803_coefficients[4]*dT)>>5);
			SENS=(MS5803_coefficients[1]<<17)+((MS5803_coefficients[3]*dT)>>7);
			Presure=(((iD1*SENS)>>21)-OFF)>>15;			// !!!!!!!!!!!!!!! data type conversion !!!!!!!!!!!!!!!!
			MS5803_state=CONV_TEMP_STEP;  //for best performance, don`t measure temp every time.
			Callback(Presure);
			break;
		}
	}
}

void MS5803_Class :: StartTxRx(uint8_t chDataSize)
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

void MS5803_Class ::SetOSR(uint8_t chOSR) {	if (chOSR<=4) MS5803_OSR=chOSR;}// set conversion speed 0-4
uint32_t MS5803_Class ::GetTemp(void){	return TEMP;}
uint32_t MS5803_Class ::GetPres(void){	return Presure;}
