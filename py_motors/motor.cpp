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
	return stm.str();
}

void motor::setPWM(float a, float b, float c, float d){
	try{
		std::string e = mapper(a);
		std::string f = mapper(b);
		std::string g = mapper(c);
		std::string h = mapper(d);
		args1[e] = pyembed::Py_long;
		args2[f] = pyembed::Py_long;
		args3[g] = pyembed::Py_long;
		args4[h] = pyembed::Py_long;
		py->call("set_pwm1",args1);
		py->call("set_pwm2",args2);
		py->call("set_pwm3",args3);
		py->call("set_pwm4",args4);
		args1.clear();
		args2.clear();
		args3.clear();
		args4.clear();
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
