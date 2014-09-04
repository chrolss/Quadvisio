################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sensors/MPU6050-Pi-Demo/I2Cdev.cpp \
../Sensors/MPU6050-Pi-Demo/MPU6050.cpp \
../Sensors/MPU6050-Pi-Demo/demo_3d.cpp \
../Sensors/MPU6050-Pi-Demo/demo_dmp.cpp \
../Sensors/MPU6050-Pi-Demo/demo_raw.cpp \
../Sensors/MPU6050-Pi-Demo/main_3d.cpp 

OBJS += \
./Sensors/MPU6050-Pi-Demo/I2Cdev.o \
./Sensors/MPU6050-Pi-Demo/MPU6050.o \
./Sensors/MPU6050-Pi-Demo/demo_3d.o \
./Sensors/MPU6050-Pi-Demo/demo_dmp.o \
./Sensors/MPU6050-Pi-Demo/demo_raw.o \
./Sensors/MPU6050-Pi-Demo/main_3d.o 

CPP_DEPS += \
./Sensors/MPU6050-Pi-Demo/I2Cdev.d \
./Sensors/MPU6050-Pi-Demo/MPU6050.d \
./Sensors/MPU6050-Pi-Demo/demo_3d.d \
./Sensors/MPU6050-Pi-Demo/demo_dmp.d \
./Sensors/MPU6050-Pi-Demo/demo_raw.d \
./Sensors/MPU6050-Pi-Demo/main_3d.d 


# Each subdirectory must supply rules for building sources it contributes
Sensors/MPU6050-Pi-Demo/%.o: ../Sensors/MPU6050-Pi-Demo/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


