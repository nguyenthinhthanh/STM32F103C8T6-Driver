/*
 * STM32F103C8T6_I2C_Driver.h
 *
 *  Created on: Aug 27, 2024
 *      Author: ADMINS
 */

#ifndef INC_STM32F103C8T6_I2C_DRIVER_H_
#define INC_STM32F103C8T6_I2C_DRIVER_H_

#include "STM32F103C8T6.h"

/*STRUCT*/
typedef struct{
	uint32_t I2C_SCLSpeed;
	uint32_t I2C_DeviceAddress;
	uint32_t I2C_ACKControl;
	uint32_t I2C_FMDutyCycle;
}I2C_CONFIG_t;

typedef struct{
	I2C_REG_t* pI2Cx;
	I2C_CONFIG_t IC2_Config;
}I2C_HANDLE_t;


/*MACRO I2C SLC SPEED MODE*/
#define I2C_SCL_SPEED_STANDARD_MODE		100000 		/*Up to 100Khz*/
#define I2C_SCL_SPEED_FAST_MODE			400000		/*Up to 400Khz*/

/*MACRO I2C ACK CONTROL*/
#define I2C_ACK_DIS_ENABLE		0
#define I2C_ACK_ENABLE			1

/*MACRO I2C FM DUTY CYCLE*/
#define I2C_FMDUTY_CYCLE_2		0
#define I2C_FMDUTY_CYCLE_16_9	1

/*MACRO I2C CR1 OFFSET BIT*/
#define I2C_CR1_PE_OFFSET			0
#define I2C_CR1_SMBUS_OFFSET		1
#define I2C_CR1_SMBTYPE_OFFSET		3
#define I2C_CR1_ENARP_OFFSET		4
#define I2C_CR1_ENPEC_OFFSET		5
#define I2C_CR1_ENGC_OFFSET			6
#define I2C_CR1_NOSTRETCH_OFFSET	7
#define I2C_CR1_START_OFFSET		8
#define I2C_CR1_STOP_OFFSET			9
#define I2C_CR1_ACK_OFFSET			10
#define I2C_CR1_POS_OFFSET			11
#define I2C_CR1_PEC_OFFSET			12
#define I2C_CR1_ALERT_OFFSET		13
#define I2C_CR1_SWRST_OFFSET		15

/*MACRO I2C CR2 OFFSET BIT*/
#define I2C_CR2_FREQ_OFFSET			0
#define I2C_CR2_ITERREN_OFFSET		8
#define I2C_CR2_ITEVTEN_OFFSET		9
#define I2C_CR2_ITBUFEN_OFFSET		10
#define I2C_CR2_DMAEN_OFFSET		11
#define I2C_CR2_LAST_OFFSET			12

/*MACRO I2C SR1 OFFSET BIT*/
#define I2C_SR1_SB_OFFSET			0
#define I2C_SR1_ADDR_OFFSET			1
#define I2C_SR1_BTF_OFFSET			2
#define I2C_SR1_ADD10_OFFSET		3
#define I2C_SR1_STOPF_OFFSET		4
#define I2C_SR1_RxNE_OFFSET			6
#define I2C_SR1_TxE_OFFSET			7
#define I2C_SR1_BERR_OFFSET			8
#define I2C_SR1_ARLO_OFFSET			9
#define I2C_SR1_AF_OFFSET			10
#define I2C_SR1_OVR_OFFSET			11
#define I2C_SR1_PECERR_OFFSET		12
#define I2C_SR1_TIMEOUT_OFFSET		14
#define I2C_SR1_SMB_ALERT_OFFSET	15

/*MACRO I2C SR2 OFFSET BIT*/
#define I2C_SR2_MSL_OFFSET			0
#define I2C_SR2_BUSY_OFFSET			1
#define I2C_SR2_TRA_OFFSET			2
#define I2C_SR2_GENCALL_OFFSET		4
#define I2C_SR2_SMBDE_FAULT_OFFSET	5
#define I2C_SR2_SMB_HOST_OFFSET		6
#define I2C_SR2_DUALF_OFFSET		7
#define I2C_SR2_PEC_OFFSET			8

/*MACRO I2C CCR OFFSET BIT*/
#define I2C_CCR_CRR_OFFSET			0
#define I2C_CCR_DUTY_OFFSET			14
#define I2C_CCR_FS_OFFSET			15

/*MACRO I2C FOR TRISE CALCULATE*/
#define I2C_TRISE_SM_MAX		1000		/*1000ns reference in I2C user manual*/
#define I2C_TRISE_FM_MAX		300 		/*300ns* reference in I2C user manual*/

/*I2C RESET*/
void I2C1_RESET(void);
void I2C2_RESET(void);

/*I2C FUNCTION*/
void I2C_ClkControl(I2C_REG_t* pI2Cx, uint8_t Enable);

void I2C_PeripheralControl(I2C_REG_t* pI2Cx, uint8_t Enable);

uint32_t I2C_GetPclk1Value(void);

void I2C_Init(I2C_HANDLE_t* pI2C_Handle);

void I2C_DeInit(I2C_REG_t* pI2Cx);

uint8_t I2C_GetFlagStatus(I2C_REG_t* pIC2x,uint8_t StatusOffset, uint8_t OffsetFlag);

void I2C_SetAckBit(I2C_HANDLE_t* pI2C_Handle);

/*DATA SEND AND RECEIVE FUNCTION*/
void I2C_MasterSendData(I2C_HANDLE_t* pI2C_Handle, uint8_t* pTxBuffer, uint32_t Length, uint8_t SlaveAddress);

/*INTERRUPT FUNCTION*/
void I2C_IRQPriorityConFig(uint8_t IRQNumber, uint8_t IRQPriority);

void I2C_IRQConFig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t Enable);

void I2C_ApplicationEventCallBack(I2C_HANDLE_t* pI2CHandle, uint8_t Event);

#endif /* INC_STM32F103C8T6_I2C_DRIVER_H_ */
