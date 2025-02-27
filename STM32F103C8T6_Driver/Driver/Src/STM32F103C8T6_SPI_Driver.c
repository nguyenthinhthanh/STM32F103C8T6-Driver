/*
 * STM32F103C8T6_SPI_Driver.c
 *
 *  Created on: Aug 13, 2024
 *      Author: ADMINS
 */

#include "STM32F103C8T6_SPI_Driver.h"

/*SPI FUNCTION*/
void SPI_ClkControl(SPI_REG_t* pSPIx, uint8_t Enable){
	if(Enable){
		if(pSPIx == pSPI1){
			SPI1_CLK_EN();
		}
		else if(pSPIx == pSPI2){
			SPI2_CLK_EN();
		}
		else if(pSPIx == pSPI3){
			SPI3_CLK_EN();
		}
		else{
			/*This is another SPI address*/
		}
	}
	else{
		if(pSPIx == pSPI1){
			SPI1_CLK_DISEN();
		}
		else if(pSPIx == pSPI2){
			SPI2_CLK_DISEN();
		}
		else if(pSPIx == pSPI3){
			SPI3_CLK_DISEN();
		}
		else{
			/*This is another SPI address*/
		}
	}
}

/*SPI RESET*/
void SPI1_RESET(void){
	/*This is reset*/
	pRCC->APB2RSTR |= (1 << 12);
	/*This is stop reset*/
	pRCC->APB2RSTR &= ~(1 << 12);
}
void SPI2_RESET(void){
	/*This is reset*/
	pRCC->APB1RSTR |= (1 << 14);
	/*This is stop reset*/
	pRCC->APB1RSTR &= ~(1 << 14);
}
void SPI3_RESET(void){
	/*This is reset*/
	pRCC->APB1RSTR |= (1 << 15);
	/*This is stop reset*/
	pRCC->APB1RSTR &= ~(1 << 15);
}

void SPI_Init(SPI_HANDLE_t* pSPI_Handle){
	uint32_t reg_tmp = 0;
	uint32_t Bus_ConFig = pSPI_Handle->SPI_ConFig.SPI_BusConFig;

	/*This is reset CR1 register*/
	pSPI_Handle->pSPIx->CR1 = reg_tmp;

	/*This is Device Mode*/
	reg_tmp |= (pSPI_Handle->SPI_ConFig.SPI_DeviceMode << SPI_CR1_MSTR_OFFSET);

	/*This is Bus Config*/
	if(Bus_ConFig == SPI_BUS_CONFIG_FULL){
		pSPI_Handle->pSPIx->CR1 &= ~(1 << SPI_CR1_BIDI_MODE_OFFSET);
	}
	else if(Bus_ConFig == SPI_BUS_CONFIG_HAFT){
		pSPI_Handle->pSPIx->CR1 |= (1 << SPI_CR1_BIDI_MODE_OFFSET);
	}
	else if(Bus_ConFig == SPI_BUS_CONFIG_SIM_RxONLY){
		pSPI_Handle->pSPIx->CR1 &= ~(1 << SPI_CR1_BIDI_MODE_OFFSET);
		pSPI_Handle->pSPIx->CR1 |= (1 << SPI_CR1_RxONLY_OFFSET);
	}
	else{
		/*This is fault Bus Configuration value*/
	}

	/*This is Sclk Speed*/
	reg_tmp |= (pSPI_Handle->SPI_ConFig.SPI_SclkSpeed << SPI_CR1_BR_OFFSET);
	/*This is Data Frame Format*/
	reg_tmp |= (pSPI_Handle->SPI_ConFig.SPI_DFF << SPI_CR1_DFF_OFFSET);
	/*This is CPHA*/
	reg_tmp |= (pSPI_Handle->SPI_ConFig.SPI_CPHA << SPI_CR1_CPHA_OFFSET);
	/*This is CPOL*/
	reg_tmp |= (pSPI_Handle->SPI_ConFig.SPI_CPOL << SPI_CR1_CPOL_OFFSET);
	/*This is SSM*/
	reg_tmp |= (pSPI_Handle->SPI_ConFig.SPI_SSM << SPI_CR1_SSM_OFFSET);
	/*This is set CR1*/
	pSPI_Handle->pSPIx->CR1 |= reg_tmp;
	reg_tmp = 0;
}

