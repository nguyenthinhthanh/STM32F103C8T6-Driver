/*
 * STM32F103C8T6_I2C_Driver.c
 *
 *  Created on: Aug 27, 2024
 *      Author: ADMINS
 */

#include "STM32F103C8T6_I2C_Driver.h"


/*I2C RESET*/
void I2C1_RESET(void){
	pRCC->APB1RSTR |= (1 << 21);

	pRCC->APB1RSTR &= ~(1 << 21);
}
void I2C2_RESET(void){
	pRCC->APB1RSTR |= (1 << 22);

	pRCC->APB1RSTR &= ~(1 << 22);
}

/*I2C FUNCTION*/
void I2C_ClkControl(I2C_REG_t* pI2Cx, uint8_t Enable){
	if(Enable){
		if(pI2Cx == pI2C1){
			I2C1_CLK_EN();
		}
		else if(pI2Cx == pI2C2){
			I2C2_CLK_EN();
		}
		else{
			/*This is another I2C*/
		}
	}
	else{
		if(pI2Cx == pI2C1){
			I2C1_CLK_DISEN();
		}
		else if(pI2Cx == pI2C2){
			I2C2_CLK_DISEN();
		}
		else{
			/*This is another I2C*/
		}
	}
}

void I2C_PeripheralControl(I2C_REG_t* pI2Cx, uint8_t Enable){
	/*This is PE bit control*/
	if(Enable){
		pI2Cx->CR1 |= (1 << I2C_CR1_PE_OFFSET);
	}
	else{
		pI2Cx->CR1 &= ~(1 << I2C_CR1_PE_OFFSET);
	}
}

static uint32_t IC2_GetPLLClkValue(void){
	/*This is need modified when use PLL as system clock*/
	uint32_t PPL_ClkValue = 8000000;

	return PPL_ClkValue;
}

uint32_t I2C_GetPclk1Value(void){
	/*CHECK CLOCK TREE IN RM0008 TO SEE CLOCK APB1*/
	uint32_t Pclk1_Value = 0;
	uint32_t System_Clock = 0;

	uint32_t reg_tmp = 0;

	uint8_t Clk_Source = ((pRCC->CFGR >> RCC_CFGR_SWS_OFFSET) & 0x3);

	/*00: HSI oscillator used as system clock
	  01: HSE oscillator used as system clock
	  10: PLL used as system clock
	  11: Not applicable*/

	if(Clk_Source == 0){
		System_Clock = 8000000;
	}
	else if(Clk_Source == 1){
		System_Clock = 8000000;
	}
	else if(Clk_Source == 2){
		System_Clock = IC2_GetPLLClkValue();
	}
	else{
		/*This is fault in System clock switch status vaule*/
	}

	/*This is system clock after AHB Prescaler*/
	reg_tmp = ((pRCC->CFGR >> RCC_CFGR_HPRE_OFFSET) & (0xF));

	/*0xxx: SYSCLK not divided
	1000: SYSCLK divided by 2
	1001: SYSCLK divided by 4
	1010: SYSCLK divided by 8
	1011: SYSCLK divided by 16
	1100: SYSCLK divided by 64
	1101: SYSCLK divided by 128
	1110: SYSCLK divided by 256
	1111: SYSCLK divided by 512*/

	if(reg_tmp < 8){
		/*This is clock not divided*/
	}
	else if(reg_tmp == 8){
		System_Clock = System_Clock / 2;
	}
	else if(reg_tmp == 9){
		System_Clock = System_Clock / 4;
	}
	else if(reg_tmp == 10){
		System_Clock = System_Clock / 8;
	}
	else if(reg_tmp == 11){
		System_Clock = System_Clock / 16;
	}
	else if(reg_tmp == 12){
		System_Clock = System_Clock / 64;
	}
	else if(reg_tmp == 13){
		System_Clock = System_Clock / 128;
	}
	else if(reg_tmp == 14){
		System_Clock = System_Clock / 256;
	}
	else if(reg_tmp == 15){
		System_Clock = System_Clock / 512;
	}
	else{
		/*This is fault Prescaler value*/
	}

	/*This is system clock after APB1 Prescaler*/
	reg_tmp = ((pRCC->CFGR >> RCC_CFGR_PPRE1_OFFSET) & (0x7));

	/*0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16*/

	if(reg_tmp < 4){
		/*This is clock not divided*/
	}
	else if(reg_tmp == 4){
		System_Clock = System_Clock / 2;
	}
	else if(reg_tmp == 5){
		System_Clock = System_Clock / 4;
	}
	else if(reg_tmp == 6){
		System_Clock = System_Clock / 8;
	}
	else if(reg_tmp == 7){
		System_Clock = System_Clock / 16;
	}
	else{
		/*This is fault Prescaler value*/
	}

	Pclk1_Value = System_Clock;

	return Pclk1_Value;
}

