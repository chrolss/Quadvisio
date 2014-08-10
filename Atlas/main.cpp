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
int vidCount = 0;

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
    while (runAtlas && counter<2000) {

        // Read sensor data
        sensorManager->readDMP(sInput);
        
        // If connected to Qvis send data
        if (communicate->connected==true && communicate->reciveMsg==false) {
            communicate->setOutputData(sInput);
            if (vidCount>=int(((double(5.0/communicate->imgSendRate))-1)*10) && communicate->videoStream) {
                communicate->imgSend=true;
                vidCount=0;
            }
            communicate->msgSend=true;
        }

        // Calculate control action
        controller->calcPWM(sInput, sOutput);

        // Send PWM values to motors
        motor->setPWM(sOutput);

        vidCount++;
        counter++;
        std::cout << counter << std::endl;
        usleep(1000);
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

