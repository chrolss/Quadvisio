//
//  Motor.h
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#ifndef __Atlas__Motor__
#define __Atlas__Motor__

#include <iostream>
#include <unistd.h>
#include <QuadLib/QuadPWM.h>

class Motor{
    
public:
    Motor();
    void setPWM(double *output); //min 22% max 49%
    void closePWM();
    QuadPWM* pwm;

    
private:
    void initializeAll();
    int mapper(double b);
};

#endif /* defined(__Atlas__Motor__) */
