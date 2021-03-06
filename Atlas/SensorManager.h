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
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>

//#include "mpu6050.h"
#include "I2Cdev.h"
#include "BMP_180.h"
#include "kalman.h"

#define offsetRoll 0.0 //-0.072605
#define offsetPitch 0.0 //0.001396

class SensorManager {
    
public:
    SensorManager(BMP180::OversamplingSetting oss);
    void initializeMPU();
    void initializeBMP(BMP180::OversamplingSetting oss);
    bool initializeMPUdmp();
    bool testMPU();
    void readDMP(double *input);
    void readBMP(double *input);
    bool getMode(){return mpuMode;}
    
private:
    
    void get_bmp_offset();
    
    void getKalmanParamsAlt();
    void getKalmanParamsVel();
    
    float kalmanParamsAlt[5];
    float kalmanParamsVel[5];
    
    uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    uint8_t devStatus;
    uint16_t packetSize;
    uint16_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64];
    // orientation/motion vars
    
    float euler[3];         // [psi, theta, phi]    Euler angle container
    float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
    bool dmpReady = false;
    bool mpuMode = true;
    double alpha, beta;
    struct bmp180_data *bmpData;
    
    double vz_est, hz_est, h_offset;
};

#endif /* defined(__Atlas__SensorManager__) */
