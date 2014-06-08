#ifndef sensorHub_H_
#define sensorHub_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

class sensorHub
{
public:
	sensorHub();
	std::string getAllData();
    std::string getDataMPU();    
private:
    extern void initializeMPU();
    extern bool dmpReady;
    extern uint8_t mpuIntStatus;
    extern uint8_t devStatus;
    extern uint16_t packetSize;
    extern uint16_t fifoCount;
    extern uint8_t fifoBuffer[64];
    extern MPU6050 mpu;
    extern Quaternion q;
    extern VectorInt16 aa;
    extern VectorInt16 aaReal;
    extern VectorInt16 aaWorld;
    extern VectorFloat gravity;
    extern float euler[3];
    extern float ypr[3];
};

#endif /* sensorHub */
