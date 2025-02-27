/*
 * Button_Iterrupt.c
 *
 *  Created on: Aug 8, 2024
 *      Author: ADMINS
 */

#include<stdio.h>
#include "STM32F103C8T6.h"
#include "STM32F103C8T6_GPIO_Driver.h"

void EXTI0_IRQHandler(void){
	for(uint32_t i =0;i<500000;i++);
	GPIO_IRQHandling(GPIO_NO_0);
	GPIO_ToggleOutPutPin(pGPIOC, GPIO_NO_13);
}

int main(){
	GPIO_HANDLE_t pGPIOC13_LED;
	GPIO_HANDLE_t pGPIOA0_BUTTON;

	pGPIOC13_LED.pGPIOx = pGPIOC;
	pGPIOC13_LED.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_13;
	pGPIOC13_LED.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_LOW;
	pGPIOC13_LED.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_PP;

	pGPIOA0_BUTTON.pGPIOx = pGPIOA;
	pGPIOA0_BUTTON.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_0;
	pGPIOA0_BUTTON.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_IT_FT;

	GPIO_ClkControl(pGPIOA0_BUTTON.pGPIOx, ENABLE);
	GPIO_ClkControl(pGPIOC13_LED.pGPIOx, ENABLE);

	GPIO_Init(&pGPIOA0_BUTTON);
	GPIO_Init(&pGPIOC13_LED);

	GPIO_WriteToOutPutPin(pGPIOC13_LED.pGPIOx, pGPIOC13_LED.GPIO_PinConFig.GPIO_PinNumber, GPIO_PIN_SET);

	GPIO_IRQConFig(6, ENABLE);
	return 0;
}

