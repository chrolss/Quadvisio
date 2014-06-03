// Quadvisio registered trademark awesomeness

#include <iostream>
#include "pyembed.h"
#include "motorPWM.h"

using namespace pyembed;

motorPWM::motorPWM(){}

void motorPWM::setMotorPWM(double s1,double s2, double s3, double s4){
		
	

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
