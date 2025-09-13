################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bitmapimage.c \
../Core/Src/delay.c \
../Core/Src/fonts.c \
../Core/Src/glcd12864b_driver.c \
../Core/Src/glcd12864b_parallel.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/screens.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c 

OBJS += \
./Core/Src/bitmapimage.o \
./Core/Src/delay.o \
./Core/Src/fonts.o \
./Core/Src/glcd12864b_driver.o \
./Core/Src/glcd12864b_parallel.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/screens.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o 

C_DEPS += \
./Core/Src/bitmapimage.d \
./Core/Src/delay.d \
./Core/Src/fonts.d \
./Core/Src/glcd12864b_driver.d \
./Core/Src/glcd12864b_parallel.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/screens.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/bitmapimage.cyclo ./Core/Src/bitmapimage.d ./Core/Src/bitmapimage.o ./Core/Src/bitmapimage.su ./Core/Src/delay.cyclo ./Core/Src/delay.d ./Core/Src/delay.o ./Core/Src/delay.su ./Core/Src/fonts.cyclo ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/glcd12864b_driver.cyclo ./Core/Src/glcd12864b_driver.d ./Core/Src/glcd12864b_driver.o ./Core/Src/glcd12864b_driver.su ./Core/Src/glcd12864b_parallel.cyclo ./Core/Src/glcd12864b_parallel.d ./Core/Src/glcd12864b_parallel.o ./Core/Src/glcd12864b_parallel.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/screens.cyclo ./Core/Src/screens.d ./Core/Src/screens.o ./Core/Src/screens.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su

.PHONY: clean-Core-2f-Src

