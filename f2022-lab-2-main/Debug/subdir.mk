################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../lab2.S 

O_SRCS += \
../autograder-FVP-Linux.o \
../autograder.o 

OBJS += \
./lab2.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.S subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Arm Assembler 6'
	armclang --target=aarch64-arm-none-eabi -g -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


