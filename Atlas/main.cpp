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

        // Read sensor data
        sensorManager->readMPU(input);

        // Calculate control action
        controller->calcPWM(input, output);

        // Send PWM values to motors
        motor->setPWM(output);

        // If connected to Qvis send data
        if (communicate->connected) {
            communicate->sendMsg("Hej", 3);
        }
        run=false;
    }
}

int main(int argc, const char * argv[])
{
    //initailize();
    //loop();
	float tal;
	float pwmTal[4];
	Motor pwm;
	while (true){
		printf("Ge pwm-värde\n");
		std::cin >> tal;
		if (tal > 100){
			pwm.closePWM();
			exit(1);
		}
		pwmTal[0] = tal;
		pwmTal[1] = tal;
		pwmTal[2] = tal;
		pwmTal[3] = tal;

		pwm.setPWM(pwmTal);
	}


    return 0;
}
