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
#include <BlackLib/BlackLib.h>

class Motor{
    
public:
    Motor(int _m);
    void setPWM(double output); //min 22% max 49%
    void closePWM();
    BlackPWM* pwm; //pins P8_13, P8_19, P9_14, P9_21

    
private:
    void initialize(int _i);
    double mapper(double b);
};

#endif /* defined(__Atlas__Motor__) */
