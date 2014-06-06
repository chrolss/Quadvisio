// Quadvisio registered trademark awesomeness

#include <iostream>
#include "motorPWM.h"

//using namespace pyembed;

motorPWM::motorPWM(int argc, char** argv){
	try
	{
        py = new pyembed::Python(argc,argv);
        py->load("pyPWM");
        py->call("init");
	}
	catch (pyembed::Python_exception ex)
	{
		std::cout << ex.what();
	}
}

void motorPWM::setPWM(std::string a){
	try
	{
		pyembed::Arg_map args;

		args[a] = pyembed::Py_string;

		py->call("setPWM",args);
		args.clear();
	}
	catch (pyembed::Python_exception ex)
	{
		std::cout << ex.what();
	}
}

void motorPWM::closePWM()
{
    try {
        py->call("close");
    } catch (pyembed::Python_exception ex) {
        std::cout << ex.what();
    }
}

//motorPWM::~motorPWM()
//{
//
//}