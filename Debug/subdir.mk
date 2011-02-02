################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../Comms.c \
../SPI.c \
../SeniorDesign2Board.c \
../uart.c 

OBJS += \
./Buzzer.o \
./Comms.o \
./SPI.o \
./SeniorDesign2Board.o \
./uart.o 

C_DEPS += \
./Buzzer.d \
./Comms.d \
./SPI.d \
./SeniorDesign2Board.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega324p -DF_CPU=10000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


