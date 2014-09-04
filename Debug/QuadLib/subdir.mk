################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../QuadLib/QuadCore.cpp \
../QuadLib/QuadGPIO.cpp \
../QuadLib/QuadPWM.cpp \
../QuadLib/test.cpp 

OBJS += \
./QuadLib/QuadCore.o \
./QuadLib/QuadGPIO.o \
./QuadLib/QuadPWM.o \
./QuadLib/test.o 

CPP_DEPS += \
./QuadLib/QuadCore.d \
./QuadLib/QuadGPIO.d \
./QuadLib/QuadPWM.d \
./QuadLib/test.d 


# Each subdirectory must supply rules for building sources it contributes
QuadLib/%.o: ../QuadLib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


