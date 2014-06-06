#ifndef MOTORPWM_H_
#define MOTORPWM_H_
#include "pyembed.h"

class motorPWM
{
public:
	motorPWM(int argc, char** argv);
	void setPWM(std::string a); //will take 4 speed values and write correct PWM
    void closePWM();
	//~motorPWM();

private:
	double p1,p2,p3,p4;
	pyembed::Python *py;
    pyembed::Arg_map args;
};

#endif /* MOTORPWM_H_ */	
 
