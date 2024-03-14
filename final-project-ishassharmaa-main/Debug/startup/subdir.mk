################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mkl25z4.c 

C_DEPS += \
./startup/startup_mkl25z4.d 

OBJS += \
./startup/startup_mkl25z4.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\board" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\source" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\drivers" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\CMSIS" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\utilities" -I"C:\Users\Isha Sharma\Documents\MCUXpressoIDE_11.6.0_8187\workspace696969\final_project_attempt1\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-startup

clean-startup:
	-$(RM) ./startup/startup_mkl25z4.d ./startup/startup_mkl25z4.o

.PHONY: clean-startup

