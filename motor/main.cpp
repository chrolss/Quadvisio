//
//  main.cpp
//  Motor
//
//  Created by Toni Axelsson on 2014-06-04.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include <iostream>
#include "motorPWM.h"

int main(int argc, char** argv)
{
    motorPWM PWM(argc, argv);
    
    
    std::string s;
    while (true) {
        printf("Enter valuse between 4 and 10, a to exit \n");
        std::cin >> s;
        if (s!="a") {
            PWM.setPWM(s);
            printf("Setting duty cycle to: %s\n", s.c_str());
        }
        else {
            printf("closing...\n");
            PWM.closePWM();
            break;
        }
    }
    return 0;
}

