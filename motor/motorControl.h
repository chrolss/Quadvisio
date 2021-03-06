#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#include <iostream>
#include <unistd.h>
#include <BlackLib/BlackLib.h>

class motorControl
{
public:
	motorControl();
	void setPWM(float a);  //min 22% max 49%
	void closePWM();
	BlackPWM* pwm13;
	BlackPWM* pwm14;

private:
	void initialize();
	float mapper(float b);
};

#endif /*MOTORCONTROL_H_ */
