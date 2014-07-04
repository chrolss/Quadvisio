//
//  SensorManager.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "SensorManager.h"

SensorManager::SensorManager(){
    mpu = new mpu6050(1, 0x68);
}

void SensorManager::initializeMPU(){
    mpu->initialize();
}

void SensorManager::readMPU(double *sInput) {
    
    mpu->getMotion(&sInput[0], &sInput[1], &sInput[2], &sInput[3], &sInput[4], &sInput[5]);
    
    //printf("X: %f\nY: %f\n Z: %f\nRoll: %f\nPitch: %f\nYaw %f\n\n",sInput[0], sInput[1], sInput[2], sInput[3], sInput[4], sInput[5]);
}


