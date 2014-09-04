################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Atlas/Com.cpp \
../Atlas/Controller.cpp \
../Atlas/I2Cdev.cpp \
../Atlas/MPU6050.cpp \
../Atlas/Motor.cpp \
../Atlas/SensorManager.cpp \
../Atlas/main.cpp 

OBJS += \
./Atlas/Com.o \
./Atlas/Controller.o \
./Atlas/I2Cdev.o \
./Atlas/MPU6050.o \
./Atlas/Motor.o \
./Atlas/SensorManager.o \
./Atlas/main.o 

CPP_DEPS += \
./Atlas/Com.d \
./Atlas/Controller.d \
./Atlas/I2Cdev.d \
./Atlas/MPU6050.d \
./Atlas/Motor.d \
./Atlas/SensorManager.d \
./Atlas/main.d 


# Each subdirectory must supply rules for building sources it contributes
Atlas/%.o: ../Atlas/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


