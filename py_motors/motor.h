#ifndef MOTOR_H_
#define MOTOR_H_

#include <iostream>
#include "pyembed.h"
#include <string>
#include <sstream>

using namespace pyembed;

class motor{
public:
	motor(int argc,char** argv);
	void setPWM(float a, float b, float c, float d);
	void closePWM();
	Python* py;
	Arg_map args1;
	Arg_map args2; //lades till
	Arg_map args3; //lades till
	Arg_map args4;

private:
	std::string mapper(float b);

};

#endif /* MOTOR_H_ */
