################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CapsuleDebugger_test.cpp \
../src/CapsuleTracker.cpp \
../src/CmdInterface.cpp \
../src/MDebugger.cpp \
../src/UMLRTDebugger.cpp 

OBJS += \
./src/CapsuleDebugger_test.o \
./src/CapsuleTracker.o \
./src/CmdInterface.o \
./src/MDebugger.o \
./src/UMLRTDebugger.o 

CPP_DEPS += \
./src/CapsuleDebugger_test.d \
./src/CapsuleTracker.d \
./src/CmdInterface.d \
./src/MDebugger.d \
./src/UMLRTDebugger.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/mojtababagherzadeh/git/MDebugger/RealTimeLibs/src" -I/Users/mojtababagherzadeh/papyrus-rt-master/git/org.eclipse.papyrus-rt/plugins/umlrt/runtime/rts/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


