################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_adc.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_delay.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_dvp.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_encoder.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_exti.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_flash.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_gpio.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_pit.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_pwm.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_soft_iic.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_spi.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_timer.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_uart.c \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_usb_cdc.c 

S_UPPER_SRCS += \
C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_irq.S 

OBJS += \
./zf_driver/zf_driver_adc.o \
./zf_driver/zf_driver_delay.o \
./zf_driver/zf_driver_dvp.o \
./zf_driver/zf_driver_encoder.o \
./zf_driver/zf_driver_exti.o \
./zf_driver/zf_driver_flash.o \
./zf_driver/zf_driver_gpio.o \
./zf_driver/zf_driver_irq.o \
./zf_driver/zf_driver_pit.o \
./zf_driver/zf_driver_pwm.o \
./zf_driver/zf_driver_soft_iic.o \
./zf_driver/zf_driver_spi.o \
./zf_driver/zf_driver_timer.o \
./zf_driver/zf_driver_uart.o \
./zf_driver/zf_driver_usb_cdc.o 

S_UPPER_DEPS += \
./zf_driver/zf_driver_irq.d 

C_DEPS += \
./zf_driver/zf_driver_adc.d \
./zf_driver/zf_driver_delay.d \
./zf_driver/zf_driver_dvp.d \
./zf_driver/zf_driver_encoder.d \
./zf_driver/zf_driver_exti.d \
./zf_driver/zf_driver_flash.d \
./zf_driver/zf_driver_gpio.d \
./zf_driver/zf_driver_pit.d \
./zf_driver/zf_driver_pwm.d \
./zf_driver/zf_driver_soft_iic.d \
./zf_driver/zf_driver_spi.d \
./zf_driver/zf_driver_timer.d \
./zf_driver/zf_driver_uart.d \
./zf_driver/zf_driver_usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
zf_driver/zf_driver_adc.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_delay.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_delay.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_dvp.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_encoder.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_exti.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_flash.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_gpio.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_irq.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_irq.S
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -x assembler -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pit.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_pit.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pwm.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_iic.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_soft_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_spi.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_timer.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_timer.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_uart.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_usb_cdc.o: C:/Users/86158/Desktop/IEECS-Design/Software/IEECS_Master_ch32v307/libraries/zf_driver/zf_driver_usb_cdc.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\Libraries\doc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Core" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Ld" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Peripheral" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\sdk\Startup" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\user\inc" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_common" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_device" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\project\code" -I"C:\Users\86158\Desktop\IEECS-Design\Software\IEECS_Master_ch32v307\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
