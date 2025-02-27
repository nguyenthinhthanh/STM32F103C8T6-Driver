#ifndef INC_STM32F103C8T6_H_
#define INC_STM32F103C8T6_H_

/*LIBRARY*/
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

/*MACRO GENRIC*/
#define ENABLE 1
#define DISENABLE 0
#define SET	ENABLE
#define RESET DISENABLE
#define GPIO_PIN_SET SET
#define GPIO_PIN_RESET RESET

/*MEMMORY*/
#define FLASH			0X80000000U  /// 64K
#define SRAM			0X20000000U  /// 20K
#define ROM 			0x1FFFF000U

/*IRQ NUMBER*/
#define IRQ_EXTI0		6
#define IRQ_EXTI1		7
#define IRQ_EXTI2		8
#define IRQ_EXTI3		9
#define IRQ_EXTI4		10
#define IRQ_EXTI9_5		23
#define IRQ_EXTI15_10	40

#define IRQ_TIM1_BRK				24
#define IRQ_TIM1_BRK_PRIORITY		31

#define IRQ_TIM1_UP					25
#define IRQ_TIM1_UP_PRIORITY		32

#define IRQ_TIM1_TRG_COM			26
#define IRQ_TIM1_TRG_COM_PRIORITY	33

#define IRQ_TIM1_CC					27
#define IRQ_TIM1_CC_PRIORITY		34

#define IRQ_TIM2			28
#define IRQ_TIM2_PRIORITY	35

#define IRQ_TIM3			29
#define IRQ_TIM3_PRIORITY	36

#define IRQ_TIM4			30
#define IRQ_TIM4_PRIORITY	37

/*PERIPHERAL*/
#define PERIPH_BASE		0X40000000U
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE 0X40010000U
#define AHBPERIPH_BASE  0X40018000U

/*APB1 PERIPHERAL*/
#define I2C1_BASEADDR	(APB1PERIPH_BASE + 0X5400)
#define I2C2_BASEADDR	(APB1PERIPH_BASE + 0X5800)

#define SPI2_BASEADDR	(APB1PERIPH_BASE + 0X3800)
#define SPI3_BASEADDR	(APB1PERIPH_BASE + 0X3C00)

#define USART2_BASEADDR	(APB1PERIPH_BASE + 0X4400)
#define USART3_BASEADDR	(APB1PERIPH_BASE + 0X4800)
#define UART4_BASEADDR	(APB1PERIPH_BASE + 0X4C00)
#define UART5_BASEADDR	(APB1PERIPH_BASE + 0X5000)

#define TIM2_BASEADDR	(APB1PERIPH_BASE + 0X0000)
#define TIM3_BASEADDR	(APB1PERIPH_BASE + 0X0400)
#define TIM4_BASEADDR	(APB1PERIPH_BASE + 0X0800)

#define TIM6_BASEADDR	(APB1PERIPH_BASE + 0X1000)
#define TIM7_BASEADDR	(APB1PERIPH_BASE + 0X1400)

/*APB2 PERIPHERAL*/
#define GPIOA_BASEADDR  (APB2PERIPH_BASE + 0X0800)
#define GPIOB_BASEADDR  (APB2PERIPH_BASE + 0X0C00)
#define GPIOC_BASEADDR  (APB2PERIPH_BASE + 0X1000)
#define GPIOD_BASEADDR  (APB2PERIPH_BASE + 0X1400)
#define GPIOE_BASEADDR  (APB2PERIPH_BASE + 0X1800)
#define GPIOF_BASEADDR  (APB2PERIPH_BASE + 0X1C00)
#define GPIOG_BASEADDR  (APB2PERIPH_BASE + 0X2000)

#define SPI1_BASEADDR	(APB2PERIPH_BASE + 0X3000)

#define USART1_BASEADDR	(APB2PERIPH_BASE + 0X3800)

#define EXTI_BASEADDR	(APB2PERIPH_BASE + 0X0400)

#define AFIO_BASEADDR	(APB2PERIPH_BASE + 0X0000)

#define TIM1_BASEADDR	(APB2PERIPH_BASE + 0X2C00)

/*AHB PERIPHERAL*/
#define RCC_BASEADDR	(0x40021000U)

/*EXTIx[3:0]: EXTIx Configuration*/
#define EXTI_PAx	0
#define EXTI_PBx	1
#define EXTI_PCx	2
#define EXTI_PDx	3
#define EXTI_PEx	4
#define EXTI_PFx	5
#define EXTI_PGx	6

