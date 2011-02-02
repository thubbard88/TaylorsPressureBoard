################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include default/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
PressureBoard4FIRM.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: PressureBoard4FIRM.elf secondary-outputs

# Tool invocations
PressureBoard4FIRM.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,PressureBoard4FIRM.map -mmcu=atmega324p -o"PressureBoard4FIRM.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

PressureBoard4FIRM.lss: PressureBoard4FIRM.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S PressureBoard4FIRM.elf  >"PressureBoard4FIRM.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: PressureBoard4FIRM.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega324p PressureBoard4FIRM.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) PressureBoard4FIRM.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
