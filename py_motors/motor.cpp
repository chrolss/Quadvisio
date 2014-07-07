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

std::string motor::mapper(float b){
	float val = float(float(29.0/100.0)*b) + float(20); //Konverterar input 0 - 100 till pwmsignal
	std::ostringstream stm;
	stm << val;
	return stm.str();;
}

void motor::setPWM(float a, float b){
	try{
		std::string c = mapper(a);
		std::string d = mapper(b);
		args2[c] = pyembed::Py_long;
		args3[d] = pyembed::Py_long;
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
