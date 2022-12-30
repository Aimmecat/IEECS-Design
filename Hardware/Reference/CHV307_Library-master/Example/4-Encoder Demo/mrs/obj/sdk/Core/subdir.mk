################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/86158/Desktop/IEECS-Design/Hardware/Reference/CHV307_Library-master/Example/libraries/sdk/Core/core_riscv.c 

OBJS += \
./sdk/Core/core_riscv.o 

C_DEPS += \
./sdk/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Core/core_riscv.o: C:/Users/86158/Desktop/IEECS-Design/Hardware/Reference/CHV307_Library-master/Example/libraries/sdk/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Hardware\Reference\CHV307_Library-master\Example\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Hardware\Reference\CHV307_Library-master\Example\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Hardware\Reference\CHV307_Library-master\Example\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Hardware\Reference\CHV307_Library-master\Example\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Hardware\Reference\CHV307_Library-master\Example\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Hardware\Reference\CHV307_Library-master\Example\4-Encoder Demo\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Hardware\Reference\CHV307_Library-master\Example\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Hardware\Reference\CHV307_Library-master\Example\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Hardware\Reference\CHV307_Library-master\Example\4-Encoder Demo\code" -I"C:\Users\86158\Desktop\IEECS-Design\Hardware\Reference\CHV307_Library-master\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