void I2C_Init(I2C_HANDLE_t* pI2C_Handle){
	uint32_t reg_tmp = 0;
	uint32_t Pclk1_Value;

	/*This is set ACK Control*/
	reg_tmp |= (pI2C_Handle->IC2_Config.I2C_ACKControl << I2C_CR1_ACK_OFFSET);
	pI2C_Handle->pI2Cx->CR1 = reg_tmp;
	reg_tmp = 0;

	/*This is configuration CR2 Frequent*/
	Pclk1_Value = I2C_GetPclk1Value();
	reg_tmp |= (Pclk1_Value / 1000000);
	pI2C_Handle->pI2Cx->CR2 = reg_tmp & 0x3F;
	reg_tmp = 0;

	/*This is configuration OAR1 register*/
	/*Shift 1 because using 7-bit slave and bit 1 don't care*/
	reg_tmp |= pI2C_Handle->IC2_Config.I2C_DeviceAddress << 1;
	pI2C_Handle->pI2Cx->OAR1 = reg_tmp;
	reg_tmp = 0;

	/*Should always be kept bit 14 at 1 by software*/
	/*Why?? I have no idea*/
	pI2C_Handle->pI2Cx->OAR1 |= (1 << 14);

	/*This is configuration CCR value*/
	uint16_t CCR_Value;
	if(pI2C_Handle->IC2_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_STANDARD_MODE){
		/*This is standard mode*/
		pI2C_Handle->pI2Cx->CCR &= ~(1 << I2C_CCR_FS_OFFSET);

		CCR_Value = Pclk1_Value / (2 * pI2C_Handle->IC2_Config.I2C_SCLSpeed);
		pI2C_Handle->pI2Cx->CCR |= (CCR_Value & 0xFFF);
	}
	else{
		/*This is Fast Mode*/
		pI2C_Handle->pI2Cx->CCR |= (1 << I2C_CCR_FS_OFFSET);
		/*This is Fast Mode duty*/
		if(pI2C_Handle->IC2_Config.I2C_FMDutyCycle == I2C_FMDUTY_CYCLE_2){
			pI2C_Handle->pI2Cx->CCR &= ~(1 << I2C_CCR_DUTY_OFFSET);

			CCR_Value = Pclk1_Value / (3 * pI2C_Handle->IC2_Config.I2C_SCLSpeed);
		}
		else if(pI2C_Handle->IC2_Config.I2C_FMDutyCycle == I2C_FMDUTY_CYCLE_16_9){
			pI2C_Handle->pI2Cx->CCR |= (1 << I2C_CCR_DUTY_OFFSET);

			CCR_Value = Pclk1_Value / (25 * pI2C_Handle->IC2_Config.I2C_SCLSpeed);
		}
		else{
			/*This is fault Fast Mode duty vaule*/
		}

		pI2C_Handle->pI2Cx->CCR |= (CCR_Value & 0xFFF);
	}

	/*This is configuration TRISE value*/
	if(pI2C_Handle->IC2_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_STANDARD_MODE){
		/*This is standard mode */
		uint8_t Trise_Value = (uint8_t)(Pclk1_Value / 1000000) + 1; /*1000ns reference in I2C user manual*/
		/*This is clear Time Rise value*/
		pI2C_Handle->pI2Cx->TRISE &= ~(0xFFFF);
		pI2C_Handle->pI2Cx->TRISE = (Trise_Value & 0x3F); /*Time rise Value 6 bits*/
	}
	else{
		/*This is fast mode*/
		uint8_t Trise_Value = (uint8_t)((Pclk1_Value * 300) / 1000000) + 1; /*300ns reference in I2C user manual*/
		/*This is clear Time Rise value*/
		pI2C_Handle->pI2Cx->TRISE &= ~(0xFFFF);
		pI2C_Handle->pI2Cx->TRISE = (Trise_Value & 0x3F); /*Time rise Value 6 bits*/
	}

}

void I2C_DeInit(I2C_REG_t* pI2Cx){
	if(pI2Cx == pI2C1){
		I2C1_RESET();
	}
	else if(pI2Cx == pI2C2){
		I2C2_RESET();
	}
	else{
		/*This is another I2C*/
	}
}

