//
//  SensorManager.h
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#ifndef __Atlas__SensorManager__
#define __Atlas__SensorManager__

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

//#include "mpu6050.h"
#include "I2Cdev.h"

#define offsetRoll -0.072605
#define offsetPitch 0.001396

class SensorManager {
    
public:
    SensorManager();
    void initializeMPU();
    bool initializeMPUdmp();
    bool testMPU();
    void readMPU(double *input);
    void readDMP(double *input);
    
private:
    
    uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    uint8_t devStatus;
    uint16_t packetSize;
    uint16_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64];
    // orientation/motion vars
    
    float euler[3];         // [psi, theta, phi]    Euler angle container
    float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
    bool dmpReady = false;
};

#endif /* defined(__Atlas__SensorManager__) */
