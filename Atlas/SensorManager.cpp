//
//  SensorManager.cpp
//  Atlas
//
//  Created by Toni Axelsson on 2014-06-17.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include "SensorManager.h"

SensorManager::SensorManager(){
    
}

void SensorManager::initialize(){
    
}

void SensorManager::readMPU(float *input) {
    input[0] = 1.0;
    input[1] = 2.0;
    input[2] = 3.0;
    input[3] = 4.0;
    input[4] = 5.0;
    input[5] = 6.0;
}


