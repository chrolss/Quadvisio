// Quadvisio registered trademark awesomeness

#include <iostream>
#include "pyembed.h"
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

void motorPWM::setPWM(float a){
	try
	{
		Arg_map args;

		args[a] = Py_float;

		py.call("setPWM",args);
	}
	catch (Pyton_exception ex)
	{
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

motorPWM::~motorPWM(){}
