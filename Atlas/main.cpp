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
double input[6];
double output[4];
bool runAtlas=true;

void initailize(){
    sensorManager = new SensorManager;
    controller = new Controller;
    communicate = new Com;
    motor = new Motor;
    
    sensorManager->initializeMPU();
}

void loop(){
    while (runAtlas) {

        // Read sensor data
        sensorManager->readMPU(input);

        // Calculate control action
        controller->calcPWM(input, output);

        // Send PWM values to motors
        //motor->setPWM(output);

        // If connected to Qvis send data
        if (communicate->connected) {
            communicate->sendMsg(input);
        }
        runAtlas=false;
    }
}

int main(int argc, const char * argv[])
{
    initailize();
    loop();

    return 0;
}

