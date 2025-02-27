/*
 * STM32F103C8T6_SPI_Driver.h
 *
 *  Created on: Aug 13, 2024
 *      Author: ADMINS
 */

#ifndef INC_STM32F103C8T6_SPI_DRIVER_H_
#define INC_STM32F103C8T6_SPI_DRIVER_H_

#include "STM32F103C8T6.h"



/*STRUCT*/
typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConFig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t	SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t	SPI_SSM;
}SPI_CONFIG_t;

typedef struct{
	SPI_REG_t* pSPIx;
	SPI_CONFIG_t SPI_ConFig;

	/*This is for store value when Interrupt*/
	uint8_t* pRx_Buffer;
	uint8_t* pTx_Buffer;
	uint32_t Rx_Length;
	uint32_t Tx_Length;
	uint8_t	 Rx_Status;
	uint8_t  Tx_Status;
}SPI_HANDLE_t;

/*MACRO SPI*/

/*MACRO SPI MODE*/
#define SPI_DEVICE_MODE_SLAVE		0
#define SPI_DEVICE_MODE_MASTER		1

/*MACRO SPI BUS CONFIG*/
#define SPI_BUS_CONFIG_FULL			1
#define SPI_BUS_CONFIG_HAFT			2
#define SPI_BUS_CONFIG_SIM_RxONLY	3

/*MACRO SPI SCLK SPEED*/
#define SPI_SCLK_SPEED_DIV2			0
#define SPI_SCLK_SPEED_DIV4			1
#define SPI_SCLK_SPEED_DIV8			2
#define SPI_SCLK_SPEED_DIV16		3
#define SPI_SCLK_SPEED_DIV32		4
#define SPI_SCLK_SPEED_DIV64		5
#define SPI_SCLK_SPEED_DIV128		6
#define SPI_SCLK_SPEED_DIV256		7

/*MACRO SPI DATA FRAME FORMAT*/
#define SPI_DFF_8BITS	0
#define SPI_DFF_16BITS	1

/*MACRO SPI CPOL*/
#define SPI_CPOL_LOW	0
#define SPI_CPOL_HIGH	1

/*MACRO SPI CPHA*/
#define SPI_CPHA_LOW	0
#define SPI_CPHA_HIGH	1

/*MACRO SPI SSM*/
#define SPI_SSM_DIS_ENABLE	0
#define SPI_SSM_ENABLE		1

/*MACRO SPI CR1 OFFSET BIT*/
#define SPI_CR1_CPHA_OFFSET			0
#define SPI_CR1_CPOL_OFFSET			1
#define SPI_CR1_MSTR_OFFSET			2
#define SPI_CR1_BR_OFFSET			3
#define SPI_CR1_SPE_OFFSET			6
#define SPI_CR1_LSB_OFFSET			7
#define SPI_CR1_SSI_OFFSET			8
#define SPI_CR1_SSM_OFFSET			9
#define SPI_CR1_RxONLY_OFFSET		10
#define SPI_CR1_DFF_OFFSET			11
#define SPI_CR1_CRC_NEXT_OFFSET		12
#define SPI_CR1_CRC_EN_OFFSET		13
#define SPI_CR1_BIDI_OE_OFFSET		14
#define SPI_CR1_BIDI_MODE_OFFSET	15

/*MACRO SPI CR2 OFFSET BIT*/
#define SPI_CR2_RX_DMA_EN_OFFSET	0
#define SPI_CR2_TX_DMA_EN_OFFSET	1
#define SPI_CR2_SSOE_OFFSET			2
#define SPI_CR2_ERRIE_OFFSET		5
#define SPI_CR2_RXNEIE_OFFSET		6
#define SPI_CR2_TXEIE_OFFSET		7

/*MACRO SPI SR OFFSET BIT*/
#define SPI_SR_RXNE_OFFSET			0
#define SPI_SR_TXE_OFFSET			1
#define SPI_SR_CHSIDE_OFFSET		2
#define SPI_SR_UDR_OFFSET			3
#define SPI_SR_CRCERR_OFFSET		4
#define SPI_SR_MODF_OFFSET			5
#define SPI_SR_OVR_OFFSET			6
#define SPI_SR_BSY_OFFSET			7

/*MACRO SPI STATUS*/
#define SPI_READY		0
#define SPI_Rx_BUSY		1
#define SPI_Tx_BUSY		2

/*MACRO SPI APPLICATION EVENTS*/
#define SPI_EVENT_TX_COMPLETE	0
#define SPI_EVENT_RX_COMPLETE	1
#define SPI_EVENT_OVERUN_ERROR	2
#define SPI_EVENT_CRC_ERROR		3

/*SPI RESET*/
void SPI1_RESET(void);
void SPI2_RESET(void);
void SPI3_RESET(void);

/*SPI FUNCTION*/
void SPI_ClkControl(SPI_REG_t* pSPIx, uint8_t Enable);

void SPI_Init(SPI_HANDLE_t* pSPI_Handle);

void SPI_DeInit(SPI_REG_t* pSPIx);

void SPI_CREnable(SPI_REG_t* pSPIx, uint8_t Enable);

uint8_t SPI_GetFlagStatus(SPI_REG_t* pSPIx, uint8_t OffsetFlag);

void SPI_SendData(SPI_REG_t* pSPIx, uint8_t* pTx_Buffer, uint32_t Length);

void SPI_ReceiveData(SPI_REG_t* pSPIx, uint8_t* pRx_Buffer, uint32_t Length);

/*INTERRUPT FUNCTION*/
void SPI_IRQPriorityConFig(uint8_t IRQNumber, uint8_t IRQPriority);

void SPI_IRQConFig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t Enable);

__attribute__((weak)) void SPI_ApplicationEventCallBack(SPI_HANDLE_t* pSPIHandle, uint8_t Event);

void SPI_IRQHandling(SPI_HANDLE_t* pSPIHandler);

uint8_t SPI_SendDataWithIT(SPI_HANDLE_t* pSPIHandle, uint8_t* pTx_Buffer, uint32_t Length);

uint8_t SPI_ReceiveDataWithIT(SPI_HANDLE_t* pSPIHandle, uint8_t* pRx_Buffer, uint32_t Length);

#endif /* INC_STM32F103C8T6_SPI_DRIVER_H_ */
