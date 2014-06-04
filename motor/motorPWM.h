#ifndef MOTORPWM_H_
#define MOTORPWM_H_
#include "pyembed.h"

class motorPWM
{
public:
	motorPWM();
	void setPWM(float a); //will take 4 speed values and write correct PWM
	void talk(int argc, char** argv); //test function for pyscripts
	~motorPWM();

private:
	double p1,p2,p3,p4;
	Python py;
};

#endif /* MOTORPWM_H_ */	
 
