################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/sdk/Startup/system_ch32v30x.c 

S_UPPER_SRCS += \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/sdk/Startup/startup_ch32v30x.S 

OBJS += \
./sdk/Startup/startup_ch32v30x.o \
./sdk/Startup/system_ch32v30x.o 

S_UPPER_DEPS += \
./sdk/Startup/startup_ch32v30x.d 

C_DEPS += \
./sdk/Startup/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Startup/startup_ch32v30x.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/sdk/Startup/startup_ch32v30x.S
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -x assembler -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Startup/system_ch32v30x.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/sdk/Startup/system_ch32v30x.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

