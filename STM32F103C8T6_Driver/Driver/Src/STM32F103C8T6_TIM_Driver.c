/*
 * STM32F103C8T6_TIM_Driver.c
 *
 *  Created on: Sep 8, 2024
 *      Author: ADMINS
 */


#include "STM32F103C8T6_TIM_Driver.h"


/*TIMER FUNCTION*/

/*TIMER RESET*/
void TIM1_RESET(void){
	/*This is reset*/
	pRCC->APB2RSTR |= (1 << 11);
	/*This is stop reset*/
	pRCC->APB2RSTR &= ~(1 << 11);
}
void TIM2_RESET(void){
	/*This is reset*/
	pRCC->APB1RSTR |= (1 << 0);
	/*This is stop reset*/
	pRCC->APB1RSTR &= ~(1 << 0);
}
void TIM3_RESET(void){
	/*This is reset*/
	pRCC->APB1RSTR |= (1 << 1);
	/*This is stop reset*/
	pRCC->APB1RSTR &= ~(1 << 1);
}
void TIM4_RESET(void){
	/*This is reset*/
	pRCC->APB1RSTR |= (1 << 2);
	/*This is stop reset*/
	pRCC->APB1RSTR &= ~(1 << 2);
}

void TIM6_RESET(void){
	/*This is reset*/
	pRCC->APB1RSTR |= (1 << 4);
	/*This is stop reset*/
	pRCC->APB1RSTR &= ~(1 << 4);
}
void TIM7_RESET(void){
	/*This is reset*/
	pRCC->APB1RSTR |= (1 << 5);
	/*This is stop reset*/
	pRCC->APB1RSTR &= ~(1 << 5);
}

/*TIMER GET DIRECTION COUNTER FOR GENERAL AND ADVANCE*/
uint8_t TIM_Advance_GetDirectCounter(TIM_AD_REG_t* pTIMx);

uint8_t TIM_General_GetDirectCounter(TIM_GP_REG_t* pTIMx){
	if(!(pTIMx->CR1 & (1 << TIM_TIMx_CR1_DIR_OFFSET))){
		/*This is direct up = 0*/
		return TIM_COUNTER_MODE_UP;
	}
	else{
		/*This is direct down = 1*/
		return TIM_COUNTER_MODE_DOWN;
	}
}

/*TIMER CLEAR UPADTE INTERRUPT FLAG*/
void TIM_Advance_ClearUpdateInterruptFlag(TIM_AD_REG_t* pTIMx){
	pTIMx->SR &= ~(1 << TIM_TIMx_SR_UIF_OFFSET);
}

void TIM_Gerenal_ClearUpdateInterruptFlag(TIM_GP_REG_t* pTIMx){
	pTIMx->SR &= ~(1 << TIM_TIMx_SR_UIF_OFFSET);
}

void TIM_Base_ClearUpdateInterruptFlag(TIM_BASE_REG_t* pTIMx){
	pTIMx->SR &= ~(1 << TIM_TIMx_SR_UIF_OFFSET);
}

/*INTERRUPT FUNCTION*/
void TIM_IRQPriorityConFig(uint8_t IRQNumber, uint8_t IRQPriority){
	uint8_t	IPRx = IRQNumber / 4;
	uint8_t IPRx_Offset = IRQNumber % 4;
	/*Plus 4 because IPRx have 4 non-bit low implement*/
	*(pNVIC_IPR_BASEADDR + (IPRx)) &= ~(0xF << (8 * IPRx_Offset + 4));
	*(pNVIC_IPR_BASEADDR + (IPRx)) |= (IRQPriority << (8 * IPRx_Offset + 4));
}

void TIM_IRQConFig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t Enable){
	if(Enable){
		/*This is set enable interrupt*/
		if(IRQNumber <= 31){
			*pNVIC_ISER0 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 32 && IRQNumber <= 63){
			*pNVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber <= 81){
			*pNVIC_ISER2 |= (1 << (IRQNumber % 32));
		}
		else{
			/*This is fault IRQNumber >= 81*/
			return;
		}

		TIM_IRQPriorityConFig(IRQNumber, IRQPriority);
	}
	else{
		/*This is clear enable interrupt*/
		if(IRQNumber <= 31){
			*pNVIC_ICER0 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 32 && IRQNumber <= 63){
			*pNVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber <= 81){
			*pNVIC_ICER2 |= (1 << (IRQNumber % 32));
		}
		else{
			/*This is fault IRQNumber >= 81*/
			return;
		}
	}
}

