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

void SensorManager::readMPU(float *input) {
    input[0] = 1.0;
    input[1] = 2.0;
    input[2] = 3.0;
    input[3] = 4.0;
    input[4] = 5.0;
    input[5] = 6.0;
}


