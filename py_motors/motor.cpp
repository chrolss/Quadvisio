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

void motor::setPWM(std::string a, std::string b){
	try{
		args2[a] = pyembed::Py_long;
		args3[b] = pyembed::Py_long;
		py->call("set_pwm1",args2);
		py->call("set_pwm2",args3);
		args2.clear();
		args3.clear();
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
