################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../SDK/platform/drivers/src/lpspi/lpspi_hw_access.c" \
"../SDK/platform/drivers/src/lpspi/lpspi_irq.c" \
"../SDK/platform/drivers/src/lpspi/lpspi_master_driver.c" \
"../SDK/platform/drivers/src/lpspi/lpspi_shared_function.c" \
"../SDK/platform/drivers/src/lpspi/lpspi_slave_driver.c" \

C_SRCS += \
../SDK/platform/drivers/src/lpspi/lpspi_hw_access.c \
../SDK/platform/drivers/src/lpspi/lpspi_irq.c \
../SDK/platform/drivers/src/lpspi/lpspi_master_driver.c \
../SDK/platform/drivers/src/lpspi/lpspi_shared_function.c \
../SDK/platform/drivers/src/lpspi/lpspi_slave_driver.c \

OBJS_OS_FORMAT += \
./SDK/platform/drivers/src/lpspi/lpspi_hw_access.o \
./SDK/platform/drivers/src/lpspi/lpspi_irq.o \
./SDK/platform/drivers/src/lpspi/lpspi_master_driver.o \
./SDK/platform/drivers/src/lpspi/lpspi_shared_function.o \
./SDK/platform/drivers/src/lpspi/lpspi_slave_driver.o \

C_DEPS_QUOTED += \
"./SDK/platform/drivers/src/lpspi/lpspi_hw_access.d" \
"./SDK/platform/drivers/src/lpspi/lpspi_irq.d" \
"./SDK/platform/drivers/src/lpspi/lpspi_master_driver.d" \
"./SDK/platform/drivers/src/lpspi/lpspi_shared_function.d" \
"./SDK/platform/drivers/src/lpspi/lpspi_slave_driver.d" \

OBJS += \
./SDK/platform/drivers/src/lpspi/lpspi_hw_access.o \
./SDK/platform/drivers/src/lpspi/lpspi_irq.o \
./SDK/platform/drivers/src/lpspi/lpspi_master_driver.o \
./SDK/platform/drivers/src/lpspi/lpspi_shared_function.o \
./SDK/platform/drivers/src/lpspi/lpspi_slave_driver.o \

OBJS_QUOTED += \
"./SDK/platform/drivers/src/lpspi/lpspi_hw_access.o" \
"./SDK/platform/drivers/src/lpspi/lpspi_irq.o" \
"./SDK/platform/drivers/src/lpspi/lpspi_master_driver.o" \
"./SDK/platform/drivers/src/lpspi/lpspi_shared_function.o" \
"./SDK/platform/drivers/src/lpspi/lpspi_slave_driver.o" \

C_DEPS += \
./SDK/platform/drivers/src/lpspi/lpspi_hw_access.d \
./SDK/platform/drivers/src/lpspi/lpspi_irq.d \
./SDK/platform/drivers/src/lpspi/lpspi_master_driver.d \
./SDK/platform/drivers/src/lpspi/lpspi_shared_function.d \
./SDK/platform/drivers/src/lpspi/lpspi_slave_driver.d \


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/drivers/src/lpspi/lpspi_hw_access.o: ../SDK/platform/drivers/src/lpspi/lpspi_hw_access.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/lpspi/lpspi_hw_access.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/lpspi/lpspi_hw_access.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/platform/drivers/src/lpspi/lpspi_irq.o: ../SDK/platform/drivers/src/lpspi/lpspi_irq.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/lpspi/lpspi_irq.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/lpspi/lpspi_irq.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/platform/drivers/src/lpspi/lpspi_master_driver.o: ../SDK/platform/drivers/src/lpspi/lpspi_master_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/lpspi/lpspi_master_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/lpspi/lpspi_master_driver.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/platform/drivers/src/lpspi/lpspi_shared_function.o: ../SDK/platform/drivers/src/lpspi/lpspi_shared_function.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/lpspi/lpspi_shared_function.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/lpspi/lpspi_shared_function.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

SDK/platform/drivers/src/lpspi/lpspi_slave_driver.o: ../SDK/platform/drivers/src/lpspi/lpspi_slave_driver.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/lpspi/lpspi_slave_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "SDK/platform/drivers/src/lpspi/lpspi_slave_driver.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


