################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Src/STM32F103C8T6_GPIO_Driver.c \
../Driver/Src/STM32F103C8T6_I2C_Driver.c \
../Driver/Src/STM32F103C8T6_SPI_Driver.c \
../Driver/Src/STM32F103C8T6_TIM_Driver.c 

OBJS += \
./Driver/Src/STM32F103C8T6_GPIO_Driver.o \
./Driver/Src/STM32F103C8T6_I2C_Driver.o \
./Driver/Src/STM32F103C8T6_SPI_Driver.o \
./Driver/Src/STM32F103C8T6_TIM_Driver.o 

C_DEPS += \
./Driver/Src/STM32F103C8T6_GPIO_Driver.d \
./Driver/Src/STM32F103C8T6_I2C_Driver.d \
./Driver/Src/STM32F103C8T6_SPI_Driver.d \
./Driver/Src/STM32F103C8T6_TIM_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Src/%.o Driver/Src/%.su Driver/Src/%.cyclo: ../Driver/Src/%.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"D:/STM32_Cube/My_WorkSpace/Target/STM32F103C8T6_Driver/Driver/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-Src

clean-Driver-2f-Src:
	-$(RM) ./Driver/Src/STM32F103C8T6_GPIO_Driver.cyclo ./Driver/Src/STM32F103C8T6_GPIO_Driver.d ./Driver/Src/STM32F103C8T6_GPIO_Driver.o ./Driver/Src/STM32F103C8T6_GPIO_Driver.su ./Driver/Src/STM32F103C8T6_I2C_Driver.cyclo ./Driver/Src/STM32F103C8T6_I2C_Driver.d ./Driver/Src/STM32F103C8T6_I2C_Driver.o ./Driver/Src/STM32F103C8T6_I2C_Driver.su ./Driver/Src/STM32F103C8T6_SPI_Driver.cyclo ./Driver/Src/STM32F103C8T6_SPI_Driver.d ./Driver/Src/STM32F103C8T6_SPI_Driver.o ./Driver/Src/STM32F103C8T6_SPI_Driver.su ./Driver/Src/STM32F103C8T6_TIM_Driver.cyclo ./Driver/Src/STM32F103C8T6_TIM_Driver.d ./Driver/Src/STM32F103C8T6_TIM_Driver.o ./Driver/Src/STM32F103C8T6_TIM_Driver.su

.PHONY: clean-Driver-2f-Src

