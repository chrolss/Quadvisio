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
Com *C;
Motor *motor;
bool pigeon;
double sInput[6];
double sOutput[4];
double idleMotorValues[] = {0.0, 0.0, 0.0, 0.0};
bool runAtlas=false;
bool motorIdle=false;
int counter = 0;
int vidCount = 0;
double errors[3];	//for reading integral errors

// Loop time measurement
double loopTime = 0.0;
int Hz = 100;
int loopSleep=0;
double ref[7];
double inParams[12];	//inte värdelös längre
double outParams[6];
double iErrors[3];

void initailize(){
    for (int i =0 ; i<6; i++) {
        sInput[i] = 0.0;
    }
    for (int i =0 ; i<4; i++) {
        sOutput[i] = 0.0;
    }
    for (int i =0 ; i<6; i++) {
            outParams[i] = 0.0;
        }
    sensorManager = new SensorManager;
    controller = new Controller(pigeon);
    C = new Com;
    motor = new Motor;
    
    if(sensorManager->getMode()){
    	if(sensorManager->initializeMPUdmp()) {
    		runAtlas = true;
    	}
    }
    
    ref[0] = 0.0;	//roll
    ref[1] = 0.0;	//pitch
    ref[2] = 0.0;	//yaz
    ref[3] = 0.0;	//x-acceleration
    ref[4] = 0.0;	//y-acceleration
    ref[5] = 0.0;	//z-accerleration
    ref[6] = 0.0;	//altitude

    sOutput[0] = 0.0;
    sOutput[1] = 0.0;
    sOutput[2] = 0.0;
    sOutput[3] = 0.0;

    controller->send_Parameters(inParams);	//lägger parametrarna i inParams
    C->setPidParams(inParams);				//tonis funktion som skickar till Com
    controller->setSensitivity(0.4);		//sätt sens, 0.25 - 0.4

    runAtlas = true;
}

void loop(){
    std::cout << "Starting Loop" << std::endl;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    while (runAtlas && counter<600000) {
        
        // Start clock
        auto start = std::chrono::high_resolution_clock::now();
        
        if (C->savePid == true){
        	C->getPidParams(inParams);
        	controller->setInnerParameters(inParams);
        	controller->write_Parameters(inParams, outParams);
        	controller->write_trim();
        	C->savePid = false;
        }

        // Read sensor data
        sensorManager->readDMP(sInput);
        
        // If connected to Qvis send data
        /*
        if (communicate->connected==true && communicate->reciveMsg==false && communicate->msgSend==false) {
            communicate->setOutputData(sInput);
            if (vidCount>=int(((double(5.0/communicate->imgSendRate))-1)*10) && communicate->videoStream==true) {
                communicate->imgSend=true;
                vidCount=0;
            }
            communicate->msgSend=true;
        }
        */

        if (C->connected) {
             if (!C->reciveMsg && !C->msgSend) {
                 //printf("Setting output and send to true\n");
            	 controller->get_Errors(iErrors);
                 C->setOutputData(sInput, sOutput, ref, loopTime, iErrors);
                 if (C->vidCount>=2) {
                     C->imgSend = true;
                 }
                 C->msgSend=true;
             }
         }

         if (!C->connected && !C->listening) {
             C->startListenThread();
         }
         C->vidCount++;

        
        //std::cout << "Calculate control action" << std::endl;
        // Calculate control action
        //add controller->setOuterParameters
        //controller->calcRef(sInput, ref);	//outer controller
        //controller->setReference(ref);		//set new references based on outer controller

        controller->setJoyCom(C->inputData, sInput, ref);
        if (C->resetIntegral){
        	controller->reset_I();
        	C->resetIntegral = false;
        }

        //controller->setInnerParameters(communicate->pidParam);

        controller->calcPWM(sInput, sOutput, ref);
        //printf("Pitch: %f, Roll: %f, Yaw: %f \n", errors[0], errors[1], errors[2]);
        //std::cout << "Setting PWM values" << std::endl;
        // Send PWM values to motors


        if (C->motorOn==true && C->connected){
            motor->setPWM(sOutput);
        }
        else {
            motor->setPWM(idleMotorValues);
        }

        //vidCount++;
        counter++;
        //std::cout << counter << std::endl;
        
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
        //std::cout << "Running at: " << loopTime << "Hz" << std::endl;
    }
    
    motor->closePWM();
    std::cout << "Test klart" << std::endl;
}

int main(int argc, const char* argv[])
{
    int bird = atoi(argv[1]);
    if (bird == 1){
    	pigeon = true;
    }
    else if(bird == 2){
    	pigeon = false;
    }
    else{
    	printf("Incorrect input argument, 1 = Pigeon, 2 = Phoenix\n");
    	exit(1);
    }
	initailize();
    loop();

    return 0;
}

