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
double sInput[6];
double sOutput[4];
bool runAtlas=false;

void initailize(){
    sensorManager = new SensorManager;
    controller = new Controller;
    communicate = new Com;
    motor = new Motor;
    
    if(sensorManager->initializeMPUdmp()) {
        runAtlas = true;
    }
}

void loop(){
    while (runAtlas) {

        // Read sensor data
        sensorManager->readDMP(sInput);

        // Calculate control action
        controller->calcPWM(sInput, sOutput);
        
        // Tillfälligt avstängd tills motorkoden är klar
        // Send PWM values to motors
        //motor->setPWM(output);

        // If connected to Qvis send data
        if (communicate->connected==true) {
            std::cout << "Sending data" << std::endl;
            communicate->sendMsg(sInput);
        }
    }
}

int main(int argc, const char * argv[])
{
    initailize();
    loop();

    return 0;
}

