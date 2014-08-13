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

#define MOTOR_FL "P8_13"
#define MOTOR_FR "P9_14"
#define MOTOR_BL "P9_21"
#define MOTOR_BR "P9_42"

int main(int argc, const char * argv[]) {
    std::string s = "";
    
    int pwmInput = 0;
    
    QuadPWM pwm;
    pwm.initialize("P8_13");
    pwm.initialize("P9_14");
    pwm.initialize("P9_21");
    pwm.initialize("P9_42");
    
    sleep(1);
    
    while (true) {
        std::cout << "Enter pwm value" << std::endl;
        std::cin >> pwmInput;
        if (pwmInput<0) {
            break;
        }
        pwm.setDuty(MOTOR_FR, pwmInput);
        pwm.setDuty(MOTOR_FL, pwmInput);
        pwm.setDuty(MOTOR_BL, pwmInput);
        pwm.setDuty(MOTOR_BR, pwmInput);

    }
    /*
    std::cout << "Setting duty to 1200000" << std::endl;
    pwm.setDuty("P8_13", 1200000);
    pwm.setDuty("P9_14", 1200000);
    pwm.setDuty("P9_21", 1200000);
    pwm.setDuty("P9_42", 1200000);
    */
    sleep(1);
    std::cout << "Setting duty to 1000000" << std::endl;
    pwm.setDuty("P8_13", 1000000);
    pwm.setDuty("P9_14", 1000000);
    pwm.setDuty("P9_21", 1000000);
    pwm.setDuty("P9_42", 1000000);

    return 0;
}
