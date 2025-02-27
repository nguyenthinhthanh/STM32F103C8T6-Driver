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
	/*PB12 SPI2_NSS*/
	GPIO_HANDLE_t PB12_SPI2_NSS;
	/*PB13 SPI2_SCK*/
	GPIO_HANDLE_t PB13_SPI2_SCK;
	/*PB14 SPI2_MISO*/
	GPIO_HANDLE_t PB14_SPI2_MISO;
	/*PB15 SPI2_MOSI*/
	GPIO_HANDLE_t PB15_SPI2_MOSI;

	/*SPI2 HANDLE*/
	SPI_HANDLE_t SPI2_Handle;

	PB12_SPI2_NSS.pGPIOx = pGPIOB;
	PB13_SPI2_SCK.pGPIOx = pGPIOB;
	PB14_SPI2_MISO.pGPIOx = pGPIOB;
	PB15_SPI2_MOSI.pGPIOx = pGPIOB;

	PB12_SPI2_NSS.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_12;
	PB12_SPI2_NSS.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_HIGH;
	PB12_SPI2_NSS.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_ALT_PP;

	PB13_SPI2_SCK.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_13;
	PB13_SPI2_SCK.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_HIGH;
	PB13_SPI2_SCK.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_ALT_PP;

	PB14_SPI2_MISO.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_14;
	PB14_SPI2_MISO.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_IN;
	PB14_SPI2_MISO.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_IMODE_FLOAT;

	PB15_SPI2_MOSI.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_15;
	PB15_SPI2_MOSI.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_HIGH;
	PB15_SPI2_MOSI.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_ALT_PP;

	/*Enable PB Clock*/
	GPIO_ClkControl(pGPIOB, ENABLE);

	GPIO_Init(&PB12_SPI2_NSS);
	GPIO_Init(&PB13_SPI2_SCK);
	GPIO_Init(&PB14_SPI2_MISO);
	GPIO_Init(&PB15_SPI2_MOSI);

	SPI2_Handle.pSPIx = pSPI2;
	SPI2_Handle.SPI_ConFig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2_Handle.SPI_ConFig.SPI_BusConFig = SPI_BUS_CONFIG_FULL;
	SPI2_Handle.SPI_ConFig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2_Handle.SPI_ConFig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2_Handle.SPI_ConFig.SPI_DFF = SPI_DFF_8BITS;
	SPI2_Handle.SPI_ConFig.SPI_SSM = SPI_SSM_ENABLE;
	SPI2_Handle.SPI_ConFig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV4;



	/*Enable SPI2 Clock*/
	SPI_ClkControl(SPI2_Handle.pSPIx, ENABLE);

	SPI_Init(&SPI2_Handle);

	/*This is set SSI to 1 if not it will MODE FAULT*/
	SPI2_Handle.pSPIx->CR1 |= (1 << SPI_CR1_SSI_OFFSET);

	char Message[] = "I am iron man";

	SPI_CREnable(SPI2_Handle.pSPIx,ENABLE);

	/*while(1){
		SPI_SendData(SPI2_Handle.pSPIx, (uint8_t*)Message, strlen(Message));
		for(uint32_t i =0;i<500000;i++);
	}*/

	SPI_SendData(SPI2_Handle.pSPIx, (uint8_t*)Message, strlen(Message));
	while(1);

	return 0;
}
