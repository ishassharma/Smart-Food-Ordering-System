################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LCD.c \
../source/buttons.c \
../source/i2c.c \
../source/main.c \
../source/mtb.c \
../source/screens.c \
../source/semihost_hardfault.c \
../source/statemachines.c 

C_DEPS += \
./source/LCD.d \
./source/buttons.d \
./source/i2c.d \
./source/main.d \
./source/mtb.d \
./source/screens.d \
./source/semihost_hardfault.d \
./source/statemachines.d 

OBJS += \
./source/LCD.o \
./source/buttons.o \
./source/i2c.o \
./source/main.o \
./source/mtb.o \
./source/screens.o \
./source/semihost_hardfault.o \
./source/statemachines.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\board" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\source" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\drivers" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\CMSIS" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\utilities" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/LCD.d ./source/LCD.o ./source/buttons.d ./source/buttons.o ./source/i2c.d ./source/i2c.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/screens.d ./source/screens.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/statemachines.d ./source/statemachines.o

.PHONY: clean-source

