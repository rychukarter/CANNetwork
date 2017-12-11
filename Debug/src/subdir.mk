################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MPU6050.c \
../src/SD.c \
../src/SPI_MSD_Driver.c \
../src/can.c \
../src/main.c \
../src/other.c \
../src/syscalls.c \
../src/system_stm32f10x.c 

OBJS += \
./src/MPU6050.o \
./src/SD.o \
./src/SPI_MSD_Driver.o \
./src/can.o \
./src/main.o \
./src/other.o \
./src/syscalls.o \
./src/system_stm32f10x.o 

C_DEPS += \
./src/MPU6050.d \
./src/SD.d \
./src/SPI_MSD_Driver.d \
./src/can.d \
./src/main.d \
./src/other.d \
./src/syscalls.d \
./src/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DNUCLEO_F103RB -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -I"C:/ARM/workspace/SDcard/inc" -I"C:/ARM/workspace/SDcard/CMSIS/core" -I"C:/ARM/workspace/SDcard/CMSIS/device" -I"C:/ARM/workspace/SDcard/FatFs/src" -I"C:/ARM/workspace/SDcard/StdPeriph_Driver/inc" -I"C:/ARM/workspace/SDcard/Utilities/STM32F1xx-Nucleo" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


