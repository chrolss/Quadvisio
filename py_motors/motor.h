#ifndef MOTOR_H_
#define MOTOR_H_

#include <iostream>
#include <Python.h>


class motor{
public:
	motor(int argc,char** argv);
	void setPWM(double *pwms);
	void closePWM();
	PyObject *pName, *pModule, *pDict, *pLoad, *pClose, *pValue;

private:
	double mapper(double b);

};

#endif /* MOTOR_H_ */
