################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal/util_c.c 

CPP_SRCS += \
../src/hal/Adc.cpp \
../src/hal/CFifo.cpp \
../src/hal/Core.cpp \
../src/hal/Dac.cpp \
../src/hal/Dev.cpp \
../src/hal/Device.cpp \
../src/hal/Display.cpp \
../src/hal/DisplayDevice.cpp \
../src/hal/Eint.cpp \
../src/hal/Fifo.cpp \
../src/hal/I2C.cpp \
../src/hal/Led.cpp \
../src/hal/Periph.cpp \
../src/hal/Pio.cpp \
../src/hal/Pwm.cpp \
../src/hal/Spi.cpp \
../src/hal/Tmr.cpp \
../src/hal/Uart.cpp \
../src/hal/Usb.cpp 

OBJS += \
./src/hal/Adc.o \
./src/hal/CFifo.o \
./src/hal/Core.o \
./src/hal/Dac.o \
./src/hal/Dev.o \
./src/hal/Device.o \
./src/hal/Display.o \
./src/hal/DisplayDevice.o \
./src/hal/Eint.o \
./src/hal/Fifo.o \
./src/hal/I2C.o \
./src/hal/Led.o \
./src/hal/Periph.o \
./src/hal/Pio.o \
./src/hal/Pwm.o \
./src/hal/Spi.o \
./src/hal/Tmr.o \
./src/hal/Uart.o \
./src/hal/Usb.o \
./src/hal/util_c.o 

C_DEPS += \
./src/hal/util_c.d 

CPP_DEPS += \
./src/hal/Adc.d \
./src/hal/CFifo.d \
./src/hal/Core.d \
./src/hal/Dac.d \
./src/hal/Dev.d \
./src/hal/Device.d \
./src/hal/Display.d \
./src/hal/DisplayDevice.d \
./src/hal/Eint.d \
./src/hal/Fifo.d \
./src/hal/I2C.d \
./src/hal/Led.d \
./src/hal/Periph.d \
./src/hal/Pio.d \
./src/hal/Pwm.d \
./src/hal/Spi.d \
./src/hal/Tmr.d \
./src/hal/Uart.d \
./src/hal/Usb.d 


# Each subdirectory must supply rules for building sources it contributes
src/hal/%.o: ../src/hal/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-none-eabi-g++ -D___debug -D__StratifyOS__ -D__armv7em -I"/Users/tgil/git/StratifyAPI/include" -Os -Wall -c -mlong-calls -ffunction-sections -fomit-frame-pointer -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -U__SOFTFP__ -D__FPU_USED=1 -fno-rtti -fno-exceptions -fno-threadsafe-statics -fno-unwind-tables -fno-use-cxa-atexit -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/hal/%.o: ../src/hal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc -D___debug -D__StratifyOS__ -D__armv7em -I"/Users/tgil/git/StratifyAPI/include" -Os -Wall -c -mlong-calls -ffunction-sections -fomit-frame-pointer -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -U__SOFTFP__ -D__FPU_USED=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


