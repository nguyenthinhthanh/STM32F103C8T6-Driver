/*
 * STM32F103C8T6_GPIO_Driver.c
 *
 *  Created on: Jul 24, 2024
 *      Author: ADMINS
 */

#include <STM32F103C8T6_GPIO_Driver.h>

/*ALTERNATIVE FUNCTION*/
void AFIO_Init(void){
	AFIO_CLK_EN();
	return;
}
void AFIO_DeInit(void){
	return;
}

/*HELPER FUNCTION*/
uint8_t EXTIxValue_FromPort(GPIO_REG_t* pGPIOx){
	if(pGPIOx == pGPIOA){
		return EXTI_PAx;
	}
	else if(pGPIOx == pGPIOB){
		return EXTI_PBx;
	}
	else if(pGPIOx == pGPIOC){
		return EXTI_PCx;
	}
	else if(pGPIOx == pGPIOD){
		return EXTI_PDx;
	}
	else if(pGPIOx == pGPIOE){
		return EXTI_PEx;
	}
	else if(pGPIOx == pGPIOF){
		return EXTI_PFx;
	}
	else if(pGPIOx == pGPIOG){
		return EXTI_PGx;
	}
	else{
		/*This is fault address*/
		return -1;
	}
}

/*PERIPHERAL FUNCTION*/
void GPIO_Init(GPIO_HANDLE_t* pGPIOHandle){
	uint32_t reg_tmp = 0;
	uint8_t PinNumber = pGPIOHandle->GPIO_PinConFig.GPIO_PinNumber;
	uint8_t PinMode = pGPIOHandle->GPIO_PinConFig.GPIO_PinMode;
	uint8_t PinConfig = pGPIOHandle->GPIO_PinConFig.GPIO_PinConfiguration;
	/*Set Mode and Speed in Mode*/
	if(pGPIOHandle->GPIO_PinConFig.GPIO_PinMode <= GPIO_MODE_OUT_HIGH){
		/*This is non interrupt mode*/
		if(PinNumber <= 7){
			/*Low registor mode*/
			reg_tmp |= pGPIOHandle->GPIO_PinConFig.GPIO_PinMode << (4 * PinNumber);
			pGPIOHandle->pGPIOx->CRL &= ~(0x3 << (4 * PinNumber));
			pGPIOHandle->pGPIOx->CRL |= reg_tmp;
			reg_tmp = 0;
		}
		else{
			/*High registor mode*/
			reg_tmp |= pGPIOHandle->GPIO_PinConFig.GPIO_PinMode << (4 * (PinNumber % 8));
			pGPIOHandle->pGPIOx->CRH &= ~(0x3 << (4 * (PinNumber % 8)));
			pGPIOHandle->pGPIOx->CRH |= reg_tmp;
			reg_tmp = 0;
		}
	}
	else{
		/*This is interrupt mode*/
		/*This is interrupt mode*/
		if(PinMode == GPIO_MODE_IT_FT){
			/*This is Interrupt Falling*/
			pEXTI->FTSR |= (1 << PinNumber);
			pEXTI->RTSR &= ~(1 << PinNumber);
		}
		else if(PinMode == GPIO_MODE_IT_RT){
			/*This is Interrupt Rising*/
			pEXTI->RTSR |= (1 << PinNumber);
			pEXTI->FTSR &= ~(1 << PinNumber);
		}
		else if(PinMode == GPIO_MODE_IT_RST){
			/*This is both Interrupt Rising and Falling*/
			pEXTI->RTSR |= (1 << PinNumber);
			pEXTI->FTSR |= (1 << PinNumber);
		}
		else{
			/*This is fault PinMode*/
		}
		/*This is configuration EXTI channel*/
		uint8_t EXTIx = PinNumber / 4;
		uint8_t EXTIX_Offset = PinNumber % 4;
		uint8_t EXTIx_Value = EXTIxValue_FromPort(pGPIOHandle->pGPIOx);
		AFIO_CLK_EN();
		pAFIO->EXTI[EXTIx] |= (EXTIx_Value << (EXTIX_Offset * 4));
		/*This is Mask Interrupt meant Enable Interrput*/
		pEXTI->IMR |= (1 << PinNumber);

		return;  /*DOUBLE CHECK ALTERNATIVE FUNCTION*/
	}

	/*Set pin Configuration*/
	if(PinNumber <= 7){
		/*This is Low*/
		/*This is Input Output Mode Configuration*/
		reg_tmp |= pGPIOHandle->GPIO_PinConFig.GPIO_PinConfiguration << (2 + 4 * PinNumber);
		pGPIOHandle->pGPIOx->CRL &= ~(0x3 << (2 + 4 * PinNumber));
		pGPIOHandle->pGPIOx->CRL |= reg_tmp;
		reg_tmp = 0;
	}
	else{
		/*This is High*/
		/*This is Input Output Mode Configuration*/
		reg_tmp |= pGPIOHandle->GPIO_PinConFig.GPIO_PinConfiguration << (2 + 4 * (PinNumber % 8));
		pGPIOHandle->pGPIOx->CRH &= ~(0x3 << (2 + 4 * (PinNumber % 8)));
		pGPIOHandle->pGPIOx->CRH |= reg_tmp;
		reg_tmp = 0;
	}

	/*Set Alternative Function Mode*/
	bool Alt_Mode = (PinMode >= GPIO_MODE_OUT_LOW && PinMode <= GPIO_MODE_OUT_HIGH) && (PinConfig == GPIO_OMODE_ALT_OD || PinConfig == GPIO_OMODE_ALT_PP);
	if(Alt_Mode){
		/*Enable APB2*/
		AFIO_Init();
	}
}

