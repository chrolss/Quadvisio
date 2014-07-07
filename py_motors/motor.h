#ifndef MOTOR_H_
#define MOTOR_H_

#include <iostream>
#include "pyembed.h"
#include <string>

using namespace pyembed;

class motor{
public:
	motor(int argc,char** argv);
	void setPWM2(std::string b, std::string c);
	void setPWM(std::string a);
	void closePWM();
	Python* py;
	Arg_map args2; //lades till

private:
	//void initialize();

};

#endif /* MOTOR_H_ */
