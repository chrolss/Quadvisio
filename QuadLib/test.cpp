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
    
    std::cout << "Enter the port that you want to start" << std::endl;
    std::cin >> s;
    QuadPWM pwm;
    return 0;
}
