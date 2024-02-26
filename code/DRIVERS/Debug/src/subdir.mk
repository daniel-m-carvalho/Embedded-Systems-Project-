################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/delay.c \
../src/encoder.c \
../src/flash_writer.c \
../src/lcd.c \
../src/led.c \
../src/mfrc522_func.c \
../src/rtc.c 

C_DEPS += \
./src/delay.d \
./src/encoder.d \
./src/flash_writer.d \
./src/lcd.d \
./src/led.d \
./src/mfrc522_func.d \
./src/rtc.d 

OBJS += \
./src/delay.o \
./src/encoder.o \
./src/flash_writer.o \
./src/lcd.o \
./src/led.o \
./src/mfrc522_func.o \
./src/rtc.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__REDLIB__ -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -I"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\DRIVERS\inc" -I"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\MFRC522\inc" -I"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\CMSIS_CORE_LPC17xx\inc" -I"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\HAL\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/delay.d ./src/delay.o ./src/encoder.d ./src/encoder.o ./src/flash_writer.d ./src/flash_writer.o ./src/lcd.d ./src/lcd.o ./src/led.d ./src/led.o ./src/mfrc522_func.d ./src/mfrc522_func.o ./src/rtc.d ./src/rtc.o

.PHONY: clean-src

