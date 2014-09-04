################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SensorManager/I2Cdev.cpp \
../SensorManager/MPU6050.cpp \
../SensorManager/SensorManager.cpp \
../SensorManager/bmp180.cpp \
../SensorManager/testRaw.cpp 

OBJS += \
./SensorManager/I2Cdev.o \
./SensorManager/MPU6050.o \
./SensorManager/SensorManager.o \
./SensorManager/bmp180.o \
./SensorManager/testRaw.o 

CPP_DEPS += \
./SensorManager/I2Cdev.d \
./SensorManager/MPU6050.d \
./SensorManager/SensorManager.d \
./SensorManager/bmp180.d \
./SensorManager/testRaw.d 


# Each subdirectory must supply rules for building sources it contributes
SensorManager/%.o: ../SensorManager/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