/*GPIO RESET*/
void GPIOA_RESET(void){
	/*This is Reset*/
	pRCC->APB2RSTR |= (1 << 2);
	/*This is stop Reset*/
	pRCC->APB2RSTR &= ~(1 << 2);
}
void GPIOB_RESET(void){
	/*This is Reset*/
	pRCC->APB2RSTR |= (1 << 3);
	/*This is stop Reset*/
	pRCC->APB2RSTR &= ~(1 << 3);
}
void GPIOC_RESET(void){
	/*This is Reset*/
	pRCC->APB2RSTR |= (1 << 4);
	/*This is stop Reset*/
	pRCC->APB2RSTR &= ~(1 << 4);
}
void GPIOD_RESET(void){
	/*This is Reset*/
	pRCC->APB2RSTR |= (1 << 5);
	/*This is stop Reset*/
	pRCC->APB2RSTR &= ~(1 << 5);
}
void GPIOE_RESET(void){
	/*This is Reset*/
	pRCC->APB2RSTR |= (1 << 6);
	/*This is stop Reset*/
	pRCC->APB2RSTR &= ~(1 << 6);
}

void GPIO_DeInit(GPIO_REG_t* pGPIOx){
	/*GPIO  Reset APB2RSTR*/
	if(pGPIOx == pGPIOA){
		GPIOA_RESET();
	}
	else if(pGPIOx == pGPIOB){
		GPIOB_RESET();
	}
	else if(pGPIOx == pGPIOC){
		GPIOC_RESET();
	}
	else if(pGPIOx == pGPIOD){
		GPIOD_RESET();
	}
	else if(pGPIOx == pGPIOE){
		GPIOE_RESET();
	}
	else{
		/*This is fault address*/
	}
}

void GPIO_ClkControl(GPIO_REG_t* pGPIOx, uint8_t Enable){
	if(Enable){
		/// Set
		if(pGPIOx == pGPIOA){
			GPIOA_CLK_EN();
		}
		else if(pGPIOx == pGPIOB){
			GPIOB_CLK_EN();
		}
		else if(pGPIOx == pGPIOC){
			GPIOC_CLK_EN();
		}
		else if(pGPIOx == pGPIOD){
			GPIOD_CLK_EN();
		}
		else if(pGPIOx == pGPIOE){
			GPIOE_CLK_EN();
		}
		else{
			/*This is fault address GPIO*/
		}
	}
	else{
		/// Clear
		if(pGPIOx == pGPIOA){
			GPIOA_CLK_DISEN();
		}
		else if(pGPIOx == pGPIOB){
			GPIOB_CLK_DISEN();
		}
		else if(pGPIOx == pGPIOC){
			GPIOC_CLK_DISEN();
		}
		else if(pGPIOx == pGPIOD){
			GPIOD_CLK_DISEN();
		}
		else if(pGPIOx == pGPIOE){
			GPIOE_CLK_DISEN();
		}
		else{
			/*This is fault address GPIO*/
		}
	}
}

uint8_t GPIO_ReadFromInputPin(GPIO_REG_t* pGPIOx, uint8_t PinNumber){
	uint8_t Value;
	Value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);

	return Value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_REG_t* pGPIOx){
	uint16_t Value;
	Value = (uint16_t)(pGPIOx->IDR && 0x0000FFFF);

	return Value;
}
void GPIO_WriteToOutPutPin(GPIO_REG_t* pGPIOx, uint8_t PinNumber, uint8_t Status){
	if(Status == GPIO_PIN_SET){
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else if(Status == GPIO_PIN_RESET){
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
	else{
		/*This is fault value of status*/
	}
}
void GPIO_WriteToOutPutPort(GPIO_REG_t* pGPIOx, uint16_t Value){
	pGPIOx->ODR = Value;
}
void GPIO_ToggleOutPutPin(GPIO_REG_t* pGPIOx, uint8_t PinNumber){
	pGPIOx->ODR = pGPIOx->ODR ^ (1 << PinNumber);
}

/*INTERRUPT FUNCTION*/
void GPIO_IRQPriorityConFig(uint8_t IRQNumber, uint8_t IRQPriority){
	uint8_t	IPRx = IRQNumber / 4;
	uint8_t IPRx_Offset = IRQNumber % 4;
	/*Plus 4 because IPRx have 4 non-bit low implement*/
	*(pNVIC_IPR_BASEADDR + (IPRx)) &= ~(0xF << (8 * IPRx_Offset + 4));
	*(pNVIC_IPR_BASEADDR + (IPRx)) |= (IRQPriority << (8 * IPRx_Offset + 4));
}

void GPIO_IRQConFig(uint8_t IRQNumber, uint8_t Enable){
	if(Enable == ENABLE){
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
		}
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
		}
	}
}
void GPIO_IRQHandling(uint8_t PinNumber){
	if(pEXTI->PR & (1 << PinNumber)){
		/*Write 1 to clear pendding bit*/
		pEXTI->PR |= (1 << PinNumber);
	}
}

