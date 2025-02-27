/*
 * STM32F103C8T6_TIM_Driver.h
 *
 *  Created on: Sep 8, 2024
 *      Author: ADMINS
 */

#ifndef INC_STM32F103C8T6_TIM_DRIVER_H_
#define INC_STM32F103C8T6_TIM_DRIVER_H_

#include "STM32F103C8T6.h"

/*MACRO FOR TIMER*/
#define TIM_NUMBER_CHANNEL					4

/*STRUCT*/

/*STRUCT FOR TIMER MODE CONFIG*/

/*STRUCT TIMER INPUT CAPTURE MODE CONFIG*/

typedef struct
{
  uint8_t Channel;
  uint8_t Interrupt;	/*Enable or Disable*/
  uint8_t  Polarity;  /*!< This parameter can be a value of @ref TIM_INPUT_CAPTURE_POLARITY*/
  uint8_t Selection;  /*!< This parameter can be a value of @ref TIM_INPUT_CAPTURE_SELECTION */
  uint8_t Filter;     /*!< This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */
						/*0000: No filter, sampling is done at fDTS
						0001: fSAMPLING=fCK_INT, N=2
						0010: fSAMPLING=fCK_INT, N=4
						0011: fSAMPLING=fCK_INT, N=8
						0100: fSAMPLING=fDTS/2, N=6
						0101: fSAMPLING=fDTS/2, N=8
						0110: fSAMPLING=fDTS/4, N=6
						0111: fSAMPLING=fDTS/4, N=8
						1000: fSAMPLING=fDTS/8, N=6
						1001: fSAMPLING=fDTS/8, N=8
						1010: fSAMPLING=fDTS/16, N=5
						1011: fSAMPLING=fDTS/16, N=6
						1100: fSAMPLING=fDTS/16, N=8
						1101: fSAMPLING=fDTS/32, N=5
						1110: fSAMPLING=fDTS/32, N=6
						1111: fSAMPLING=fDTS/32, N=8*/
  uint8_t Prescaler;  /*!< This parameter can be a value of @ref TIM_INPUT_CAPTURE_PRESCALER */
} TIM_IC_CONFIG_t;

typedef struct{

}TIM_AD_CONFIG_t;

typedef struct{
	uint8_t CounterMode;		/*@ref: TIM_COUNTER_MODE_x*/

	uint8_t AutoReLoadPreload;	 /*ARPE: Auto-reload preload enable
	 	 	 	 	 	 	 	 0: TIMx_ARR register is not buffered.
								 1: TIMx_ARR register is buffered.*/
	uint8_t ClockDivison;			/*@ref: TIM_CLOCK_DIVISION_DIVx*/

	uint16_t Prescaler;
	uint16_t CounterPeriod;
}TIM_GP_CONFIG_t;

typedef struct{
	TIM_GP_REG_t* pTIMx;
	TIM_GP_CONFIG_t TIM_Config;
}TIM_GP_HANDLE_t;

typedef struct{
	uint8_t CounterMode;		/*@ref: TIM_COUNTER_MODE_x*/

	uint8_t AutoReLoadPreload;	 /*ARPE: Auto-reload preload enable
	 	 	 	 	 	 	 	 0: TIMx_ARR register is not buffered.
								 1: TIMx_ARR register is buffered.*/
	uint8_t MasterMode;			/*@ref: TIM_MASTER_MODE_x*/
	uint8_t OnePluseMode;
	uint16_t Prescaler;
	uint16_t CounterPeriod;

}TIM_BASE_CONFIG_t;

typedef struct{
	TIM_BASE_REG_t* pTIMx;
	TIM_BASE_CONFIG_t TIM_Config;

}TIM_BASE_HANDLE_t;


/*MACRO FOR TIMER GP,AD TIMER MODE*/
#define TIM_TIMER_MODE_RESET				-1
#define TIM_TIMER_MODE_INPUT_CAPTURE		0
#define TIM_TIMER_MODE_PWM_INPUT_CAPTURE	1
#define TIM_TIMER_MODE_FORCED_OUTPUT		2
#define TIM_TIMER_MODE_OUTPUT_COMPARE		3
#define TIM_TIMER_MODE_PWM					4
#define TIM_TIMER_MODE_ONEPLUSE				5
#define TIM_TIMER_MODE_ENCODER				6

