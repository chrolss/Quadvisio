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

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

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
double idleMotorValues[] = {0.0, 0.0, 0.0, 0.0};
bool runAtlas=false;
bool motorIdle=false;
int counter = 0;
int vidCount = 0;

// Loop time measurement
double loopTime;
int Hz = 200;
int loopSleep=0;
double ref[3];
double params[9];

void initailize(){
    for (int i =0 ; i<6; i++) {
        sInput[i] = 0.0;
    }
    for (int i =0 ; i<4; i++) {
        sOutput[i] = 0.0;
    }
    sensorManager = new SensorManager;
    controller = new Controller;
    communicate = new Com;
    motor = new Motor;
    
    if(sensorManager->initializeMPUdmp()) {
        runAtlas = true;
    }
    
    ref[0]=0.0;
    ref[1]=0.0;
    ref[2]=0.0;

    /*

    params[0] = 0.00009;
    params[1] = 0.0; 	//0.00003;
    params[2] = 0.00002;
    params[3] = 0.00009;
    params[4] = 0.0;	//0.00003;
    params[5] = 0.00002;
    params[6] = 0.00006;
    params[7] = 0.0;	//0.00003;
    params[8] = 0.00002;
	controller->setParameters(params);
    */

    controller->setReference(ref);
    

    runAtlas = true;
}

void loop(){
    std::cout << "Starting Loop" << std::endl;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    
    while (runAtlas && counter<6000) {
        
        // Start clock
        auto start = std::chrono::high_resolution_clock::now();
        
        // Read sensor data
        sensorManager->readDMP(sInput);
        
        // If connected to Qvis send data
        if (communicate->connected==true && communicate->reciveMsg==false && communicate->msgSend==false) {
            communicate->setOutputData(sInput);
            if (vidCount>=int(((double(5.0/communicate->imgSendRate))-1)*10) && communicate->videoStream==true) {
                communicate->imgSend=true;
                vidCount=0;
            }
            communicate->msgSend=true;
        }
        
        //std::cout << "Calculate control action" << std::endl;
        // Calculate control action
        controller->setF(communicate->verticalThrust);
        controller->setParameters(communicate->pidParam);
        controller->calcPWM(sInput, sOutput);
        
        //std::cout << "Setting PWM values" << std::endl;
        // Send PWM values to motors
        if (communicate->runMotor==true) {
            motor->setPWM(sOutput);
        }
        else if (motorIdle==false) {
            motor->setPWM(idleMotorValues);
        }
        else {
            motorIdle=true;
            motor->setPWM(idleMotorValues);
        }

        vidCount++;
        counter++;
        std::cout << counter << std::endl;
        
        // Measure duration
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        
        loopSleep = 1000000/Hz - (int)duration;
        
        
        // Sleep
        if (loopSleep>0) {
            usleep(loopSleep);
        }
        
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

