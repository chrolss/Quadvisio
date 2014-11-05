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
#include "ComHandler.h"
#include "Motor.h"

SensorManager *sensorManager;
Controller *controller;
ComHandler *comHandler;
Motor *motor;

bool pigeon;
bool video = false;
double sInput[7];
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
double inParams[15];
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
    comHandler = new ComHandler(video);
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

    controller->get_parameters(inParams);	//lägger parametrarna i inParams
    comHandler->setSettingsData(inParams);	//tonis funktion som skickar till Com
    controller->setSensitivity(0.6);		//sätt sens, 0.25 - 0.4
    
    runAtlas = true;
}

void loop(){
    std::cout << "Starting Loop" << std::endl;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    while (runAtlas) {
        
        // Start clock
        auto start = std::chrono::high_resolution_clock::now();

        // Read sensor data
        sensorManager->readDMP(sInput);

        
        // Commincation with Qvis
        if (comHandler->connected) {
             if (!comHandler->reciveMsg && !comHandler->sendMsg) {
                 //printf("Setting output and send to true\n");
            	 controller->get_Errors(iErrors);
                 comHandler->setOutputData(sInput, sOutput, ref, loopTime, iErrors);
                 if (comHandler->vidCount>=2) {
                     comHandler->sendImage = true;
                 }
                 comHandler->sendMsg=true;
             }
         }
        
        // Apply and store possible new settings
        if (comHandler->newSettings == true){
            
            if (comHandler->savePidTrim) {
                comHandler->getSettingsData(inParams);
                controller->setInnerParameters(inParams);
                controller->write_Parameters(inParams, outParams);
                comHandler->savePidTrim = false;
            }
            
            else if(comHandler->saveJoySens) {
                
                comHandler->saveJoySens = false;
            }
            
            comHandler->newSettings = false;
        }

        if (!comHandler->connected && !comHandler->listening) {
            comHandler->startListenThread();
        }
        comHandler->vidCount++;

        
        // Controller
        controller->setJoyCom(comHandler->controllerInputData, sInput, ref);
        if (comHandler->resetIntegral){
        	controller->reset_I();
        	comHandler->resetIntegral = false;
        }

        controller->calcPWM(sInput, sOutput, ref);

        // Set PWM values
        if (comHandler->motorOn==true && comHandler->connected){
            motor->setPWM(sOutput);
        }
        else {
            motor->setPWM(idleMotorValues);
        }
        
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
    long int bird = atoi(argv[1]);
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
    
    int videoArg = atoi(argv[2]);
                        
    if (videoArg == 1) {
        video = true;
    }
    else if (videoArg == 0) {
        video = false;
    }
    else {
        printf("Incorrect input argument for camera, 1 = Camera On, 0 = Camera Off\n");
        exit(1);
    }
    
	initailize();
    loop();

    return 0;
}

