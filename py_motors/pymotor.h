#ifndef PYMOTOR_H_
#define PYMOTOR_H_

#include <iostream>
#include "pyembed.h"
#include <string>
#include <sstream>

using namespace pyembed;

class motor{
public:
	motor(int argc,char** argv);
	void setPWM(double* d);
	void closePWM();
	Python* py;

private:
	double mapper(double b);

};

#endif /* PYMOTOR_H_ */
