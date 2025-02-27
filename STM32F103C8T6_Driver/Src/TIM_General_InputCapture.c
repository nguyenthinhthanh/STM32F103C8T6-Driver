/*
 * TIM_General_InputCapture.c
 *
 *  Created on: Sep 13, 2024
 *      Author: ADMINS
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "STM32F103C8T6.h"
#include "STM32F103C8T6_GPIO_Driver.h"
#include "STM32F103C8T6_I2C_Driver.h"
#include "STM32F103C8T6_SPI_Driver.h"
#include "STM32F103C8T6_TIM_Driver.h"


bool first = true;
TIM_GP_HANDLE_t	TIM2_GP_Handle;
uint32_t CC1_Value =0;
uint32_t CC2_Value =0;
uint32_t Result = 0;

void TIM2_IRQHandler(void){
	if(first){
		first = false;
		CC1_Value = (pTIM2_GP->CCR1 & 0xFFFF);
	}
	else{
		CC2_Value = (pTIM2_GP->CCR1 & 0xFFFF);
		TIM_General_Stop(pTIM2_GP);

		Result = CC2_Value - CC1_Value;
	}

	TIM_General_ClearInterrupttFlag(pTIM2_GP, TIM_TIMx_SR_CC1IF_FLAG);
	/*TIM_General_ClearInterrupttFlag(pTIM2_GP, TIM_TIMx_SR_CC2IF_FLAG);
	TIM_General_ClearInterrupttFlag(pTIM2_GP, TIM_TIMx_SR_CC3IF_FLAG);
	TIM_General_ClearInterrupttFlag(pTIM2_GP, TIM_TIMx_SR_CC4IF_FLAG);
	TIM_General_ClearInterrupttFlag(pTIM2_GP, TIM_TIMx_SR_UIF_FLAG);*/
}

int main(){

	GPIO_HANDLE_t PA0_TIM2_IC_Channel1;
	PA0_TIM2_IC_Channel1.pGPIOx = pGPIOA;
	PA0_TIM2_IC_Channel1.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_0;
	PA0_TIM2_IC_Channel1.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_HIGH;
	PA0_TIM2_IC_Channel1.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_ALT_PP;

	GPIO_ClkControl(PA0_TIM2_IC_Channel1.pGPIOx, ENABLE);

	GPIO_Init(&PA0_TIM2_IC_Channel1);


	TIM2_GP_Handle.pTIMx = pTIM2_GP;
	TIM2_GP_Handle.TIM_Config.AutoReLoadPreload = TIM_AUTO_RELOAD_PRELOAD_DISENABLE;
	TIM2_GP_Handle.TIM_Config.ClockDivison = TIM_CLOCK_DIVISION_DIV1;
	TIM2_GP_Handle.TIM_Config.CounterMode = TIM_COUNTER_MODE_UP;
	TIM2_GP_Handle.TIM_Config.Prescaler = 19;
	TIM2_GP_Handle.TIM_Config.CounterPeriod = 65535;

	TIM_General_ClkControl(TIM2_GP_Handle.pTIMx, ENABLE);

	TIM_General_Init(&TIM2_GP_Handle);

	TIM_IC_CONFIG_t	TIM2_GP_IC_Channel1;
	TIM2_GP_IC_Channel1.Channel = 1;
	TIM2_GP_IC_Channel1.Interrupt = ENABLE;
	TIM2_GP_IC_Channel1.Selection = TIM_INPUT_CAPTURE_SELECTION_DIRECT_TI;
	TIM2_GP_IC_Channel1.Filter = 3;
	TIM2_GP_IC_Channel1.Prescaler = TIM_INPUT_CAPTURE_PRESCALER_DIV1;
	TIM2_GP_IC_Channel1.Polarity = TIM_INPUT_CAPTURE_POLARITY_RISING;

	TIM_General_IC_Init(&TIM2_GP_Handle, TIM2_GP_IC_Channel1);


	TIM_General_Start(TIM2_GP_Handle.pTIMx);



	while(1);

	return 0;
}