uint8_t I2C_GetFlagStatus(I2C_REG_t* pIC2x,uint8_t StatusOffset, uint8_t OffsetFlag){
	if(StatusOffset == 1){
		if(pIC2x->SR1 & (1 << OffsetFlag)){
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(StatusOffset == 2){
		if(pIC2x->SR2 & (1 << OffsetFlag)){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		/*This is fault out of SR1,SR2*/
		return -1;
	}
}

void I2C_SetAckBit(I2C_HANDLE_t* pI2C_Handle){
	uint32_t reg_tmp = 0;

	/*This is set ACK Control*/
	reg_tmp = (pI2C_Handle->IC2_Config.I2C_ACKControl << I2C_CR1_ACK_OFFSET);
	pI2C_Handle->pI2Cx->CR1 |= reg_tmp;
	reg_tmp = 0;
}

/*DATA SEND AND RECEIVE FUNCTION*/
static void I2C_GenerationStartCondition(I2C_REG_t* pI2Cx){
	pI2Cx->CR1 |= (1 << I2C_CR1_START_OFFSET);
}

static void I2C_GenerationStopCondition(I2C_REG_t* pI2Cx){
	pI2Cx->CR1 |= (1 << I2C_CR1_STOP_OFFSET);
}

static void I2C_SendAddressPhase(I2C_REG_t* pI2Cx, uint8_t SlaveAddress){
	/*Highest bits is read/write bit*/
	SlaveAddress = SlaveAddress << 1;
	SlaveAddress &= ~(1 << 0);

	pI2Cx->DR = SlaveAddress;
}

static void I2C_ClearAddrFlag(I2C_REG_t* pI2Cx){
	uint32_t reg_tmp;
	reg_tmp = pI2Cx->SR1;
	reg_tmp = pI2Cx->SR2;
	(void)reg_tmp;
}

void I2C_MasterSendData(I2C_HANDLE_t* pI2C_Handle, uint8_t* pTxBuffer, uint32_t Length, uint8_t SlaveAddress){
	/*Generation start condition*/
	I2C_GenerationStartCondition(pI2C_Handle->pI2Cx);
	/*Check start condition completed using SB bit in SR1
	if SB bit 1 that mean it completed*/
	while(!(pI2C_Handle->pI2Cx->SR1 & (1 << I2C_SR1_SB_OFFSET)));
	/*Write to 8 bits address with 1 bit w/r, DR register that auto clear SB bits*/
	I2C_SendAddressPhase(pI2C_Handle->pI2Cx, SlaveAddress);
	/*Check address phase is completed using ADDR bit*/
	while(!(pI2C_Handle->pI2Cx->SR1 & (1 << I2C_SR1_ADDR_OFFSET)));
	/*Clear ADDR bit by software reading SR1 register followed reading SR2*/
	I2C_ClearAddrFlag(pI2C_Handle->pI2Cx);
	/*Send slave address while Length > 0*/
	while(Length > 0){
		while(!(pI2C_Handle->pI2Cx->SR1 & (1 << I2C_SR1_TxE_OFFSET)));
		pI2C_Handle->pI2Cx->DR = *pTxBuffer;
		pTxBuffer = pTxBuffer + 1;
		Length = Length - 1;
	}
	/*Wait TxE BTF bit set Data byte transfer succeeded*/
	while(!(pI2C_Handle->pI2Cx->SR1 & (1 << I2C_SR1_TxE_OFFSET)));

	while(!(pI2C_Handle->pI2Cx->SR1 & (1 << I2C_SR1_BTF_OFFSET)));

	/*Generation stop condition*/
	I2C_GenerationStopCondition(pI2C_Handle->pI2Cx);
}

/*INTERRUPT FUNCTION*/
void I2C_IRQPriorityConFig(uint8_t IRQNumber, uint8_t IRQPriority){
	uint8_t	IPRx = IRQNumber / 4;
	uint8_t IPRx_Offset = IRQNumber % 4;
	/*Plus 4 because IPRx have 4 non-bit low implement*/
	*(pNVIC_IPR_BASEADDR + (IPRx)) &= ~(0xF << (8 * IPRx_Offset + 4));
	*(pNVIC_IPR_BASEADDR + (IPRx)) |= (IRQPriority << (8 * IPRx_Offset + 4));
}

void I2C_IRQConFig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t Enable){
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

void I2C_ApplicationEventCallBack(I2C_HANDLE_t* pI2CHandle, uint8_t Event);
