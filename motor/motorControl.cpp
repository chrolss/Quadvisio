#include <iostream>
#include "motorControl.h"


motorControl::motorControl(){
	initialize();
}

void motorControl::initialize(){
	pwm13 = new BlackPWM(P8_19);
	sleep(1);
	pwm13->setRunState(run); //sätt igång signalen
	sleep(1);
	pwm13->setPeriodTime(5000000);
	sleep(1);
	pwm13->setDutyPercent(0.0);
	sleep(1);
	pwm13->setDutyPercent(20.0); //Speciellt för vår ESC
	sleep(1);
}

float motorControl::mapper(float b){
	float val = float(float(29.0/100.0)*b) + float(20); //Konverterar input 0 - 100 till pwmsignal
	return val;
}

void motorControl::setPWM(float a){
	float val = mapper(a);
	std::cout << "val = " << val << std::endl;
	pwm13->setDutyPercent(val);
}

void motorControl::closePWM(){
	std::cout << "Setting pwm to zero" << std::endl;
	pwm13->setDutyPercent(20.0);
	std::cout << "Closing pwm channels" << std::endl;
	pwm13->setRunState(stop);
}