/*TIMER GENERAL PURPOSE FUNCTION*/
void TIM_General_ClkControl(TIM_GP_REG_t* pTIMx, uint8_t Enable){
	if(Enable){
		if(pTIMx == pTIM1_GP){
			TIM1_CLK_EN();
		}
		else if(pTIMx == pTIM2_GP){
			TIM2_CLK_EN();
		}
		else if(pTIMx == pTIM3_GP){
			TIM3_CLK_EN();
		}
		else if(pTIMx == pTIM4_GP){
			TIM4_CLK_EN();
		}
		else{
			/*This is another TIM address*/
		}
	}
	else{
		if(pTIMx == pTIM1_GP){
			TIM1_CLK_DISEN();
		}
		else if(pTIMx == pTIM2_GP){
			TIM2_CLK_DISEN();
		}
		else if(pTIMx == pTIM3_GP){
			TIM3_CLK_DISEN();
		}
		else if(pTIMx == pTIM4_GP){
			TIM4_CLK_DISEN();
		}
		else{
			/*This is another TIM address*/
		}
	}
}


void TIM_General_Init(TIM_GP_HANDLE_t* pTIM_Handle){
	uint8_t Counter_Mode = pTIM_Handle->TIM_Config.CounterMode;
	uint32_t reg_tmp = 0;
	/*This is configuration Counter Mode*/
	if((Counter_Mode == TIM_COUNTER_MODE_DOWN) || (Counter_Mode == TIM_COUNTER_MODE_UP)){
		/*This is counter mode up down*/
		reg_tmp = (Counter_Mode << TIM_TIMx_CR1_DIR_OFFSET);
		pTIM_Handle->pTIMx->CR1 = reg_tmp;
		reg_tmp = 0;
	}
	else{
		/*This is center-aligned mode*/
		/*Counter_Mode - 1 = Value bits*/
		reg_tmp = ((Counter_Mode - 1) << TIM_TIMx_CR1_CMS_OFFSET);
		pTIM_Handle->pTIMx->CR1 = reg_tmp;
		reg_tmp = 0;
	}

	/*This is configuration auto reload preload*/
	pTIM_Handle->pTIMx->CR1 |= (pTIM_Handle->TIM_Config.AutoReLoadPreload << TIM_TIMx_CR1_ARPE_OFFSET);
	/*This is configuration clock division*/
	pTIM_Handle->pTIMx->CR1 |= (pTIM_Handle->TIM_Config.ClockDivison << TIM_TIMx_CR1_CKD_OFFSET);

	/*This is set prescaler value*/
	pTIM_Handle->pTIMx->PSC = pTIM_Handle->TIM_Config.Prescaler;
	/*This is set period value*/
	pTIM_Handle->pTIMx->ARR = pTIM_Handle->TIM_Config.CounterPeriod;
}

void TIM_General_DeInit(TIM_GP_REG_t* pTIMx){
	if(pTIMx == pTIM1_GP){
		TIM1_RESET();
	}
	else if(pTIMx == pTIM2_GP){
		TIM2_RESET();
	}
	else if(pTIMx == pTIM3_GP){
		TIM3_RESET();
	}
	else if(pTIMx == pTIM4_GP){
		TIM4_RESET();
	}
	else{
		/*This is another TIM address*/
	}
}

void TIM_General_CounterEnable(TIM_GP_REG_t* pTIMx, uint8_t Enable){
	if(Enable){
		pTIMx->CR1 |= (1 << TIM_TIMx_CR1_CEN_OFFSET);
	}
	else{
		pTIMx->CR1 &= ~(1 << TIM_TIMx_CR1_CEN_OFFSET);
	}
}

