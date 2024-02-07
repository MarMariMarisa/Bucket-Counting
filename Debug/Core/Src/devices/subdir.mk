################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/devices/GPIO.c \
../Core/Src/devices/UART.c \
../Core/Src/devices/clock.c \
../Core/Src/devices/led.c 

OBJS += \
./Core/Src/devices/GPIO.o \
./Core/Src/devices/UART.o \
./Core/Src/devices/clock.o \
./Core/Src/devices/led.o 

C_DEPS += \
./Core/Src/devices/GPIO.d \
./Core/Src/devices/UART.d \
./Core/Src/devices/clock.d \
./Core/Src/devices/led.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/devices/%.o Core/Src/devices/%.su Core/Src/devices/%.cyclo: ../Core/Src/devices/%.c Core/Src/devices/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-devices

clean-Core-2f-Src-2f-devices:
	-$(RM) ./Core/Src/devices/GPIO.cyclo ./Core/Src/devices/GPIO.d ./Core/Src/devices/GPIO.o ./Core/Src/devices/GPIO.su ./Core/Src/devices/UART.cyclo ./Core/Src/devices/UART.d ./Core/Src/devices/UART.o ./Core/Src/devices/UART.su ./Core/Src/devices/clock.cyclo ./Core/Src/devices/clock.d ./Core/Src/devices/clock.o ./Core/Src/devices/clock.su ./Core/Src/devices/led.cyclo ./Core/Src/devices/led.d ./Core/Src/devices/led.o ./Core/Src/devices/led.su

.PHONY: clean-Core-2f-Src-2f-devices