/*MACRO FOR TIMER COUNTER MODE*/
#define TIM_COUNTER_MODE_UP						0
#define TIM_COUNTER_MODE_DOWN					1
#define TIM_COUNTER_MODE_CENTER_ALIGNED1		2
#define TIM_COUNTER_MODE_CENTER_ALIGNED2		3
#define TIM_COUNTER_MODE_CENTER_ALIGNED3		4

/*MACRO FOR TIMER COUNTER CENTER ALIGNED MODE */
#define	TIM_CENTER_ALIGNED1_MODE_BITS			1
#define TIM_CENTER_ALIGNED2_MODE_BITS			2
#define TIM_CENTER_ALIGNED3_MODE_BITS			3

/*MACRO FOR AUTO RELOAD PRELOAD*/
#define TIM_AUTO_RELOAD_PRELOAD_DISENABLE	0
#define TIM_AUTO_RELOAD_PRELOAD_ENABLE		1

/*MACRO FOR UPDATE REQUEST SOURCE*/
#define TIM_UPDATE_REQUEST_SOURCE_DISABLE	0
#define TIM_UPDATE_REQUEST_SOURCE_ENABLE	1

/*MACRO FOR MASTER MODE TRIGGER OUTPUT */
#define TIM_MASTER_MODE_RESET			0
#define TIM_MASTER_MODE_ENABLE			1
#define TIM_MASTER_MODE_UPDATE			2

/*MACRO FOR ONE PLUSE MODE*/
#define TIM_ONEPLUSE_MODE_DISENABLE			0
#define TIM_ONEPLUSE_MODE_ENABLE			1

/*MACRO FOR INPUT CAPTURE PRESCALER*/
#define TIM_INPUT_CAPTURE_PRESCALER_DIV1	0
#define TIM_INPUT_CAPTURE_PRESCALER_DIV2	1
#define TIM_INPUT_CAPTURE_PRESCALER_DIV4	2
#define TIM_INPUT_CAPTURE_PRESCALER_DIV8	3

/*MACRO FOR INPUT CAPTURE POLARITY*/
#define TIM_INPUT_CAPTURE_POLARITY_RISING		0
#define TIM_INPUT_CAPTURE_POLARITY_FALLING		1
#define TIM_INPUT_CAPTURE_POLARITY_BOTH_EDGE	2	/*(TIM_CCER_CC1P | TIM_CCER_CC1NP)*/

/////////*BEGIN MACRO FOR CAPTURE/COMPARE SELECTION*///////////
/*MACRO FOR OUTPUT COMPARE SELECTION*/
#define TIM_OUTPUT_COMPARE_SELECTION			0

/*MACRO FOR INPUT CAPTURE SELECTION*/
#define TIM_INPUT_CAPTURE_SELECTION_DIRECT_TI	1
#define TIM_INPUT_CAPTURE_SELECTION_INDIRECT_TI	2
#define TIM_INPUT_CAPTURE_SELECTION_TRC			3

/////////*END MACRO FOR CAPTURE/COMPARE SELECTION*///////////

/*MACRO FOR CLOCK DIVISION*/
#define TIM_CLOCK_DIVISION_DIV1					0
#define TIM_CLOCK_DIVISION_DIV2					1
#define TIM_CLOCK_DIVISION_DIV4					2

/*MACRO FOR EVENT INTERRUPT FLAGS*/
#define TIM_UPDATE_INTERRUPT_FLAGS		0
#define TIM_CC1_INTERRUPT_FLAGS			1
#define TIM_CC2_INTERRUPT_FLAGS			2
#define TIM_CC3_INTERRUPT_FLAGS			3
#define TIM_CC4_INTERRUPT_FLAGS			4
#define TIM_TRIGGER_INTERRUPT_FLAGS		6