void TIM_General_UpdateGeneration(TIM_GP_REG_t* pTIMx){
	/*This bit can be set by software, it is automatically cleared by hardware.*/
	pTIMx->EGR |= (1 << TIM_TIMx_EGR_UG_OFFSET);
}

void TIM_General_UpdateRequestSource(TIM_GP_REG_t* pTIMx, uint8_t Enable){
	if(Enable){
		pTIMx->CR1 |= (1 << TIM_TIMx_CR1_URS_OFFSET);
	}
	else{
		pTIMx->CR1 &= ~(1 << TIM_TIMx_CR1_URS_OFFSET);
	}
}

void TIM_General_UpdateInterruptControl(TIM_GP_REG_t* pTIMx, uint8_t Enable){
	if(Enable){
		pTIMx->DIER |= (1 << TIM_TIMx_DIER_UIE_OFFSET);
	}
	else{
		pTIMx->DIER &= ~(1 << TIM_TIMx_DIER_UIE_OFFSET);
	}
}

void TIM_General_EventInterruptControl(TIM_GP_REG_t* pTIMx, uint16_t Flag, uint8_t Enable){
	if(Enable){
		/*Flag value = Offset bit*/
		pTIMx->DIER |= (1 << Flag);
	}
	else{
		pTIMx->DIER &= ~(1 << Flag);
	}
}

void TIM_General_ClearInterrupttFlag(TIM_GP_REG_t* pTIMx, uint16_t Flag){
	pTIMx->SR &= ~(1 << Flag);
}

void TIM_General_Start(TIM_GP_REG_t* pTIMx){
	pTIMx->CCER |= (1 << 0);

	TIM_General_CounterEnable(pTIMx, ENABLE);

	//pTIMx->SR &= ~(0x1F);
}

void TIM_General_Stop(TIM_GP_REG_t* pTIMx){
	pTIMx->CCER &= ~(1 << 0);

	TIM_General_CounterEnable(pTIMx, DISENABLE);
}

/*INPUT CAPTURE FUNCTION*/
void TIM_General_IC_Init(TIM_GP_HANDLE_t* pTIM_Handle, TIM_IC_CONFIG_t IC_Config){
	uint8_t Channel = IC_Config.Channel;
	/*This is Config value*/
	uint8_t Interrupt = IC_Config.Interrupt;
	uint8_t Selection = IC_Config.Selection;
	uint8_t Filter = IC_Config.Filter;
	uint8_t Prescaler = IC_Config.Prescaler;
	uint8_t Polarity = IC_Config.Polarity;
	/*This is configuration capture channel selection*/
	if(Channel == 1 || Channel == 2){
		pTIM_Handle->pTIMx->CCMR1 &= ~(Selection << (8*(Channel-1)));
		pTIM_Handle->pTIMx->CCMR1 |= (Selection << (8*(Channel-1)));
	}
	else if(Channel == 3 || Channel == 4){
		pTIM_Handle->pTIMx->CCMR1 &= ~(Selection << (8*(Channel-3)));
		pTIM_Handle->pTIMx->CCMR2 |= (Selection << (8*(Channel-3)));
	}
	else{
		/*This is fault channel value*/
	}

	/*This is configuration prescaler for filter*/
	TIM_General_IC_FilterConfig(pTIM_Handle->pTIMx, Channel, Selection, Filter);

	/*This is configuration Polarity*/
		/*Just rising or falling in GP timer*/
		if(Polarity == TIM_INPUT_CAPTURE_POLARITY_RISING){
			pTIM_Handle->pTIMx->CCER &= ~(1 << (1 + 4*(Channel-1)));
		}
		else if(Polarity == TIM_INPUT_CAPTURE_POLARITY_FALLING){
			pTIM_Handle->pTIMx->CCER |= (1 << (1 + 4*(Channel-1)));
		}
		else{
			/*This is fault Polarity value*/
		}

	if(Interrupt){
		TIM_General_IC_Start_IT(pTIM_Handle, Channel);
	}
	else{
		TIM_General_IC_Start(pTIM_Handle, Channel);
	}

	/*This bit-field defines the ratio of the prescaler acting on CC1 input (IC1).
	The prescaler is reset as soon as CC1E=0 (TIMx_CCER register).*/
	if(Channel == 1 || Channel == 2){
		pTIM_Handle->pTIMx->CCMR1 &= ~(Prescaler << (2 + 8*(Channel-1)));
		pTIM_Handle->pTIMx->CCMR1 |= (Prescaler << (2 + 8*(Channel-1)));
	}
	else if(Channel == 3 || Channel == 4){
		pTIM_Handle->pTIMx->CCMR1 &= ~(Prescaler << (2 + 8*(Channel-1)));
		pTIM_Handle->pTIMx->CCMR2 |= (Prescaler << (2 + 8*(Channel-3)));
	}
	else{
		/*This is fault channel value*/
	}

}

