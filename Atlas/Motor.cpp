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

void Motor::setPWM(int *sOutput) {
	pwm->setDuty("P8_13", sOutput[0]);
	pwm->setDuty("P9_14", sOutput[1]);
	pwm->setDuty("P9_21", sOutput[2]);
	pwm->setDuty("P9_42", sOutput[3]);
}
