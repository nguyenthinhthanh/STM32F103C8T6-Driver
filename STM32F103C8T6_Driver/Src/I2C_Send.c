/*
 * I2C_Send.c
 *
 *  Created on: Sep 5, 2024
 *      Author: ADMINS
 */

#include <stdio.h>
#include <string.h>
#include "STM32F103C8T6.h"
#include "STM32F103C8T6_GPIO_Driver.h"
#include "STM32F103C8T6_I2C_Driver.h"

int main(){
	GPIO_HANDLE_t PB10_I2C2_SCL;
	GPIO_HANDLE_t PB11_I2C2_SDA;

	PB10_I2C2_SCL.pGPIOx = pGPIOB;
	PB11_I2C2_SDA.pGPIOx = pGPIOB;

	PB10_I2C2_SCL.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_10;
	PB10_I2C2_SCL.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_LOW;
	PB10_I2C2_SCL.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_ALT_OD;

	PB11_I2C2_SDA.GPIO_PinConFig.GPIO_PinNumber = GPIO_NO_11;
	PB11_I2C2_SDA.GPIO_PinConFig.GPIO_PinMode = GPIO_MODE_OUT_LOW;
	PB11_I2C2_SDA.GPIO_PinConFig.GPIO_PinConfiguration = GPIO_OMODE_ALT_OD;

	GPIO_ClkControl(pGPIOB, ENABLE);

	GPIO_Init(&PB10_I2C2_SCL);
	GPIO_Init(&PB11_I2C2_SDA);

	I2C_HANDLE_t I2C2_Handle;

	I2C2_Handle.pI2Cx = pI2C2;
	I2C2_Handle.IC2_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	I2C2_Handle.IC2_Config.I2C_SCLSpeed = I2C_SCL_SPEED_STANDARD_MODE;
	/*Do not use address which in 3.1.12 in I2C manual*/
	I2C2_Handle.IC2_Config.I2C_DeviceAddress = 0x61;
	/*This is not care*/
	I2C2_Handle.IC2_Config.I2C_FMDutyCycle = I2C_FMDUTY_CYCLE_2;

	I2C_ClkControl(pI2C2, ENABLE);

	I2C_Init(&I2C2_Handle);

	/*This address get from slave monitor*/
	uint8_t SlaveAddress = 0x68;
	char Message[] = "I am iron man";

	I2C_PeripheralControl(pI2C2, ENABLE);

	I2C_SetAckBit(&I2C2_Handle);

	//I2C_MasterSendData(&I2C2_Handle, (uint8_t*)Message, strlen(Message), SlaveAddress);

	while(1){
		I2C_MasterSendData(&I2C2_Handle, (uint8_t*)Message, strlen(Message), SlaveAddress);
		for(int i =0;i< 5000000;i++);
	}

	return 0;
}