void TIM_General_IC_DeInit(TIM_GP_REG_t* pTIMx){
	return;
}

void TIM_General_IC_Start(TIM_GP_HANDLE_t* pTIM_Handle, uint8_t Channel){
	/*This is Capture/Compare enable*/
	uint8_t Offset = (Channel - 1)* 4;
	pTIM_Handle->pTIMx->CCER |= (1 << Offset);
}

void TIM_General_IC_Start_IT(TIM_GP_HANDLE_t* pTIM_Handle, uint8_t Channel){
	/*This is Capture/Compare enable*/
	/*uint8_t Offset = (Channel - 1)* 4;
	pTIM_Handle->pTIMx->CCER |= (1 << Offset);*/

	/*General purpose timer just have TIM2_IRQ for all interrupt*/
	/*Enable and Configuration interrupt*/
	if(Channel == 1){
		TIM_General_EventInterruptControl(pTIM_Handle->pTIMx, TIM_CC1_INTERRUPT_FLAGS, ENABLE);
	}
	else if(Channel == 2){
		TIM_General_EventInterruptControl(pTIM_Handle->pTIMx, TIM_CC2_INTERRUPT_FLAGS, ENABLE);
	}
	else if(Channel == 3){
		TIM_General_EventInterruptControl(pTIM_Handle->pTIMx, TIM_CC3_INTERRUPT_FLAGS, ENABLE);
	}
	else if(Channel == 4){
		TIM_General_EventInterruptControl(pTIM_Handle->pTIMx, TIM_CC4_INTERRUPT_FLAGS, ENABLE);
	}
	else{
		/*This is fault channel*/
	}

	if(pTIM_Handle->pTIMx == pTIM1_GP){
		TIM_IRQConFig(IRQ_TIM1_CC, IRQ_TIM1_CC_PRIORITY, ENABLE);
	}
	else if(pTIM_Handle->pTIMx == pTIM2_GP){
		TIM_IRQConFig(IRQ_TIM2, IRQ_TIM2_PRIORITY, ENABLE);
	}
	else if(pTIM_Handle->pTIMx == pTIM3_GP){
		TIM_IRQConFig(IRQ_TIM3, IRQ_TIM3_PRIORITY, ENABLE);
	}
	else if(pTIM_Handle->pTIMx == pTIM4_GP){
		TIM_IRQConFig(IRQ_TIM4, IRQ_TIM4_PRIORITY, ENABLE);
	}
	else{
		/*This is fault address*/
	}

}

