#include <iostream>
#include "motorControl.h"
#include <BlackLib/BlackLib.h>


motorControl::motorControl(){
	initialize();
}

void motorControl::initialize(){
	//BlackPWM *pwm13 = new BlackPWM(EHRPWM2B); //instansera P8_13's pwm
	pwm13 = new BlackPWM(EHRPWM2B);
	pwm13->setRunState(run); //sätt igång signalen

	pwm13->setPeriodTime(5000000);
	pwm13->setDutyPercent(0.0);

	sleep(1);
}

float motorControl::mapper(){
	std::cout << "inget än" << std::endl; //ska konvertera 0 - 100% input till riktiga pwmvärden
	return 0.0;
}

void motorControl::setPWM(float a){
	pwm13->setDutyPercent(a);
}

void motorControl::closePWM(){
	pwm13->setRunState(stop);
}
