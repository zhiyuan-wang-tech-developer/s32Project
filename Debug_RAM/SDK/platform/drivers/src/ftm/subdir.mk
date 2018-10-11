################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../SDK/platform/drivers/src/ftm/ftm_common.c" \
"../SDK/platform/drivers/src/ftm/ftm_hw_access.c" \
"../SDK/platform/drivers/src/ftm/ftm_mc_driver.c" \

C_SRCS += \
../SDK/platform/drivers/src/ftm/ftm_common.c \
../SDK/platform/drivers/src/ftm/ftm_hw_access.c \
../SDK/platform/drivers/src/ftm/ftm_mc_driver.c \

OBJS_OS_FORMAT += \
./SDK/platform/drivers/src/ftm/ftm_common.o \
./SDK/platform/drivers/src/ftm/ftm_hw_access.o \
./SDK/platform/drivers/src/ftm/ftm_mc_driver.o \

C_DEPS_QUOTED += \
"./SDK/platform/drivers/src/ftm/ftm_common.d" \
"./SDK/platform/drivers/src/ftm/ftm_hw_access.d" \
"./SDK/platform/drivers/src/ftm/ftm_mc_driver.d" \

OBJS += \
./SDK/platform/drivers/src/ftm/ftm_common.o \
./SDK/platform/drivers/src/ftm/ftm_hw_access.o \
./SDK/platform/drivers/src/ftm/ftm_mc_driver.o \

OBJS_QUOTED += \
"./SDK/platform/drivers/src/ftm/ftm_common.o" \
"./SDK/platform/drivers/src/ftm/ftm_hw_access.o" \
"./SDK/platform/drivers/src/ftm/ftm_mc_driver.o" \

C_DEPS += \
./SDK/platform/drivers/src/ftm/ftm_common.d \
./SDK/platform/drivers/src/ftm/ftm_hw_access.d \
./SDK/platform/drivers/src/ftm/ftm_mc_driver.d \


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/drivers/src/ftm/ftm_common.o: ../SDK/platform/drivers/src/ftm/ftm_common.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/ftm/ftm_common.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/ftm/ftm_common.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/platform/drivers/src/ftm/ftm_hw_access.o: ../SDK/platform/drivers/src/ftm/ftm_hw_access.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/ftm/ftm_hw_access.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/ftm/ftm_hw_access.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/platform/drivers/src/ftm/ftm_mc_driver.o: ../SDK/platform/drivers/src/ftm/ftm_mc_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/ftm/ftm_mc_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/ftm/ftm_mc_driver.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


