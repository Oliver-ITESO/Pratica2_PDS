################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ADC_example.c \
../source/Convolution.c \
../source/DAC_examples.c \
../source/Delay.c \
../source/GPIO.c \
../source/main.c \
../source/semihost_hardfault.c 

OBJS += \
./source/ADC_example.o \
./source/Convolution.o \
./source/DAC_examples.o \
./source/Delay.o \
./source/GPIO.o \
./source/main.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/ADC_example.d \
./source/Convolution.d \
./source/DAC_examples.d \
./source/Delay.d \
./source/GPIO.d \
./source/main.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\PROJECTS\PDS_P2\Convolution\board" -I"C:\PROJECTS\PDS_P2\Convolution\source" -I"C:\PROJECTS\PDS_P2\Convolution\drivers" -I"C:\PROJECTS\PDS_P2\Convolution\utilities" -I"C:\PROJECTS\PDS_P2\Convolution\component\serial_manager" -I"C:\PROJECTS\PDS_P2\Convolution\component\uart" -I"C:\PROJECTS\PDS_P2\Convolution\component\lists" -I"C:\PROJECTS\PDS_P2\Convolution\CMSIS" -I"C:\PROJECTS\PDS_P2\Convolution\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


