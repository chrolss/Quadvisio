//
//  main.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include <string>

#include "SensorManager.h"
#include "Controller.h"
#include "Com.h"
#include "Motor.h"

SensorManager *sensorManager;
Controller *controller;
Com *communicate;
Motor *motor;
float input[6];
float output[4];
bool run=true;

void initailize(){
    sensorManager = new SensorManager;
    controller = new Controller;
    communicate = new Com;
    motor = new Motor;
}

void loop(){
    while (run) {
        sensorManager->readMPU(input);
        controller->calcPWM(input, output);
        motor->setPWM(output);
        run=false;
    }
}

int main(int argc, const char * argv[])
{
    initailize();
    loop();
    return 0;
}

