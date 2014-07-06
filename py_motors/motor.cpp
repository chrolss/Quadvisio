#include "motor.h"

motor::motor(int argc,char** argv){
	try{
		py = new pyembed::Python(argc, argv);
		py->load("pwm");
		py->call("initialize");
	}
	catch (pyembed::Python_exception ex){
		std::cout << ex.what() << '\n';
	}
}

void motor::setPWM(std::string a){
	try{
		pyembed::Arg_map args;
		args[a] = pyembed::Py_long;
		py->call("set_pwm",args);
	}
	catch (pyembed::Python_exception ex){
		std::cout << ex.what() << '\n';
	}
}

void motor::closePWM(){
	try{
		py->call("close_pwm");
	}
	catch (pyembed::Python_exception ex){
		std::cout << ex.what() << '\n';
	}
}
