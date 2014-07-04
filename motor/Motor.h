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
    Motor();
    void setPWM(float *output); //min 22% max 49%
    void closePWM();
    BlackPWM* pwmLF; //Left Front, pin P8_13
    BlackPWM* pwmRF; //right front, pin P8_19
    //BlackPWM* pwmLR; //left rear, pin P9_14
    //BlackPWM* pwmRR; //right rear, pin P9_16

    
private:
    float PWM[4];
    void initialize();
    float mapper(float b);
};

#endif /* defined(__Atlas__Motor__) */