/*GPIO STRUCT PERIPHERAL*/
typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_REG_t;

/*RCC STRUCT*/
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBRSTR;
	volatile uint32_t CFGR2;
}RCC_REG_t;

#define pRCC	((RCC_REG_t*) RCC_BASEADDR)

/*MACRO RCC CFGR OFFSET BIT*/
#define RCC_CFGR_SWS_OFFSET			2
#define RCC_CFGR_HPRE_OFFSET		4
#define RCC_CFGR_PPRE1_OFFSET		8

/*EXTI STRUCT*/
typedef struct{
	uint32_t volatile IMR;
	uint32_t volatile EMR;
	uint32_t volatile RTSR;
	uint32_t volatile FTSR;
	uint32_t volatile SWIER;
	uint32_t volatile PR;
}EXTI_REG_t;

#define pEXTI	((EXTI_REG_t*)EXTI_BASEADDR)

/*AFIO STRUCT*/
typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTI[4];
	volatile uint32_t MAPR2;
}AFIO_REG_t;

#define pAFIO	((AFIO_REG_t*)AFIO_BASEADDR)

/*SPI STRUCT*/
typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RX_CRCR;
	volatile uint32_t TX_CRCR;
	volatile uint32_t CFGR;
	volatile uint32_t PR;
}SPI_REG_t;

#define pSPI1	((SPI_REG_t*)SPI1_BASEADDR)
#define pSPI2	((SPI_REG_t*)SPI2_BASEADDR)
#define pSPI3	((SPI_REG_t*)SPI3_BASEADDR)

/*IC2 STRUCT*/
typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
}I2C_REG_t;

#define pI2C1	((I2C_REG_t*)I2C1_BASEADDR)
#define pI2C2	((I2C_REG_t*)I2C2_BASEADDR)

/*TIMER STRUCT*/

/*ADVANCED CONTROL TIMERS(TIM1 AND TIM8) STRUCT*/
typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}TIM_AD_REG_t;

#define pTIM1_AD		((TIM_AD_REG_t*)TIM1_BASEADDR)

/*GENERAL PURPOSE TIMERS(TIM2 TO TIM5) STRUCT*/
typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RESERVED0;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t RESERVED1;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}TIM_GP_REG_t;

#define pTIM1_GP	((TIM_GP_REG_t*)TIM1_BASEADDR)
#define pTIM2_GP	((TIM_GP_REG_t*)TIM2_BASEADDR)
#define pTIM3_GP	((TIM_GP_REG_t*)TIM3_BASEADDR)
#define pTIM4_GP	((TIM_GP_REG_t*)TIM4_BASEADDR)

/*BASIC TIMER (TIM 6 AND TIM7) STRUCT*/
typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t RESERVED0;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t RESERVED1;
	volatile uint32_t RESERVED2;
	volatile uint32_t RESERVED3;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
}TIM_BASE_REG_t;

/*BASE TIMER IS NOT AVAILABLE IN STM32F103C8T6*/
/*THIS IS GENERAL PORPUSE TIMER USING AS BASIC TIMER*/
#define pTIM2_BASE	((TIM_BASE_REG_t*)TIM2_BASEADDR)
#define pTIM3_BASE	((TIM_BASE_REG_t*)TIM3_BASEADDR)
#define pTIM4_BASE	((TIM_BASE_REG_t*)TIM4_BASEADDR)

#define pTIM6_BASE	((TIM_BASE_REG_t*)TIM6_BASEADDR)
#define pTIM7_BASE	((TIM_BASE_REG_t*)TIM7_BASEADDR)

/*MACRO POINTER STRUCT*/
#define pGPIOA ((GPIO_REG_t*)GPIOA_BASEADDR)
#define pGPIOB ((GPIO_REG_t*)GPIOB_BASEADDR)
#define pGPIOC ((GPIO_REG_t*)GPIOC_BASEADDR)
#define pGPIOD ((GPIO_REG_t*)GPIOD_BASEADDR)
#define pGPIOE ((GPIO_REG_t*)GPIOE_BASEADDR)
#define pGPIOF ((GPIO_REG_t*)GPIOF_BASEADDR)
#define pGPIOG ((GPIO_REG_t*)GPIOG_BASEADDR)

/*NVIC INTERRUPT POINTER*/

