//
//  main.cpp
//  Atlas
//
//  Created by Toni Axelsson on 2014-06-06.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
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

void initailize(){
    sensorManager = new SensorManager;
    controller = new Controller;
    communicate = new Com;
    motor = new Motor;
}

void loop(){
    while (true) {
        sensorManager->readMPU(input);
        controller->calcPWM(input, output);
        motor->setPWM(output);
    }
}

int main(int argc, const char * argv[])
{
    initailize();
    loop();
    return 0;
}

