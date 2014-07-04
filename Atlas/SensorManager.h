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

#include "mpu6050.h"

class SensorManager {
    
public:
    SensorManager();
    void initializeMPU();
    void readMPU(double *input);
    
private:
    mpu6050 *mpu;
    
};

#endif /* defined(__Atlas__SensorManager__) */