void TIM_General_IC_FilterConfig(TIM_GP_REG_t* pTIMx, uint8_t Channel, uint8_t Selection, uint8_t Filter){
	/*Clear because Filter = 0 then |= is not work*/
	pTIMx->CCMR1 &= ~(Filter << TIM_TIMx_CCMR1_IC_IC1F_OFFSET);
	pTIMx->CCMR1 &= ~(Filter << TIM_TIMx_CCMR1_IC_IC2F_OFFSET);
	pTIMx->CCMR1 &= ~(Filter << TIM_TIMx_CCMR2_IC_IC3F_OFFSET);
	pTIMx->CCMR1 &= ~(Filter << TIM_TIMx_CCMR2_IC_IC4F_OFFSET);

	if(Channel == 1){
		if(Selection == TIM_INPUT_CAPTURE_SELECTION_DIRECT_TI){
			pTIMx->CCMR1 |= (Filter << TIM_TIMx_CCMR1_IC_IC1F_OFFSET);
		}
		else if(Selection == TIM_INPUT_CAPTURE_SELECTION_INDIRECT_TI){
			pTIMx->CCMR1 |= (Filter << TIM_TIMx_CCMR1_IC_IC2F_OFFSET);
		}
		else if(Selection == TIM_INPUT_CAPTURE_SELECTION_TRC){
			return;
		}
		else{
			/*This is fault selection channel value*/
		}
	}
	else if(Channel == 2){
		if(Selection == TIM_INPUT_CAPTURE_SELECTION_DIRECT_TI){
			pTIMx->CCMR1 |= (Filter << TIM_TIMx_CCMR1_IC_IC2F_OFFSET);
		}
		else if(Selection == TIM_INPUT_CAPTURE_SELECTION_INDIRECT_TI){
			pTIMx->CCMR1 |= (Filter << TIM_TIMx_CCMR1_IC_IC1F_OFFSET);
		}
		else if(Selection == TIM_INPUT_CAPTURE_SELECTION_TRC){
			return;
		}
		else{
			/*This is fault selection channel value*/
		}
	}
	else if(Channel == 3){
		if(Selection == TIM_INPUT_CAPTURE_SELECTION_DIRECT_TI){
			pTIMx->CCMR1 |= (Filter << TIM_TIMx_CCMR2_IC_IC3F_OFFSET);
		}
		else if(Selection == TIM_INPUT_CAPTURE_SELECTION_INDIRECT_TI){
			pTIMx->CCMR1 |= (Filter << TIM_TIMx_CCMR2_IC_IC4F_OFFSET);
		}
		else if(Selection == TIM_INPUT_CAPTURE_SELECTION_TRC){
			return;
		}
		else{
			/*This is fault selection channel value*/
		}
	}
	else if(Channel == 4){
		if(Selection == TIM_INPUT_CAPTURE_SELECTION_DIRECT_TI){
			pTIMx->CCMR1 |= (Filter << TIM_TIMx_CCMR2_IC_IC4F_OFFSET);
		}
		else if(Selection == TIM_INPUT_CAPTURE_SELECTION_INDIRECT_TI){
			pTIMx->CCMR1 |= (Filter << TIM_TIMx_CCMR2_IC_IC3F_OFFSET);
		}
		else if(Selection == TIM_INPUT_CAPTURE_SELECTION_TRC){
			return;
		}
		else{
			/*This is fault selection channel value*/
		}
	}
	else{
		/*This is fault channel value*/
	}
}

/*TIMER BASE FUNCTION*/
void TIM_Base_ClkControl(TIM_BASE_REG_t* pTIMx, uint8_t Enable){
	if(Enable){
		if(pTIMx == pTIM2_BASE){
			TIM2_CLK_EN();
		}
		else if(pTIMx == pTIM3_BASE){
			TIM3_CLK_EN();
		}
		else if(pTIMx == pTIM4_BASE){
			TIM4_CLK_EN();
		}
		else if(pTIMx == pTIM6_BASE){
			TIM6_CLK_EN();
		}
		else if(pTIMx == pTIM7_BASE){
			TIM7_CLK_EN();
		}
		else{
			/*This is another TIM address*/
		}
	}
	else{
		if(pTIMx == pTIM2_BASE){
			TIM2_CLK_DISEN();
		}
		else if(pTIMx == pTIM3_BASE){
			TIM3_CLK_DISEN();
		}
		else if(pTIMx == pTIM4_BASE){
			TIM4_CLK_DISEN();
		}
		else if(pTIMx == pTIM6_BASE){
			TIM6_CLK_DISEN();
		}
		else if(pTIMx == pTIM7_BASE){
			TIM7_CLK_DISEN();
		}
		else{
			/*This is another TIM address*/
		}
	}
}

