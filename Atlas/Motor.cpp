//
//  Motor.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "Motor.h"

Motor::Motor(){
	initializeAll();
}

void Motor::initializeAll(){
	pwm = new QuadPWM;
	pwm->initialize("P8_13"); //Left Rear
	pwm->initialize("P9_14"); //Right Rear
	pwm->initialize("P9_21"); //Right Front
	pwm->initialize("P9_42"); //Left Front
	printf("Motors initialized\n");
}


void Motor::closePWM(){
	pwm->setDuty("P8_13", 1000000);
	pwm->setDuty("P9_14", 1000000);
	pwm->setDuty("P9_21", 1000000);
	pwm->setDuty("P9_42", 1000000);
	printf("Motors are closed\n");

}

void Motor::setPWM(double *sOutput) {
    
	pwm->setDuty("P9_42", mapper(sOutput[0])); // Left Front
	pwm->setDuty("P9_14", mapper(sOutput[1])); // Right Front
	pwm->setDuty("P8_13", mapper(sOutput[2])); // Right Rear
	pwm->setDuty("P9_21", mapper(sOutput[3])); // Left Rear
}

int Motor::mapper(double _d) {
    return _d*10000 + 1000000;
}