/*MACRO FOR TIMx_SR FLAGS (OFFSET)*/
#define TIM_TIMx_SR_UIF_FLAG			0
#define TIM_TIMx_SR_CC1IF_FLAG			1
#define TIM_TIMx_SR_CC2IF_FLAG			2
#define TIM_TIMx_SR_CC3IF_FLAG			3
#define TIM_TIMx_SR_CC4IF_FLAG			4

/*MACRO FOR BASE TIMx_CR1 OFFSET BITS*/
#define TIM_TIMx_CR1_CEN_OFFSET					0
#define TIM_TIMx_CR1_UDIS_OFFSET				1
#define TIM_TIMx_CR1_URS_OFFSET					2
#define TIM_TIMx_CR1_OPM_OFFSET					3
#define TIM_TIMx_CR1_ARPE_OFFSET				7

/*MACRO FOR GENERAL PURPOSE TIMx_CR1 OFFSET BITS*/
#define TIM_TIMx_CR1_DIR_OFFSET					4
#define TIM_TIMx_CR1_CMS_OFFSET					5
#define TIM_TIMx_CR1_CKD_OFFSET					8

/*MACRO FOR BASE TIMx_CR2 OFFSET BITS*/
#define TIM_TIMx_CR2_MMS_OFFSET					4

/*MACRO FOR BASE TIMx_EGR OFFSET BITS*/
#define TIM_TIMx_EGR_UG_OFFSET					0

/*MACRO FOR BASE TIMx_PSC OFFSET BITS*/
#define TIM_TIMx_PSC_OFFSET						0

/*MACRO FOR BASE TIMx_ARR OFFSET BITS*/
#define TIM_TIMx_ARR_OFFSET						0

/*MACRO FOR BASE TIMx_DIER OFFSET BITS*/
#define TIM_TIMx_DIER_UIE_OFFSET				0
#define TIM_TIMx_DIER_CC1IE_OFFSET				1
#define TIM_TIMx_DIER_CC2IE_OFFSET				2
#define TIM_TIMx_DIER_CC3IE_OFFSET				3
#define TIM_TIMx_DIER_CC4IE_OFFSET				4
#define TIM_TIMx_DIER_TIE_OFFSET				6
#define TIM_TIMx_DIER_UDE_OFFSET				8

/*MACRO FOR BASE TIMx_SR OFFSET BITS*/
#define TIM_TIMx_SR_UIF_OFFSET					0

/*MACRO FOR GENERAL AND ADVANCE TIMx_CCMR1 OFFSET BITS*/
#define TIM_TIMx_CCMR1_CC1S_OFFSET			0
#define TIM_TIMx_CCMR1_CC2S_OFFSET			8

/*TIMx_CCMR1 INPUT CAPTURE OFFSET BITS*/
#define TIM_TIMx_CCMR1_IC_IC1PSC_OFFSET		2
#define TIM_TIMx_CCMR1_IC_IC1F_OFFSET		4
#define TIM_TIMx_CCMR1_IC_IC2PSC_OFFSET		10
#define TIM_TIMx_CCMR1_IC_IC2F_OFFSET		12

/*TIMx_CCMR2 INPUT CAPTURE OFFSET BITS*/
#define TIM_TIMx_CCMR2_IC_IC3PSC_OFFSET		2
#define TIM_TIMx_CCMR2_IC_IC3F_OFFSET		4
#define TIM_TIMx_CCMR2_IC_IC4PSC_OFFSET		10
#define TIM_TIMx_CCMR2_IC_IC4F_OFFSET		12

/*TIM RESET*/
void TIM1_RESET(void);
void TIM2_RESET(void);
void TIM3_RESET(void);

/*TIMER FUNCTION*/

/*TIMER RESET*/
void TIM1_RESET(void);
void TIM2_RESET(void);
void TIM3_RESET(void);
void TIM4_RESET(void);

void TIM6_RESET(void);
void TIM7_RESET(void);

/*TIMER GET DIRECTION COUNTER FOR GENERAL AND ADVANCE*/
uint8_t TIM_Advance_GetDirectCounter(TIM_AD_REG_t* pTIMx);