void TIM_Base_Init(TIM_BASE_HANDLE_t* pTIM_Handle){
	uint32_t reg_tmp;
	/*Counter mode up is default and only in basic TIMER*/
	/*This is set prescaler value*/
	pTIM_Handle->pTIMx->PSC = pTIM_Handle->TIM_Config.Prescaler;
	/*This is set period value*/
	pTIM_Handle->pTIMx->ARR = pTIM_Handle->TIM_Config.CounterPeriod;
	/*This is configuration auto reload preload*/
	reg_tmp = (pTIM_Handle->TIM_Config.AutoReLoadPreload << TIM_TIMx_CR1_ARPE_OFFSET);
	/*This is set onepluse mode*/
	reg_tmp |= (pTIM_Handle->TIM_Config.OnePluseMode << TIM_TIMx_CR1_OPM_OFFSET);
	pTIM_Handle->pTIMx->CR1 = reg_tmp;
	reg_tmp = 0;
}

void TIM_Base_DeInit(TIM_BASE_REG_t* pTIMx){
	if(pTIMx == pTIM6_BASE){
		TIM6_RESET();
	}
	else if(pTIMx == pTIM7_BASE){
		TIM7_RESET();
	}
	else{
		/*This is another TIM address*/
	}
}

void TIM_Base_CounterEnable(TIM_BASE_REG_t* pTIMx, uint8_t Enable){
	if(Enable){
		pTIMx->CR1 |= (1 << TIM_TIMx_CR1_CEN_OFFSET);
	}
	else{
		pTIMx->CR1 &= ~(1 << TIM_TIMx_CR1_CEN_OFFSET);
	}
}

void TIM_Base_UpdateInterruptControl(TIM_BASE_REG_t* pTIMx, uint8_t Enable){
	if(Enable){
		pTIMx->DIER |= (1 << TIM_TIMx_DIER_UIE_OFFSET);
	}
	else{
		pTIMx->DIER &= ~(1 << TIM_TIMx_DIER_UIE_OFFSET);
	}
}

void TIM_Base_UpdateEventDisable(TIM_BASE_REG_t* pTIMx){
	pTIMx->CR1 |= (1 << TIM_TIMx_CR1_UDIS_OFFSET);
}

void TIM_Base_MasterModeSelection(TIM_BASE_REG_t* pTIMx, uint8_t MasterMode){
	uint8_t reg_tmp;
	reg_tmp = (MasterMode & 0x7) << TIM_TIMx_CR2_MMS_OFFSET;

	pTIMx->CR2 = reg_tmp;
}

void TIM_Base_UpdateGeneration(TIM_BASE_REG_t* pTIMx){
	/*This bit can be set by software, it is automatically cleared by hardware.*/
	pTIMx->EGR |= (1 << TIM_TIMx_EGR_UG_OFFSET);
}

void TIM_Base_UpdateRequestSource(TIM_BASE_REG_t* pTIMx, uint8_t Enable){
	if(Enable){
		pTIMx->CR1 |= (1 << TIM_TIMx_CR1_URS_OFFSET);
	}
	else{
		pTIMx->CR1 &= ~(1 << TIM_TIMx_CR1_URS_OFFSET);
	}
}

uint16_t TIM_Base_GetCounterValue(TIM_BASE_REG_t* pTIMx){
	return (uint16_t)pTIMx->CNT;
}

void TIM_Base_IRQHandler(TIM_BASE_REG_t* pTIMx){
	TIM_Base_ClearUpdateInterruptFlag(pTIMx);
}

void TIM_Base_Start(TIM_BASE_HANDLE_t* pTIM_Handle){
	TIM_Base_CounterEnable(pTIM_Handle->pTIMx, ENABLE);
}

void TIM_Base_Start_IT(TIM_BASE_HANDLE_t* pTIM_Handle, uint8_t IRQNumber, uint8_t IRQPriority){
	/*Enable and Configuration interrupt*/
	TIM_Base_UpdateInterruptControl(pTIM_Handle->pTIMx, ENABLE);

	TIM_IRQConFig(IRQNumber, IRQPriority, ENABLE);

	TIM_Base_CounterEnable(pTIM_Handle->pTIMx, ENABLE);
}
