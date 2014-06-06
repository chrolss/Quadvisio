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
		args[a] = pyembed::Py_string;
		std::cout << "A" << std::endl;
		py->call("setPWM",args);
		std::cout << "B" << std::endl;
        
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
