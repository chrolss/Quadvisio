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

void SensorManager::readMPU(double *input) {
    
    mpu->getMotion(&input[0], &input[1], &input[2], &input[3], &input[4], &input[5]);
    
    printf("a/g: %f %f %f   %f %f %f\n",input[0],input[1],input[2],input[3],input[4],input[5]);
}


