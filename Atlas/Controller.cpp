//
//  Controller.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "Controller.h"

Controller::Controller(){
    
}

void Controller::calcPWM(double *input, int *output) {
    
    output[0] = 1100000;
    output[1] = 1100000;
    output[2] = 1100000;
    output[3] = 1100000;
    
}
