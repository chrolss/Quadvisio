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
int sOutput[4];
bool runAtlas=false;
int counter = 0;
int globalCounter = 0;

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
    while (runAtlas && counter<1000) {

        // Read sensor data
        sensorManager->readDMP(sInput);

        // Calculate control action
        controller->calcPWM(sInput, sOutput);
        
        // Tillfälligt avstängd tills motorkoden är klar
        // Send PWM values to motors
        motor->setPWM(sOutput);

        // If connected to Qvis send data
        if (communicate->connected==true && counter>10) {
            
            communicate->sendMsg(sInput);
            globalCounter++;
            std::cout << "Sent data " << globalCounter << std::endl;
            counter = 0;
        }
        counter++;
    }
    motor->closePWM();
    std::cout << "Test klart" << std::endl;
}

int main(int argc, const char * argv[])
{
    initailize();
    loop();

    return 0;
}

