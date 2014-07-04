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
	pwmRF = new BlackPWM(P8_13); //P8_19
	pwmLR = new BlackPWM(P9_14);	//P9_14
	pwmRR = new BlackPWM(P9_21); //P9_21
	sleep(1);
	pwmLF->setRunState(run); 		//sätt igång signalen
	pwmRF->setRunState(run);
	pwmLR->setRunState(run);
	pwmRR->setRunState(run);
	sleep(1);

	pwmLF->setPeriodTime(5000000); 	//Definiera rätt period
	pwmRF->setPeriodTime(5000000);
	pwmLR->setPeriodTime(5000000);
	pwmRR->setPeriodTime(5000000);
	sleep(1);
	pwmLF->setDutyPercent(0.0);		//Sätt duty till 0 för initiering
	pwmRF->setDutyPercent(0.0);
	pwmLR->setDutyPercent(0.0);
	pwmRR->setDutyPercent(0.0);
	sleep(1);

	pwmLF->setDutyPercent(20.0); 	//Speciellt för vår ESC, noll-nivån
	pwmRF->setDutyPercent(20.0);
	pwmLR->setDutyPercent(20.0);
	pwmRR->setDutyPercent(20.0);
	sleep(1);
	printf("PWM signal ready");
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
    
    //printf("The PWM values are: %f %f %f %f", PWM[0], PWM[1], PWM[2], PWM[3]);
}
