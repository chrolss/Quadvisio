#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#include <iostream>
#include <unistd.h>

class motorControl
{
public:
	motorControl();
	void setPWM(float a);
	void closePWM();

private:
	void initialize();
	float mapper();
};

#endif /*MOTORCONTROL_H_ */
