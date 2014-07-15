//
//  main.cpp
//  QuadLib
//
//  Created by Toni Axelsson on 2014-07-11.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include <string>
#include <unistd.h>

#include "QuadPWM.h"

int main(int argc, const char * argv[]) {
    std::string s = "";
    
    QuadPWM pwm;
    pwm.intitialize("P8_13");
    pwm.intitialize("P9_14");
    pwm.intitialize("P9_21");
    pwm.intitialize("P9_42");
    
    sleep(2);
    std::cout << "Setting duty to 1200000" << std::endl;
    pwm.setDuty("P8_13", 1200000);
    pwm.setDuty("P9_14", 1200000);
    pwm.setDuty("P9_21", 1200000);
    pwm.setDuty("P9_42", 1200000);
    
    sleep(4);
    std::cout << "Setting duty to 1000000" << std::endl;
    pwm.setDuty("P8_13", 1000000);
    pwm.setDuty("P9_14", 1000000);
    pwm.setDuty("P9_21", 1000000);
    pwm.setDuty("P9_42", 1000000);

    return 0;
}
