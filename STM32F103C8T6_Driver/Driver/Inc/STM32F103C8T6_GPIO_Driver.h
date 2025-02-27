/*
 * STM32F103C8T6_GPIO_Driver.h
 *
 *  Created on: Jul 24, 2024
 *      Author: ADMINS
 */

#ifndef INC_STM32F103C8T6_GPIO_DRIVER_H_
#define INC_STM32F103C8T6_GPIO_DRIVER_H_

#include <STM32F103C8T6.h>
#include <stdbool.h>

/*STRUCT*/
typedef struct{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinConfiguration;
	//uint8_t GPIO_PinPuPdControl;
	//uint8_t GPIO_PinOPType;
	//uint8_t GPIO_PinAltFunMode;
}GPIO_PINCONFIG_t;

typedef struct{
	GPIO_REG_t* pGPIOx;
	GPIO_PINCONFIG_t GPIO_PinConFig;
}GPIO_HANDLE_t;


/*@MACRO GPIO*/

/*MACRO GPIO MODE*/
#define GPIO_MODE_IN	 	 0
#define GPIO_MODE_OUT_LOW	 2
#define GPIO_MODE_OUT_MEDIUM 1
#define GPIO_MODE_OUT_HIGH 	 3

/*DOUBLE CHECK*/
#define GPIO_MODE_IT_FT  4
#define GPIO_MODE_IT_RT  5
#define GPIO_MODE_IT_RST 6

/*MACRO GPIO OUTPUT TYPE*/
#define GPIO_OMODE_PP		0
#define GPIO_OMODE_OD		1
#define GPIO_OMODE_ALT_PP	2
#define GPIO_OMODE_ALT_OD	3

/*MACRO GPIO INPUT TYPE*/
#define GPIO_IMODE_ANALOG		0
#define GPIO_IMODE_FLOAT		1
#define GPIO_IMODE_PUPD			2
#define GPIO_IMODE_RES			3

/*IRQ NUMBER*/
#define IRQ_EXTI0		6
#define IRQ_EXTI1		7
#define IRQ_EXTI2		8
#define IRQ_EXTI3		9
#define IRQ_EXTI4		10
#define IRQ_EXTI9_5		23
#define IRQ_EXTI15_10	40

/*MACRO GPIO PIN NUMBER*/
#define GPIO_NO_0	0
#define GPIO_NO_1	1
#define GPIO_NO_2	2
#define GPIO_NO_3	3
#define GPIO_NO_4	4
#define GPIO_NO_5	5
#define GPIO_NO_6	6
#define GPIO_NO_7	7
#define GPIO_NO_8	8
#define GPIO_NO_9	9
#define GPIO_NO_10	10
#define GPIO_NO_11	11
#define GPIO_NO_12	12
#define GPIO_NO_13	13
#define GPIO_NO_14	14
#define GPIO_NO_15	15

/*HELPER FUNCTION*/
uint8_t EXTIxValue_FromPort(GPIO_REG_t* pGPIOx);

/*PERIPHERAL FUNCTION*/
void GPIO_Init(GPIO_HANDLE_t* pGPIOHandle);
void GPIO_DeInit(GPIO_REG_t* pGPIOx);
/*GPIO RESET*/
void GPIOA_RESET(void);
void GPIOB_RESET(void);
void GPIOC_RESET(void);
void GPIOD_RESET(void);
void GPIOE_RESET(void);
void AFIO_Init(void);
void AFIO_DeInit(void);
void GPIO_ClkControl(GPIO_REG_t* pGPIOx, uint8_t Enable);
uint8_t GPIO_ReadFromInputPin(GPIO_REG_t* pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_REG_t* pGPIOx);
void GPIO_WriteToOutPutPin(GPIO_REG_t* pGPIOx, uint8_t PinNumber, uint8_t Status);
void GPIO_WriteToOutPutPort(GPIO_REG_t* pGPIOx, uint16_t Value);
void GPIO_ToggleOutPutPin(GPIO_REG_t* pGPIOx, uint8_t PinNumber);

/*INTERRUPT FUNCTION*/
void GPIO_IRQPriorityConFig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQConFig(uint8_t IRQNumber, uint8_t Enable);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32F103C8T6_GPIO_DRIVER_H_ */