/*INTERRUPT SET ENABLE*/
#define pNVIC_ISER0		((uint32_t*)0xE000E100)
#define pNVIC_ISER1		((uint32_t*)0xE000E104)
#define pNVIC_ISER2		((uint32_t*)0xE000E108)
#define pNVIC_ISER3		((uint32_t*)0xE000E10C)
#define pNVIC_ISER4		((uint32_t*)0xE000E110)
#define pNVIC_ISER5		((uint32_t*)0xE000E114)
#define pNVIC_ISER6		((uint32_t*)0xE000E118)
#define pNVIC_ISER7		((uint32_t*)0xE000E11C)

/*INTERRUPT CLEAR ENABLE*/
#define pNVIC_ICER0		((uint32_t*)0XE000E180)
#define pNVIC_ICER1		((uint32_t*)0xE000E184)
#define pNVIC_ICER2		((uint32_t*)0xE000E188)
#define pNVIC_ICER3		((uint32_t*)0xE000E18C)
#define pNVIC_ICER4		((uint32_t*)0xE000E190)
#define pNVIC_ICER5		((uint32_t*)0xE000E194)
#define pNVIC_ICER6		((uint32_t*)0xE000E198)
#define pNVIC_ICER7		((uint32_t*)0xE000E19C)

#define pNVIC_IPR_BASEADDR	((uint32_t*)0xE000E400)

/*CLOCK ENABLE*/
#define GPIOA_CLK_EN()	(pRCC->APB2ENR |= (1 << 2))
#define GPIOB_CLK_EN()	(pRCC->APB2ENR |= (1 << 3))
#define GPIOC_CLK_EN()	(pRCC->APB2ENR |= (1 << 4))
#define GPIOD_CLK_EN()	(pRCC->APB2ENR |= (1 << 5))
#define GPIOE_CLK_EN()	(pRCC->APB2ENR |= (1 << 6))

#define AFIO_CLK_EN()	(pRCC->APB2ENR |= (1 << 0))

#define SPI1_CLK_EN()	(pRCC->APB2ENR |= (1 << 12))
#define SPI2_CLK_EN()	(pRCC->APB1ENR |= (1 << 14))
#define SPI3_CLK_EN()	(pRCC->APB1ENR |= (1 << 15))

#define I2C1_CLK_EN()	(pRCC->APB1ENR |= (1 << 21))
#define I2C2_CLK_EN()	(pRCC->APB1ENR |= (1 << 22))

#define TIM1_CLK_EN()	(pRCC->APB2ENR |= (1 << 11))
#define TIM2_CLK_EN()	(pRCC->APB1ENR |= (1 << 0))
#define TIM3_CLK_EN()	(pRCC->APB1ENR |= (1 << 1))
#define TIM4_CLK_EN()	(pRCC->APB1ENR |= (1 << 2))

#define TIM6_CLK_EN()	(pRCC->APB1ENR |= (1 << 4))
#define TIM7_CLK_EN()	(pRCC->APB1ENR |= (1 << 5))

/*CLOCK DISENABLE*/
#define GPIOA_CLK_DISEN()	(pRCC->APB2ENR &= ~(1 << 2))
#define GPIOB_CLK_DISEN()	(pRCC->APB2ENR &= ~(1 << 3))
#define GPIOC_CLK_DISEN()	(pRCC->APB2ENR &= ~(1 << 4))
#define GPIOD_CLK_DISEN()	(pRCC->APB2ENR &= ~(1 << 5))
#define GPIOE_CLK_DISEN()	(pRCC->APB2ENR &= ~(1 << 6))

#define SPI1_CLK_DISEN()	(pRCC->APB2ENR &= ~(1 << 12))
#define SPI2_CLK_DISEN()	(pRCC->APB1ENR &= ~(1 << 14))
#define SPI3_CLK_DISEN()	(pRCC->APB1ENR &= ~(1 << 15))

#define I2C1_CLK_DISEN()	(pRCC->APB1ENR &= ~(1 << 21))
#define I2C2_CLK_DISEN()	(pRCC->APB1ENR &= ~(1 << 22))

#define TIM1_CLK_DISEN()	(pRCC->APB2ENR &= ~(1 << 11))
#define TIM2_CLK_DISEN()	(pRCC->APB1ENR &= ~(1 << 0))
#define TIM3_CLK_DISEN()	(pRCC->APB1ENR &= ~(1 << 1))
#define TIM4_CLK_DISEN()	(pRCC->APB1ENR &= ~(1 << 2))

#define TIM6_CLK_DISEN()		(pRCC->APB1ENR &= ~(1 << 4))
#define TIM7_CLK_DISEN()		(pRCC->APB1ENR &= ~(1 << 5))

#endif /* INC_STM32F103C8T6_H_ */
