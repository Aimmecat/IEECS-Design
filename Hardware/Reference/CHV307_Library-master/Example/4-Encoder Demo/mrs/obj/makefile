################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include zf_driver/subdir.mk
-include zf_device/subdir.mk
-include zf_common/subdir.mk
-include user_c/subdir.mk
-include sdk/Startup/subdir.mk
-include sdk/Peripheral/subdir.mk
-include sdk/Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
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
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
4-Encoder\ Demo.hex \

SECONDARY_LIST += \
4-Encoder\ Demo.lst \

SECONDARY_SIZE += \
4-Encoder\ Demo.siz \


# All Target
all: 4-Encoder\ Demo.elf secondary-outputs

# Tool invocations
4-Encoder\ Demo.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -T "C:\Users\86158\Desktop\IEECS-Design\Hardware\Reference\CHV307_Library-master\Example\libraries\sdk\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -Wl,-Map,"4-Encoder Demo.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -o "4-Encoder Demo.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
4-Encoder\ Demo.hex: 4-Encoder\ Demo.elf
	@	riscv-none-embed-objcopy -O ihex "4-Encoder Demo.elf"  "4-Encoder Demo.hex"
	@	@
4-Encoder\ Demo.lst: 4-Encoder\ Demo.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "4-Encoder Demo.elf" > "4-Encoder Demo.lst"
	@	@
4-Encoder\ Demo.siz: 4-Encoder\ Demo.elf
	@	riscv-none-embed-size --format=berkeley "4-Encoder Demo.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) "4-Encoder Demo.elf"
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
