################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/system/printf.c \
../Core/Src/system/syscalls.c \
../Core/Src/system/sysmem.c \
../Core/Src/system/system_stm32l4xx.c 

OBJS += \
./Core/Src/system/printf.o \
./Core/Src/system/syscalls.o \
./Core/Src/system/sysmem.o \
./Core/Src/system/system_stm32l4xx.o 

C_DEPS += \
./Core/Src/system/printf.d \
./Core/Src/system/syscalls.d \
./Core/Src/system/sysmem.d \
./Core/Src/system/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/system/%.o Core/Src/system/%.su Core/Src/system/%.cyclo: ../Core/Src/system/%.c Core/Src/system/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-system

clean-Core-2f-Src-2f-system:
	-$(RM) ./Core/Src/system/printf.cyclo ./Core/Src/system/printf.d ./Core/Src/system/printf.o ./Core/Src/system/printf.su ./Core/Src/system/syscalls.cyclo ./Core/Src/system/syscalls.d ./Core/Src/system/syscalls.o ./Core/Src/system/syscalls.su ./Core/Src/system/sysmem.cyclo ./Core/Src/system/sysmem.d ./Core/Src/system/sysmem.o ./Core/Src/system/sysmem.su ./Core/Src/system/system_stm32l4xx.cyclo ./Core/Src/system/system_stm32l4xx.d ./Core/Src/system/system_stm32l4xx.o ./Core/Src/system/system_stm32l4xx.su

.PHONY: clean-Core-2f-Src-2f-system

