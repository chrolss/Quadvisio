#include "motor.h"
#include <string>

motor::motor(int argc,char** argv){
	// Initialize Python interpreter
	Py_Initialize();

	// Make sure so that the Python code is found
	PyRun_SimpleString ("import sys; sys.path.insert(0, '/home/root/Desktop/Quadvisio/py_motors')");

	//Name of the Python script
	pName = PyString_FromString("pwm");

	// Load the module object
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	// pDict is a borrowed reference
	
	pLoad = PyObject_GetAttrString(pModule, "initialize");
	//pSet = PyObject_GetAttrString(pModule, "set_pwm");
	//pClose = PyObject_GetAttrString(pModule, "close_pwm");
	//pArgs = PyTuple_New(4);
	PyObject_CallObject(pLoad,NULL);
	Py_DECREF(pModule);

}

double motor::mapper(double b){
	double val = (double(double(29.0/100.0)*b) + double(20)); //Konverterar input 0 - 100 till pwmsignal
	return val;
}

void motor::setPWM(double *pwms){
	PyObject* pName = PyString_FromString("pwm");

		// Load the module object
	PyObject* pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	PyObject* pSet = PyObject_GetAttrString(pModule,"set_pwm1");
	PyObject* pArgs = PyTuple_New(1);
	std::string s;
	std::cin >> s;
	for (int i = 0; i < 1; i++){
		pValue = PyString_FromString(s.c_str());
		PyTuple_SetItem(pArgs, i, pValue);
	}

	Py_XINCREF(pArgs);
	PyObject_CallObject(pSet, pArgs);
	Py_XDECREF(pArgs);
	Py_DECREF(pSet);
}


void motor::closePWM(){
	PyObject* pClose = PyObject_GetAttrString(pModule,"close_pwm");
	PyObject_CallObject(pClose,NULL);
	Py_DECREF(pClose);
	Py_DECREF(pModule);
	Py_DECREF(pName);
	Py_Finalize();
}
