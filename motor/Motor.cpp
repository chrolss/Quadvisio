//
//  Motor.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "Motor.h"

Motor::Motor(int _i){
	initialize(_i);
}

void Motor::initialize(int _i){
	if (_i == 1)
		pwm = new BlackPWM(P8_13);
	else if (_i == 2)
		pwm = new BlackPWM(P8_19);
	else if (_i == 3)
			pwm = new BlackPWM(P9_14);
	else if (_i == 4)
			pwm = new BlackPWM(P9_21);
	else
		printf("Invalid engine number \n");
	sleep(1);
	pwm->setRunState(run); //sätt igång signalen
	sleep(1);
	pwm->setPeriodTime(5000000);
	sleep(1);
	pwm->setDutyPercent(0.0);
	sleep(1);
	pwm->setDutyPercent(20.0); //Speciellt för vår ESC
	printf("PWM signal ready on engine %f.\n", _i);
	sleep(1);
}

double Motor::mapper(double b){
	double val = double(double(29.0/100.0)*b) + double(20); //Konverterar input 0 - 100 till pwmsignal
	return val;
}

void Motor::closePWM(){
	pwm->setDutyPercent(20.0); //förhindrar felkalibrering
	pwm->setRunState(stop); //stäng pwmportar
}

void Motor::setPWM(double output) {
    pwm->setDutyPercent(mapper(output));

}
