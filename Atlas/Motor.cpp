//
//  Motor.cpp
//  Atlas
//
//  Created by Toni Axelsson on 2014-06-17.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include "Motor.h"

Motor::Motor(){
    
}

void Motor::setPWM(float *output) {
    PWM[0]=output[0];
    PWM[1]=output[1];
    PWM[2]=output[2];
    PWM[3]=output[3];
    
    printf("The PWM values are: %f %f %f %f", PWM[0], PWM[1], PWM[2], PWM[3]);
}