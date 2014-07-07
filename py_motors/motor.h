#ifndef MOTOR_H_
#define MOTOR_H_

#include <iostream>
#include "pyembed.h"
#include <string>

using namespace pyembed;

class motor{
public:
	motor(int argc,char** argv);
	void setPWM(std::string a, std::string b);
	void closePWM();
	Python* py;
	Arg_map args2; //lades till
	Arg_map args3; //lades till

private:
	//void initialize();

};

#endif /* MOTOR_H_ */
