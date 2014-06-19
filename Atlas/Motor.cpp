//
//  Motor.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "Motor.h"

Motor::Motor(){
	initialize();
}

void Motor::initialize(){
	pwmLF = new BlackPWM(EHRPWM2B); //P8_13
	pwmRF = new BlackPWM(EHRPWM2A); //P8_19
	pwmLR = new BlackPWM(EHRPWM1A);	//P9_14
	pwmRR = new BlackPWM(EHRPWM1B); //P9_16

	pwmLF->setRunState(run); //sätt igång signalen
	pwmRF->setRunState(run);
	pwmLR->setRunState(run);
	pwmRR->setRunState(run);

	pwmLF->setPeriodTime(5000000);
	pwmRF->setPeriodTime(5000000);
	pwmLR->setPeriodTime(5000000);
	pwmRR->setPeriodTime(5000000);

	pwmLF->setDutyPercent(0.0);
	pwmRF->setDutyPercent(0.0);
	pwmLR->setDutyPercent(0.0);
	pwmRR->setDutyPercent(0.0);

	sleep(1);
	pwmLF->setDutyPercent(20.0); //Speciellt för vår ESC
	pwmRF->setDutyPercent(20.0);
	pwmLR->setDutyPercent(20.0);
	pwmRR->setDutyPercent(20.0);


	sleep(1);
}

float Motor::mapper(float b){
	float val = float(float(29.0/100.0)*b) + float(20); //Konverterar input 0 - 100 till pwmsignal
	return val;
}

void Motor::closePWM(){
	pwmLF->setRunState(stop); //stäng alla fyra pwmportar
	pwmRF->setRunState(stop);
	pwmLR->setRunState(stop);
	pwmRR->setRunState(stop);
}

void Motor::setPWM(float *output) {
	for (int i = 0; i<4; i++)
		PWM[i] = mapper(output[i]);

    pwmLF->setDutyPercent(PWM[0]);
    pwmRF->setDutyPercent(PWM[1]);
    pwmLR->setDutyPercent(PWM[2]);
    pwmRR->setDutyPercent(PWM[3]);
    
    printf("The PWM values are: %f %f %f %f", PWM[0], PWM[1], PWM[2], PWM[3]);
}
