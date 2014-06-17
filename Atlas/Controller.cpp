//
//  Controller.cpp
//  Atlas
//
//  Created by Toni Axelsson on 2014-06-17.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include "Controller.h"

Controller::Controller(){
    
}

void Controller::calcPWM(float *input, float *output) {
    
    output[0] = input[0];
    output[1] = input[1];
    output[2] = input[2];
    output[3] = input[3];
    
}