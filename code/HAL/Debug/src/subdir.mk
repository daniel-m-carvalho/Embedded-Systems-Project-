################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/flash.c \
../src/pin.c \
../src/rit.c \
../src/rtc_hal.c \
../src/spi.c \
../src/systick.c \
../src/timer.c 

C_DEPS += \
./src/flash.d \
./src/pin.d \
./src/rit.d \
./src/rtc_hal.d \
./src/spi.d \
./src/systick.d \
./src/timer.d 

OBJS += \
./src/flash.o \
./src/pin.o \
./src/rit.o \
./src/rtc_hal.o \
./src/spi.o \
./src/systick.o \
./src/timer.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__REDLIB__ -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -I"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\HAL\inc" -I"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\CMSIS_CORE_LPC17xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/flash.d ./src/flash.o ./src/pin.d ./src/pin.o ./src/rit.d ./src/rit.o ./src/rtc_hal.d ./src/rtc_hal.o ./src/spi.d ./src/spi.o ./src/systick.d ./src/systick.o ./src/timer.d ./src/timer.o

.PHONY: clean-src

