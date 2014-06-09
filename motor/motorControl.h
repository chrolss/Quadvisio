#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#include <iostream>
#include <unistd.h>
#include <BlackLib/BlackLib.h>

class motorControl
{
public:
	motorControl();
	void setPWM(float a);
	void closePWM();
	BlackPWM* pwm13;

private:
	void initialize();
	float mapper();
};

#endif /*MOTORCONTROL_H_ */
