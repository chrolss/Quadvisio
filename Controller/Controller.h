//
//  Controller.h
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#ifndef __Atlas__Controller__
#define __Atlas__Controller__

#include <iostream>

#define THRUST_CONSTANT 0.0003
#define ARM_RADIUS 0.176
#define DRAG_CONSTANT 9.9768e-8

class Controller{
    
public:
    Controller();
    void calcPWM(double *input, double *output);
    
private:
    
};

#endif /* defined(__Atlas__Controller__) */
