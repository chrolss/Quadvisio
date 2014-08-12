//
//  main.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include <string>
#include <chrono>

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

// Loop time measurement
double loopTime;
int Hz = 1;
int loopSleep;

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
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    
    while (runAtlas && counter<2000) {
        
        // Start clock
        auto start = std::chrono::high_resolution_clock::now();
        
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
        
        // Measure duration
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        
        loopSleep = 1000000/Hz - (int)duration;
        
        // Sleep
        usleep(loopSleep);
        
        // Measure duration again and print out the frequency
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        loopTime = double(1000000)/(duration2);
        std::cout << "Running at: " << loopTime << "Hz" << std::endl;
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

