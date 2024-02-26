################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Project
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: Project.axf

# Tool invocations
Project.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\CMSIS_CORE_LPC17xx\Debug" -L"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\HAL\Debug" -L"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\DRIVERS\Debug" -L"C:\Daniel\Faculdade\Ano_3\Semestre_5\SE\sw\MFRC522\Release" -Xlinker -Map="Project.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T Project_Debug.ld -o "Project.axf" $(OBJS) $(USER_OBJS) $(LIBS) -lMFRC522 -lDRIVERS -lHAL -lCMSIS_CORE_LPC17xx
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Project.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Project.axf"; # arm-none-eabi-objcopy -v -O binary "Project.axf" "Project.bin" ; # checksum -p LPC1769 -d "Project.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
