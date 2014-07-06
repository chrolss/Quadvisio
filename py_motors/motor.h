#ifndef MOTOR_H_
#define MOTOR_H_

#include <iostream>
#include "pyembed.h"
#include <string>

using namespace pyembed;

class motor{
public:
	motor(int argc,char** argv);
	void setPWM(std::string a);
	void closePWM();
	Python* py;

private:
	//void initialize();

};

#endif /* MOTOR_H_ */
