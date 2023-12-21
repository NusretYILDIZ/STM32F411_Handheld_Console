################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/STM32_Handheld_Console/input/input_driver.c 

OBJS += \
./Core/STM32_Handheld_Console/input/input_driver.o 

C_DEPS += \
./Core/STM32_Handheld_Console/input/input_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/STM32_Handheld_Console/input/%.o Core/STM32_Handheld_Console/input/%.su Core/STM32_Handheld_Console/input/%.cyclo: ../Core/STM32_Handheld_Console/input/%.c Core/STM32_Handheld_Console/input/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/NusretY_Official/STM32CubeIDE/workspace_1.13.1/STM32 Handheld Console/Core/STM32_Handheld_Console" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-STM32_Handheld_Console-2f-input

clean-Core-2f-STM32_Handheld_Console-2f-input:
	-$(RM) ./Core/STM32_Handheld_Console/input/input_driver.cyclo ./Core/STM32_Handheld_Console/input/input_driver.d ./Core/STM32_Handheld_Console/input/input_driver.o ./Core/STM32_Handheld_Console/input/input_driver.su

.PHONY: clean-Core-2f-STM32_Handheld_Console-2f-input

