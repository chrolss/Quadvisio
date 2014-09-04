################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Controller/Controller.cpp \
../Controller/test.cpp 

OBJS += \
./Controller/Controller.o \
./Controller/test.o 

CPP_DEPS += \
./Controller/Controller.d \
./Controller/test.d 


# Each subdirectory must supply rules for building sources it contributes
Controller/%.o: ../Controller/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