void SPI_DeInit(SPI_REG_t* pSPIx){
	if(pSPIx == pSPI1){
		SPI1_RESET();
	}
	else if(pSPIx == pSPI2){
		SPI2_RESET();
	}
	else if(pSPIx == pSPI3){
		SPI3_RESET();
	}
	else{
		/*This is another SPI address*/
	}
}

void SPI_CREnable(SPI_REG_t* pSPIx,uint8_t Enable){
	/*SPI Enable bit*/
	if(Enable){
		pSPIx->CR1 |= (1 << SPI_CR1_SPE_OFFSET);
	}
	else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE_OFFSET);
	}
}

uint8_t SPI_GetFlagStatus(SPI_REG_t* pSPIx, uint8_t OffsetFlag){
	if((pSPIx->SR & (1 << OffsetFlag))){
		return 1;
	}
	else{
		return 0;
	}
}

void SPI_SendData(SPI_REG_t* pSPIx, uint8_t* pTx_Buffer, uint32_t Length){
	while(Length > 0){
		/*This is wait Tx Buffer empty*/
		while(!(pSPIx->SR & (1 << SPI_SR_TXE_OFFSET)));
		/*This is check DFF 8 bits or 16 bits*/
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF_OFFSET)){
			/*This is 16 bits*/
			pSPIx->DR = *((uint16_t*)pTx_Buffer);
			Length = Length - 2;
			pTx_Buffer = pTx_Buffer + 2;
		}
		else{
			/*This is 8 bits*/
			pSPIx->DR = *(pTx_Buffer);
			Length = Length - 1;
			pTx_Buffer = pTx_Buffer + 1;
		}
	}
}

void SPI_ReceiveData(SPI_REG_t* pSPIx, uint8_t* pRx_Buffer, uint32_t Length){
	pRx_Buffer = (uint8_t*)malloc(Length* sizeof(uint8_t));
	while(Length > 0){
		/*This is wait Rx Buffer empty*/
		while(!(pSPIx->SR & (1 << SPI_SR_RXNE_OFFSET)));
		/*This is check DFF 8 bits or 16 bits*/
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF_OFFSET)){
			/*This is 16 bits*/
			*((uint16_t*)pRx_Buffer) = pSPIx->DR;
			pRx_Buffer = pRx_Buffer + 2;
			Length = Length - 2;
		}
		else{
			/*This is 8 bits*/
			*pRx_Buffer = (uint8_t)pSPIx->DR;
			pRx_Buffer = pRx_Buffer + 1;
			Length = Length - 1;
		}
	}
}


/*INTERRUPT FUNCTION*/
void SPI_IRQPriorityConFig(uint8_t IRQNumber, uint8_t IRQPriority){
	uint8_t	IPRx = IRQNumber / 4;
	uint8_t IPRx_Offset = IRQNumber % 4;
	/*Plus 4 because IPRx have 4 non-bit low implement*/
	*(pNVIC_IPR_BASEADDR + (IPRx)) &= ~(0xF << (8 * IPRx_Offset + 4));
	*(pNVIC_IPR_BASEADDR + (IPRx)) |= (IRQPriority << (8 * IPRx_Offset + 4));
}

void SPI_IRQConFig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t Enable){
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

__attribute__((weak)) void SPI_ApplicationEventCallBack(SPI_HANDLE_t* pSPIHandle, uint8_t Event){
	return;
}

static void SPI_ClearOverunFlag(SPI_HANDLE_t* pSPIHandle){
	uint8_t reg_temp;
	reg_temp = pSPIHandle->pSPIx->DR;
	reg_temp = pSPIHandle->pSPIx->SR;
	(void)reg_temp;
}

static void SPI_CloseTransMission(SPI_HANDLE_t* pSPIHandle){
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE_OFFSET);
	pSPIHandle->Tx_Length = 0;
	pSPIHandle->pTx_Buffer = NULL;
	pSPIHandle->Tx_Status = SPI_READY;
}

static void SPI_CloseReceive(SPI_HANDLE_t* pSPIHandle){
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE_OFFSET);
	pSPIHandle->Rx_Length = 0;
	pSPIHandle->pRx_Buffer = NULL;
	pSPIHandle->Rx_Status = SPI_READY;
	SPI_ApplicationEventCallBack(pSPIHandle, SPI_EVENT_RX_COMPLETE);
}

