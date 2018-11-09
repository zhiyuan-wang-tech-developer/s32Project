################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 48
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Generated_Code/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include SDK/platform/devices/S32K144/startup/subdir.mk
-include SDK/platform/devices/subdir.mk
-include SDK/platform/drivers/src/clock/S32K1xx/subdir.mk
-include SDK/platform/drivers/src/clock/subdir.mk
-include SDK/platform/drivers/src/edma/subdir.mk
-include SDK/platform/drivers/src/flash/subdir.mk
-include SDK/platform/drivers/src/flexcan/subdir.mk
-include SDK/platform/drivers/src/interrupt/subdir.mk
-include SDK/platform/drivers/src/lpit/subdir.mk
-include SDK/platform/drivers/src/lpspi/subdir.mk
-include SDK/platform/drivers/src/lptmr/subdir.mk
-include SDK/platform/drivers/src/lpuart/subdir.mk
-include SDK/platform/drivers/src/pins/subdir.mk
-include SDK/platform/pal/can/src/subdir.mk
-include SDK/rtos/osif/subdir.mk
-include Sources/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
AutoLivTest.elf \

EXECUTABLES_QUOTED += \
"AutoLivTest.elf" \

EXECUTABLES_OS_FORMAT += \
AutoLivTest.elf \

SECONDARY_FLASH += \
AutoLivTest.hex \

SECONDARY_FLASH_QUOTED += \
"AutoLivTest.hex" \

SECONDARY_FLASH_OS_FORMAT += \
AutoLivTest.hex \

SECONDARY_SIZE += \
AutoLivTest.siz \

SECONDARY_SIZE_QUOTED += \
"AutoLivTest.siz" \

SECONDARY_SIZE_OS_FORMAT += \
AutoLivTest.siz \


# All Target
all: warning-messages explicit-dependencies AutoLivTest.elf secondary-outputs

# Tool invocations
AutoLivTest.elf: $(OBJS) D:/AllRound/Project/AutoLivTest/Project_Settings/Linker_Files/S32K144_64_ram.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #49 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "AutoLivTest.elf" "@AutoLivTest.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

AutoLivTest.hex: $(EXECUTABLES)
	@echo 'Executing target #50 $@'
	@echo 'Invoking: Standard S32DS Create Flash Image'
	arm-none-eabi-objcopy -O ihex $(EXECUTABLES)  "AutoLivTest.hex"
	@echo 'Finished building: $@'
	@echo ' '

AutoLivTest.siz: $(EXECUTABLES)
	@echo 'Executing target #51 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=sysv --totals $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH_QUOTED) ./*/*.d ./*/*/*/*.d ./*/*/*/*/*/*.d ./*/*/*/*/*/*/*.d  ./*/*.o ./*/*/*/*.o ./*/*/*/*/*/*.o ./*/*/*/*/*/*/*.o ./*/*/*.o  $(SECONDARY_SIZE_QUOTED) $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

