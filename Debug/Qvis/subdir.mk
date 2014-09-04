################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Qvis/controller.cpp \
../Qvis/glwidget.cpp \
../Qvis/layout.cpp \
../Qvis/main.cpp \
../Qvis/moc_controller.cpp \
../Qvis/moc_glwidget.cpp \
../Qvis/moc_layout.cpp \
../Qvis/model.cpp 

OBJS += \
./Qvis/controller.o \
./Qvis/glwidget.o \
./Qvis/layout.o \
./Qvis/main.o \
./Qvis/moc_controller.o \
./Qvis/moc_glwidget.o \
./Qvis/moc_layout.o \
./Qvis/model.o 

CPP_DEPS += \
./Qvis/controller.d \
./Qvis/glwidget.d \
./Qvis/layout.d \
./Qvis/main.d \
./Qvis/moc_controller.d \
./Qvis/moc_glwidget.d \
./Qvis/moc_layout.d \
./Qvis/model.d 


# Each subdirectory must supply rules for building sources it contributes
Qvis/%.o: ../Qvis/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


