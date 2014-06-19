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

class SensorManager {
    
public:
    SensorManager();
    void initialize();
    void readMPU(float *input);
    
private:
    
};

#endif /* defined(__Atlas__SensorManager__) */
