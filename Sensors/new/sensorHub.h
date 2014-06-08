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
	void initializeMPU();
    
private:
    bool dmpReady;
    uint8_t mpuIntStatus;
    uint8_t devStatus;
    uint16_t packetSize;
    uint16_t fifoCount;
    uint8_t fifoBuffer[64];
    MPU6050 mpu;
    Quaternion q;
    VectorInt16 aa;
    VectorInt16 aaReal;
    VectorInt16 aaWorld;
    VectorFloat gravity;
    float euler[3];
    float ypr[3];
};

#endif /* sensorHub */
