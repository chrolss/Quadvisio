//
//  SensorManager.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "SensorManager.h"
#include "MPU6050_6AXIS_MOTIONAPPS20.h"

MPU6050 *mpu;

Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector

SensorManager::SensorManager(){
    mpu = new MPU6050(0x68);
}

void SensorManager::initializeMPU() {
    mpu->initialize();
}

bool SensorManager::initializeMPUdmp() {
    devStatus = mpu->dmpInitialize();
    if (devStatus==0) {
        printf("Enabling DMP...\n");
        mpu->setDMPEnabled(true);
        
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
    return false;
}

/*
void SensorManager::readMPU(double *input) {
    
    mpu->getMotion6(&input[0], &input[1], &input[2], &input[3], &input[4], &input[5]);
    
    printf("X: %f\nY: %f\n Z: %f\nRoll: %f\nPitch: %f\nYaw %f\n\n",input[0],input[1],input[2],input[3],input[4],input[5]);
}
*/

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
    if (fifoCount>=42) {
        mpu->getFIFOBytes(fifoBuffer, packetSize);
        
        // display Euler angles in degrees
        mpu->dmpGetQuaternion(&q, fifoBuffer);
        mpu->dmpGetGravity(&gravity, &q);
        mpu->dmpGetYawPitchRoll(ypr, &q, &gravity);
        //printf("ypr  %7.2f %7.2f %7.2f    ", ypr[0] * 180/M_PI, ypr[1] * 180/M_PI, ypr[2] * 180/M_PI);
        
        //printf("\n");
        
        mpu->dmpGetQuaternion(&q, fifoBuffer);
        mpu->dmpGetAccel(&aa, fifoBuffer);
        mpu->dmpGetGravity(&gravity, &q);
        mpu->dmpGetLinearAccel(&aaReal, &aa, &gravity);
        //printf("areal %6d %6d %6d    ", aaReal.x, aaReal.y, aaReal.z);
        
        //printf("\n");
        
        input[0] = aaReal.x;
        input[1] = aaReal.y;
        input[2] = aaReal.z;
        input[3] = ypr[2] * 180/M_PI; // Roll
        input[4] = ypr[1] * 180/M_PI; // Pitch
        input[5] = ypr[0] * 180/M_PI; // Yaw

    }
    else {
        printf("not reading");
    }
}


