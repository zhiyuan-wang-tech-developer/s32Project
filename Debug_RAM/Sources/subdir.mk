################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/adc.c" \
"../Sources/can_bus.c" \
"../Sources/dac.c" \
"../Sources/main.c" \
"../Sources/systemRunFsm.c" \

C_SRCS += \
../Sources/adc.c \
../Sources/can_bus.c \
../Sources/dac.c \
../Sources/main.c \
../Sources/systemRunFsm.c \

C_DEPS_QUOTED += \
"./Sources/adc.d" \
"./Sources/can_bus.d" \
"./Sources/dac.d" \
"./Sources/main.d" \
"./Sources/systemRunFsm.d" \

OBJS_QUOTED += \
"./Sources/adc.o" \
"./Sources/can_bus.o" \
"./Sources/dac.o" \
"./Sources/main.o" \
"./Sources/systemRunFsm.o" \

C_DEPS += \
./Sources/adc.d \
./Sources/can_bus.d \
./Sources/dac.d \
./Sources/main.d \
./Sources/systemRunFsm.d \

OBJS_OS_FORMAT += \
./Sources/adc.o \
./Sources/can_bus.o \
./Sources/dac.o \
./Sources/main.o \
./Sources/systemRunFsm.o \

OBJS += \
./Sources/adc.o \
./Sources/can_bus.o \
./Sources/dac.o \
./Sources/main.o \
./Sources/systemRunFsm.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/adc.o: ../Sources/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #41 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/adc.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/can_bus.o: ../Sources/can_bus.c
	@echo 'Building file: $<'
	@echo 'Executing target #42 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/can_bus.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/can_bus.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/dac.o: ../Sources/dac.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/dac.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/dac.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #44 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/systemRunFsm.o: ../Sources/systemRunFsm.c
	@echo 'Building file: $<'
	@echo 'Executing target #45 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/systemRunFsm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/systemRunFsm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


