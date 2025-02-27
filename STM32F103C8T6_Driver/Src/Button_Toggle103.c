/*
 * Button_Toggle103.c

 *  Created on: Jul 31, 2024
 *      Author: ADMINS
 */


#include<stdio.h>
#include "STM32F103C8T6.h"
#include "STM32F103C8T6_GPIO_Driver.h"


int main(){
	GPIO_HANDLE_t pGPIOC_Handle;
	GPIO_HANDLE_t pGPIOA_Handle;

	pGPIOC_Handle.pGPIOx = pGPIOC;
	pGPIOC_Handle.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_13;
	pGPIOC_Handle.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_LOW;
	pGPIOC_Handle.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_PP;

	pGPIOA_Handle.pGPIOx = pGPIOA;
	pGPIOA_Handle.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_0;
	pGPIOA_Handle.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_IN;
	pGPIOA_Handle.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_IMODE_FLOAT;

	GPIO_ClkControl(pGPIOC_Handle.pGPIOx, ENABLE);
	GPIO_Init(&pGPIOC_Handle);

	GPIO_ClkControl(pGPIOA_Handle.pGPIOx, ENABLE);
	GPIO_Init(&pGPIOA_Handle);

	GPIO_WriteToOutPutPin(pGPIOC_Handle.pGPIOx, GPIO_NO_13, GPIO_PIN_SET);

	while(1){
		uint8_t ReadPin = GPIO_ReadFromInputPin(pGPIOA_Handle.pGPIOx, GPIO_NO_0);
		if(ReadPin){
			for(uint32_t i =0;i<500000;i++);
			GPIO_ToggleOutPutPin(pGPIOC_Handle.pGPIOx, 13);
		}

	}
}