uint8_t TIM_General_GetDirectCounter(TIM_GP_REG_t* pTIMx);

/*TIMER CLEAR UPADTE INTERRUPT FLAG*/
void TIM_Advance_ClearUpdateInterruptFlag(TIM_AD_REG_t* pTIMx);

void TIM_Gerenal_ClearUpdateInterruptFlag(TIM_GP_REG_t* pTIMx);

void TIM_Base_ClearUpdateInterruptFlag(TIM_BASE_REG_t* pTIMx);

/*INTERRUPT FUNCTION*/
void TIM_IRQPriorityConFig(uint8_t IRQNumber, uint8_t IRQPriority);

void TIM_IRQConFig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t Enable);

/*TIMER GENERAL PURPOSE FUNCTION*/
void TIM_General_ClkControl(TIM_GP_REG_t* pTIMx, uint8_t Enable);

void TIM_General_Init(TIM_GP_HANDLE_t* pTIM_Handle);

void TIM_General_DeInit(TIM_GP_REG_t* pTIMx);

void TIM_General_CounterEnable(TIM_GP_REG_t* pTIMx, uint8_t Enable);

void TIM_General_UpdateGeneration(TIM_GP_REG_t* pTIMx);

void TIM_General_UpdateRequestSource(TIM_GP_REG_t* pTIMx, uint8_t Enable);

void TIM_General_UpdateInterruptControl(TIM_GP_REG_t* pTIMx, uint8_t Enable);

void TIM_General_EventInterruptControl(TIM_GP_REG_t* pTIMx, uint16_t Flag, uint8_t Enable);

void TIM_General_ClearInterrupttFlag(TIM_GP_REG_t* pTIMx, uint16_t Flag);

void TIM_General_Start(TIM_GP_REG_t* pTIMx);

void TIM_General_Stop(TIM_GP_REG_t* pTIMx);

/*INPUT CAPTURE FUNCTION*/
void TIM_General_IC_Init(TIM_GP_HANDLE_t* pTIM_Handle, TIM_IC_CONFIG_t IC_Config);

void TIM_General_IC_DeInit(TIM_GP_REG_t* pTIMx);

void TIM_General_IC_Start(TIM_GP_HANDLE_t* pTIM_Handle, uint8_t Channel);

void TIM_General_IC_Start_IT(TIM_GP_HANDLE_t* pTIM_Handle, uint8_t Channel);

void TIM_General_IC_FilterConfig(TIM_GP_REG_t* pTIMx, uint8_t Channel, uint8_t Selection, uint8_t Filter);

/*TIMER BASE FUNCTION*/
void TIM_Base_ClkControl(TIM_BASE_REG_t* pTIMx, uint8_t Enable);

void TIM_Base_Init(TIM_BASE_HANDLE_t* pTIM_Handle);

void TIM_Base_DeInit(TIM_BASE_REG_t* pTIMx);

void TIM_Base_CounterEnable(TIM_BASE_REG_t* pTIMx, uint8_t Enable);

void TIM_Base_UpdateInterruptControl(TIM_BASE_REG_t* pTIMx, uint8_t Enable);

void TIM_Base_UpdateEventDisable(TIM_BASE_REG_t* pTIMx);

void TIM_Base_MasterModeSelection(TIM_BASE_REG_t* pTIMx, uint8_t MasterMode);

void TIM_Base_UpdateGeneration(TIM_BASE_REG_t* pTIMx);

void TIM_Base_UpdateRequestSource(TIM_BASE_REG_t* pTIMx, uint8_t Enable);

uint16_t TIM_Base_GetCounterValue(TIM_BASE_REG_t* pTIMx);

void TIM_Base_IRQHandler(TIM_BASE_REG_t* pTIMx);

void TIM_Base_Start(TIM_BASE_HANDLE_t* pTIM_Handle);

void TIM_Base_Start_IT(TIM_BASE_HANDLE_t* pTIM_Handle, uint8_t IRQNumber, uint8_t IRQPriority);

#endif /* INC_STM32F103C8T6_TIM_DRIVER_H_ */
