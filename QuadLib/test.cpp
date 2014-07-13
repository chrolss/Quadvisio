//
//  main.cpp
//  QuadLib
//
//  Created by Toni Axelsson on 2014-07-11.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>

#include "QuadPWM.h"

int main(int argc, const char * argv[]) {

    QuadPWM pwm;
    pwm.intitialize("P8_13");
    
    return 0;
}
