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
	
	pwmLF = new BlackPWM(P8_13); //P8_13
	sleep(1);
	pwmLF->setRunState(run); //sätt igång signalen
	sleep(1);
	pwmLF->setPeriodTime(5000000);
	sleep(1);
	pwmLF->setDutyPercent(0.0);
	sleep(1);
	pwmLF->setDutyPercent(20.0); //Speciellt för vår ESC
	sleep(1);
	printf("P8_13 ready\n");
	
	pwmRF = new BlackPWM(P8_19); //P8_19
	sleep(1);
	pwmRF->setRunState(run); //sätt igång signalen
	sleep(1);
	pwmRF->setPeriodTime(5000000);
	sleep(1);
	pwmRF->setDutyPercent(0.0);
	sleep(1);
	pwmRF->setDutyPercent(20.0); //Speciellt för vår ESC
	sleep(1);
	printf("P8_19 ready\n");
}

float Motor::mapper(float b){
	float val = float(float(29.0/100.0)*b) + float(20); //Konverterar input 0 - 100 till pwmsignal
	return val;
}

void Motor::closePWM(){
	pwmLF->setRunState(stop); //stäng alla fyra pwmportar
	pwmRF->setRunState(stop);
	/*
	pwmLR->setRunState(stop);
	pwmRR->setRunState(stop);
	*/
}

void Motor::setPWM(float *output) {
	for (int i = 0; i<4; i++)
		PWM[i] = mapper(output[i]);

    pwmLF->setDutyPercent(PWM[0]);
    pwmRF->setDutyPercent(PWM[1]);
    /*
    pwmLR->setDutyPercent(PWM[2]);
    pwmRR->setDutyPercent(PWM[3]);
	*/
    //printf("The PWM values are: %f %f %f %f", PWM[0], PWM[1], PWM[2], PWM[3]);
}
