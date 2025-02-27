/*
 * SPI_Test.c
 *
 *  Created on: Aug 15, 2024
 *      Author: ADMINS
 */

#include "STM32F103C8T6_GPIO_Driver.h"
#include "STM32F103C8T6_SPI_Driver.h"
#include <string.h>
#include <stdio.h>

int main(){
	/*PA4 SPI1_NSS*/
	GPIO_HANDLE_t PA4_SPI1_NSS;
	(void)PA4_SPI1_NSS;
	/*PA5 SPI1_SCK*/
	GPIO_HANDLE_t PA5_SPI1_SCK;
	/*PA6 SPI1_MISO*/
	GPIO_HANDLE_t PA6_SPI1_MISO;
	(void)PA6_SPI1_MISO;
	/*PA7 SPI1_MOSI*/
	GPIO_HANDLE_t PA7_SPI1_MOSI;

	/*SPI2 HANDLE*/
	SPI_HANDLE_t SPI1_Handle;

	PA4_SPI1_NSS.pGPIOx = pGPIOA;
	PA5_SPI1_SCK.pGPIOx = pGPIOA;
	PA6_SPI1_MISO.pGPIOx = pGPIOA;
	PA7_SPI1_MOSI.pGPIOx = pGPIOA;

	PA4_SPI1_NSS.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_4;
	PA4_SPI1_NSS.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_HIGH;
	PA4_SPI1_NSS.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_ALT_PP;

	PA5_SPI1_SCK.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_5;
	PA5_SPI1_SCK.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_HIGH;
	PA5_SPI1_SCK.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_ALT_PP;

	PA6_SPI1_MISO.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_6;
	PA6_SPI1_MISO.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_IN;
	PA6_SPI1_MISO.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_IMODE_FLOAT;

	PA7_SPI1_MOSI.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_7;
	PA7_SPI1_MOSI.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_HIGH;
	PA7_SPI1_MOSI.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_ALT_PP;

	/*Enable PB Clock*/
	GPIO_ClkControl(pGPIOA, ENABLE);

	//GPIO_Init(&PA4_SPI1_NSS);
	GPIO_Init(&PA5_SPI1_SCK);
	//GPIO_Init(&PA6_SPI1_MISO);
	GPIO_Init(&PA7_SPI1_MOSI);

	SPI1_Handle.pSPIx = pSPI1;
	SPI1_Handle.SPI_ConFig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI1_Handle.SPI_ConFig.SPI_BusConFig = SPI_BUS_CONFIG_FULL;
	SPI1_Handle.SPI_ConFig.SPI_CPOL = SPI_CPOL_LOW;
	SPI1_Handle.SPI_ConFig.SPI_CPHA = SPI_CPHA_LOW;
	SPI1_Handle.SPI_ConFig.SPI_DFF = SPI_DFF_8BITS;
	SPI1_Handle.SPI_ConFig.SPI_SSM = SPI_SSM_ENABLE;
	SPI1_Handle.SPI_ConFig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV4;

	/*Enable SPI1 Clock*/
	SPI_ClkControl(SPI1_Handle.pSPIx, ENABLE);

	/*Remap SPI1*/
	//pAFIO->MAPR |= (1 << 0);

	SPI_Init(&SPI1_Handle);

	/*This is set SSI to 1 if not it will MODE FAULT*/
	SPI1_Handle.pSPIx->CR1 |= (1 << SPI_CR1_SSI_OFFSET);

	char Message[] = "I am iron man";

	SPI_CREnable(SPI1_Handle.pSPIx,ENABLE);

	/*while(1){
		SPI_SendData(SPI2_Handle.pSPIx, (uint8_t*)Message, strlen(Message));
		for(uint32_t i =0;i<500000;i++);
	}*/

	SPI_SendData(SPI1_Handle.pSPIx, (uint8_t*)Message, strlen(Message));
	while(1);

	return 0;
}
