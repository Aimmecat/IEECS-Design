################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/Beep.c \
../CODE/Data.c \
../CODE/Encoder.c \
../CODE/Key.c \
../CODE/MCUCommunication.c \
../CODE/Menu.c \
../CODE/Motor.c \
../CODE/PID.c \
../CODE/Robot_Communite.c \
../CODE/Style.c \
../CODE/Util.c 

OBJS += \
./CODE/Beep.o \
./CODE/Data.o \
./CODE/Encoder.o \
./CODE/Key.o \
./CODE/MCUCommunication.o \
./CODE/Menu.o \
./CODE/Motor.o \
./CODE/PID.o \
./CODE/Robot_Communite.o \
./CODE/Style.o \
./CODE/Util.o 

C_DEPS += \
./CODE/Beep.d \
./CODE/Data.d \
./CODE/Encoder.d \
./CODE/Key.d \
./CODE/MCUCommunication.d \
./CODE/Menu.d \
./CODE/Motor.d \
./CODE/PID.d \
./CODE/Robot_Communite.d \
./CODE/Style.d \
./CODE/Util.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/%.o: ../CODE/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"../Libraries/wch_libraries/Core" -I"../Libraries/wch_libraries/Peripheral" -I"../Libraries/wch_libraries/Startup" -I"../Libraries/seekfree_libraries" -I"../Libraries/seekfree_peripheral" -I"../Libraries/board" -I"../CODE" -I"../USER" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

