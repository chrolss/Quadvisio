// Quadvisio registered trademark awesomeness

#include <iostream>
#include "motorPWM.h"

using namespace pyembed;

motorPWM::motorPWM(int argc, char** argv){
	try
	{
        py(argc, argv);
        py.load("pyPWM");
        py.call("init");
	}
	catch (Python_exception ex)
	{
		std::cout << ex.what();
	}
}

void motorPWM::setPWM(std::string a){
	try
	{
		Arg_map args;

		args["4"] = Py_long;

		py.call("setPWM",args);
	}
	catch (Python_exception ex)
	{
		std::cout << ex.what();
	}
}

void motorPWM::closePWM()
{
    try {
        py.call("close");
    } catch (Python_exception ex) {
        std::cout << ex.what();
    }
}

void motorPWM::talk(int argc, char** argv){
	try
    	{
      		Python py(argc, argv); //create a python instance
	
		py.run_file("hello.py");
	}
	catch (Python_exception ex)
   	{
      		std::cout << ex.what() << '\n';
    	}
}

//motorPWM::~motorPWM()
//{
//
//}
