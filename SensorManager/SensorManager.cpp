//
//  SensorManager.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "SensorManager.h"
#include <math.h>


SensorManager::SensorManager(){
    mpu = new mpu6050(1, 0x68);
}

void SensorManager::initializeMPU() {
    mpu->initialize();
}

bool SensorManager::initializeMPUdmp() {
    devStatus = mpu->dmpInitialize()
    if (devStatus==0) {
        printf("Enabling DMP...\n");
        mpu->setDMPEnable(true);
        
        mpuIntStatus = mpu->getIntStatus();
        
        packetSize = mpu->dmpGetFIFOPacketSize();
        dmpReady = true;
        return dmpReady;
    }
    printf("DMP Initialization failed (code %d)\n", devStatus);
    return false;
}

bool SensorManager::testMPU() {
    if (mpu->testConnection()) {
        return true;
    }
    else {
        return false;
    }
}

void SensorManager::readMPU(double *input) {
    
    mpu->getMotion(&input[0], &input[1], &input[2], &input[3], &input[4], &input[5]);
    
    printf("X: %f\nY: %f\n Z: %f\nRoll: %f\nPitch: %f\nYaw %f\n\n",input[0],input[1],input[2],input[3],input[4],input[5]);
}

void SensorManager::readDMP(double *input) {
    if (!dmpReady) {
        return;
    }
    
    fifoCount = mpu->getFIFOCount();
    
    if (fifoCount == 1024) {
        mpu->resetFIFO();
        printf("FIFO overflow! Reseting...\n");
    }
    
    while (fifoCount<42) {
        fifoCount = mpu->getFIFOCount();
    }
    mpu->getFIFOBytes(fifoBuffer, packetSize);
    
    // display Euler angles in degrees
    mpu->dmpGetQuaternion(&q, fifoBuffer);
    mpu->dmpGetGravity(&gravity, &q);
    mpu->dmpGetYawPitchRoll(ypr, &q, &gravity);
    printf("ypr  %7.2f %7.2f %7.2f    ", ypr[0] * 180/M_PI, ypr[1] * 180/M_PI, ypr[2] * 180/M_PI);
    
    
    // display initial world-frame acceleration, adjusted to remove gravity
    // and rotated based on known orientation from quaternion
    mpu->dmpGetQuaternion(&q, fifoBuffer);
    mpu->dmpGetAccel(&aa, fifoBuffer);
    mpu->dmpGetGravity(&gravity, &q);
    mpu->dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
    printf("aworld %6d %6d %6d    ", aaWorld.x, aaWorld.y, aaWorld.z);
    
}


