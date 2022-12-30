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
-include code/subdir.mk
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
IEECS_Master_ch32v307.hex \

SECONDARY_LIST += \
IEECS_Master_ch32v307.lst \

SECONDARY_SIZE += \
IEECS_Master_ch32v307.siz \


# All Target
all: IEECS_Master_ch32v307.elf secondary-outputs

# Tool invocations
IEECS_Master_ch32v307.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -T "C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -Wl,-Map,"IEECS_Master_ch32v307.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -o "IEECS_Master_ch32v307.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
IEECS_Master_ch32v307.hex: IEECS_Master_ch32v307.elf
	@	riscv-none-embed-objcopy -O ihex "IEECS_Master_ch32v307.elf"  "IEECS_Master_ch32v307.hex"
	@	@
IEECS_Master_ch32v307.lst: IEECS_Master_ch32v307.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "IEECS_Master_ch32v307.elf" > "IEECS_Master_ch32v307.lst"
	@	@
IEECS_Master_ch32v307.siz: IEECS_Master_ch32v307.elf
	@	riscv-none-embed-size --format=berkeley "IEECS_Master_ch32v307.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) IEECS_Master_ch32v307.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
