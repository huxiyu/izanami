################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/common.c \
../src/iregioninfo.c \
../src/mempool.c \
../src/networkserver.c \
../src/skiplist.c 

OBJS += \
./src/common.o \
./src/iregioninfo.o \
./src/mempool.o \
./src/networkserver.o \
./src/skiplist.o 

C_DEPS += \
./src/common.d \
./src/iregioninfo.d \
./src/mempool.d \
./src/networkserver.d \
./src/skiplist.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/caojx/download/iniparser-master/src -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


