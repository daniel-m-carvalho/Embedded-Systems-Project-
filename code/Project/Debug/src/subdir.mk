################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/lists.c \
../src/main.c \
../src/project.c 

C_DEPS += \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/lists.d \
./src/main.d \
./src/project.d 

OBJS += \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/lists.o \
./src/main.o \
./src/project.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\DRIVERS\inc" -I"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\MFRC522\inc" -I"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\Project\inc" -I"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\CMSIS_CORE_LPC17xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/cr_startup_lpc175x_6x.d ./src/cr_startup_lpc175x_6x.o ./src/crp.d ./src/crp.o ./src/lists.d ./src/lists.o ./src/main.d ./src/main.o ./src/project.d ./src/project.o

.PHONY: clean-src

