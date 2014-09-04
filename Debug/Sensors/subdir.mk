################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sensors/adxl345.cpp \
../Sensors/bmp085.cpp \
../Sensors/calchmc.cpp \
../Sensors/hmc5883l.cpp \
../Sensors/l3g4200d.cpp \
../Sensors/main.cpp \
../Sensors/mpu6050.cpp \
../Sensors/sensorHub.cpp \
../Sensors/sensors.cpp 

OBJS += \
./Sensors/adxl345.o \
./Sensors/bmp085.o \
./Sensors/calchmc.o \
./Sensors/hmc5883l.o \
./Sensors/l3g4200d.o \
./Sensors/main.o \
./Sensors/mpu6050.o \
./Sensors/sensorHub.o \
./Sensors/sensors.o 

CPP_DEPS += \
./Sensors/adxl345.d \
./Sensors/bmp085.d \
./Sensors/calchmc.d \
./Sensors/hmc5883l.d \
./Sensors/l3g4200d.d \
./Sensors/main.d \
./Sensors/mpu6050.d \
./Sensors/sensorHub.d \
./Sensors/sensors.d 


# Each subdirectory must supply rules for building sources it contributes
Sensors/%.o: ../Sensors/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


