//
//  SensorManager.h
//  Atlas
//
//  Created by Toni Axelsson on 2014-06-17.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#ifndef __Atlas__SensorManager__
#define __Atlas__SensorManager__

#include <iostream>
#include <string>

class SensorManager {
    
public:
    SensorManager();
    void initialize();
    void readMPU(float *input);
    
private:
    
};

#endif /* defined(__Atlas__SensorManager__) */
