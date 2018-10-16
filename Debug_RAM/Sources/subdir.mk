################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/adc.c" \
"../Sources/dac.c" \
"../Sources/main.c" \
"../Sources/systemRunFsm.c" \

C_SRCS += \
../Sources/adc.c \
../Sources/dac.c \
../Sources/main.c \
../Sources/systemRunFsm.c \

OBJS_OS_FORMAT += \
./Sources/adc.o \
./Sources/dac.o \
./Sources/main.o \
./Sources/systemRunFsm.o \

C_DEPS_QUOTED += \
"./Sources/adc.d" \
"./Sources/dac.d" \
"./Sources/main.d" \
"./Sources/systemRunFsm.d" \

OBJS += \
./Sources/adc.o \
./Sources/dac.o \
./Sources/main.o \
./Sources/systemRunFsm.o \

OBJS_QUOTED += \
"./Sources/adc.o" \
"./Sources/dac.o" \
"./Sources/main.o" \
"./Sources/systemRunFsm.o" \

C_DEPS += \
./Sources/adc.d \
./Sources/dac.d \
./Sources/main.d \
./Sources/systemRunFsm.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/adc.o: ../Sources/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #33 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/adc.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/dac.o: ../Sources/dac.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/dac.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/dac.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/systemRunFsm.o: ../Sources/systemRunFsm.c
	@echo 'Building file: $<'
	@echo 'Executing target #36 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/systemRunFsm.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "Sources/systemRunFsm.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


