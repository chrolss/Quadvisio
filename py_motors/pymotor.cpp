#include "pymotor.h"

motor::motor(int argc,char** argv){
	try{
		py = new pyembed::Python(argc, argv);
		py->load("pypwm");
		double a[4] = {22.0,23.0,24.0,25.0};
		py->call("initialize",a);
	}
	catch (pyembed::Python_exception ex){
		std::cout << ex.what() << '\n';
	}
}

double motor::mapper(double b){
	double val = (double(double(29.0/100.0)*b) + double(20)); //Konverterar input 0 - 100 till pwmsignal
	return val;
}

void motor::setPWM(double* d){
	try{
		for (int i = 0; i < 4; i++){
			d[i] = mapper(d[i]);
		}
		py->call("set_pwm",d);
	}
	catch (pyembed::Python_exception ex){
		std::cout << ex.what() << '\n';
	}
}


void motor::closePWM(){
	try{
		double b[4] = {0.0,0.0,0.0,0.0};
		py->call("close_pwm",b);
	}
	catch (pyembed::Python_exception ex){
		std::cout << ex.what() << '\n';
	}
}
