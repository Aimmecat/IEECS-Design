################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/Adc.c \
../CODE/DA.c \
../CODE/Icm20602.c \
../CODE/Key.c \
../CODE/MCUCommunication.c \
../CODE/Util.c 

OBJS += \
./CODE/Adc.o \
./CODE/DA.o \
./CODE/Icm20602.o \
./CODE/Key.o \
./CODE/MCUCommunication.o \
./CODE/Util.o 

C_DEPS += \
./CODE/Adc.d \
./CODE/DA.d \
./CODE/Icm20602.d \
./CODE/Key.d \
./CODE/MCUCommunication.d \
./CODE/Util.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/%.o: ../CODE/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"../Libraries/wch_libraries/Core" -I"../Libraries/wch_libraries/Peripheral" -I"../Libraries/wch_libraries/Startup" -I"../Libraries/seekfree_libraries" -I"../Libraries/seekfree_peripheral" -I"../Libraries/board" -I"../CODE" -I"../USER" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

