################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FatFs/src/diskio.c \
../FatFs/src/ff.c 

OBJS += \
./FatFs/src/diskio.o \
./FatFs/src/ff.o 

C_DEPS += \
./FatFs/src/diskio.d \
./FatFs/src/ff.d 


# Each subdirectory must supply rules for building sources it contributes
FatFs/src/%.o: ../FatFs/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DNUCLEO_F103RB -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -I"C:/ARM/workspace/SDcard/inc" -I"C:/ARM/workspace/SDcard/CMSIS/core" -I"C:/ARM/workspace/SDcard/CMSIS/device" -I"C:/ARM/workspace/SDcard/FatFs/src" -I"C:/ARM/workspace/SDcard/StdPeriph_Driver/inc" -I"C:/ARM/workspace/SDcard/Utilities/STM32F1xx-Nucleo" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


