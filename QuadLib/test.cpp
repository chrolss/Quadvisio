//
//  main.cpp
//  QuadLib
//
//  Created by Toni Axelsson on 2014-07-11.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include <string>

#include "QuadPWM.h"

int main(int argc, const char * argv[]) {
    std::string s = "";
    
    QuadPWM pwm;
    pwm.checkLoaded("am33xx_pwm");
    //pwm.intitialize("P8_13");
    
    return 0;
}