static void SPI_TxEInterruptHandler(SPI_HANDLE_t* pSPIHandle){
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF_OFFSET)){
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTx_Buffer);
		pSPIHandle->Tx_Length = pSPIHandle->Tx_Length - 2;
		pSPIHandle->pRx_Buffer = pSPIHandle->pRx_Buffer + 2 ;
	}
	else{
		pSPIHandle->pSPIx->DR = *(pSPIHandle->pTx_Buffer);
		pSPIHandle->Tx_Length = pSPIHandle->Tx_Length - 1;
		pSPIHandle->pTx_Buffer = pSPIHandle->pTx_Buffer + 1;
	}

	if(!pSPIHandle->Tx_Length){
		SPI_CloseTransMission(pSPIHandle);
		SPI_ApplicationEventCallBack(pSPIHandle, SPI_EVENT_TX_COMPLETE);
	}

	return;
}

static void SPI_RxNEInterruptHandler(SPI_HANDLE_t* pSPIHandle){
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF_OFFSET)){
		*((uint16_t*)pSPIHandle->pRx_Buffer) = (uint16_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->Rx_Length = pSPIHandle->Rx_Length - 2;
		pSPIHandle->pRx_Buffer = pSPIHandle->pRx_Buffer + 2;
	}
	else{
		*(pSPIHandle->pRx_Buffer) = (uint8_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->Rx_Length = pSPIHandle->Rx_Length - 1;
		pSPIHandle->pRx_Buffer = pSPIHandle->pRx_Buffer + 1;
	}

	if(!pSPIHandle->Rx_Length){
			SPI_CloseReceive(pSPIHandle);
			SPI_ApplicationEventCallBack(pSPIHandle, SPI_EVENT_RX_COMPLETE);
	}

	return;
}

static void SPI_OverunInterruptHandler(SPI_HANDLE_t* pSPIHandle){
	/*This is to clear Overun Flag*/
	if(pSPIHandle->Tx_Status != SPI_Tx_BUSY){
		SPI_ClearOverunFlag(pSPIHandle);
	}

	SPI_ApplicationEventCallBack(pSPIHandle, SPI_EVENT_OVERUN_ERROR);
}

void SPI_IRQHandling(SPI_HANDLE_t* pSPIHandle){
	uint8_t Flag;
	uint8_t Flag_Enable;

	Flag = pSPIHandle->pSPIx->SR & (1 << SPI_SR_TXE_OFFSET);
	Flag_Enable = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE_OFFSET);

	if(Flag && Flag_Enable){
		/*This is Tx Empty Interrupt*/
		SPI_TxEInterruptHandler(pSPIHandle);
	}

	Flag = pSPIHandle->pSPIx->SR & (1 << SPI_SR_RXNE_OFFSET);
	Flag_Enable = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE_OFFSET);

	if(Flag && Flag_Enable){
		/*This is Rx Not Empty Interrupt*/
		SPI_RxNEInterruptHandler(pSPIHandle);
	}

	Flag = pSPIHandle->pSPIx->SR & (1 << SPI_SR_OVR_OFFSET);
	Flag_Enable = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE_OFFSET);

	if(Flag && Flag_Enable){
		/*This is Overun Interrupt*/
		SPI_OverunInterruptHandler(pSPIHandle);
	}
}

uint8_t SPI_SendDataWithIT(SPI_HANDLE_t* pSPIHandle, uint8_t* pTx_Buffer, uint32_t Length){
	uint8_t Status = pSPIHandle->Tx_Status;

	if(Status != SPI_Tx_BUSY){
		pSPIHandle->Tx_Length = Length;
		pSPIHandle->pTx_Buffer = pTx_Buffer;

		pSPIHandle->Tx_Status = SPI_Tx_BUSY;

		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE_OFFSET);
	}
	/*This is false because Status is not update
	return Status;*/

	return (pSPIHandle->Tx_Status);
}

uint8_t SPI_ReceiveDataWithIT(SPI_HANDLE_t* pSPIHandle, uint8_t* pRx_Buffer, uint32_t Length){
	uint8_t Status = pSPIHandle->Rx_Status;

	if(Status != SPI_Rx_BUSY){
		pSPIHandle->Rx_Length = Length;
		pSPIHandle->pRx_Buffer = pRx_Buffer;

		pSPIHandle->Rx_Status = SPI_Rx_BUSY;

		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE_OFFSET);
	}

	/*This is false because Status is not update
	return Status;*/

	return (pSPIHandle->Rx_Status);
}
