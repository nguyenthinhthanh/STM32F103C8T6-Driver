/*
 * TIM_Basic.c
 *
 *  Created on: Sep 9, 2024
 *      Author: ADMINS
 */


#include <stdio.h>
#include <string.h>
#include "STM32F103C8T6.h"
#include "STM32F103C8T6_GPIO_Driver.h"
#include "STM32F103C8T6_I2C_Driver.h"
#include "STM32F103C8T6_SPI_Driver.h"
#include "STM32F103C8T6_TIM_Driver.h"

/*TOGGLE LED PC13 EVERY 500ms WITH TIMER2*/
void TIM2_IRQHandler(void){
	GPIO_ToggleOutPutPin(pGPIOC, GPIO_NO_13);
	TIM_Base_ClearUpdateInterruptFlag(pTIM2_BASE);
	//TIM_Base_IRQHandler(pTIM2_BASE);
}

int main(){
	GPIO_HANDLE_t PC13_Led_Handle;
	PC13_Led_Handle.pGPIOx = pGPIOC;
	PC13_Led_Handle.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_13;
	PC13_Led_Handle.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_LOW;
	PC13_Led_Handle.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_PP;

	GPIO_ClkControl(PC13_Led_Handle.pGPIOx, ENABLE);

	GPIO_Init(&PC13_Led_Handle);

	TIM_BASE_HANDLE_t TIM2_Handle;
	TIM2_Handle.pTIMx = pTIM2_BASE;
	TIM2_Handle.TIM_Config.CounterMode = TIM_COUNTER_MODE_UP;
	TIM2_Handle.TIM_Config.OnePluseMode = TIM_ONEPLUSE_MODE_DISENABLE;
	TIM2_Handle.TIM_Config.Prescaler = 19999;
	TIM2_Handle.TIM_Config.CounterPeriod = 199;
	TIM2_Handle.TIM_Config.AutoReLoadPreload = TIM_AUTO_RELOAD_PRELOAD_DISENABLE;

	TIM_Base_ClkControl(TIM2_Handle.pTIMx, ENABLE);

	TIM_Base_Init(&TIM2_Handle);

	/*Enable and Configuration interrupt*/
	/*TIM_Base_UpdateInterruptControl(TIM2_Handle.pTIMx, ENABLE);

	TIM_IRQConFig(IRQ_TIM2, IRQ_TIM2_PRIORITY, ENABLE);

	TIM_Base_CounterEnable(TIM2_Handle.pTIMx, ENABLE);*/

	TIM_Base_Start_IT(&TIM2_Handle, IRQ_TIM2, IRQ_TIM2_PRIORITY);

	while(1);

	return 0;
}
