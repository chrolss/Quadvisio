#include <iostream>
#include "pyembed.h"
#include <string>
#include "pymotor.h"
#include <sstream>

using namespace pyembed;
double p1;
double p2;
//Speed Test

/*
int main(int argc, char** argv){
	motor motor(argc, argv);
	sleep(1);
	for (double i = 20.0; i < 30.0; i=i+0.001){
		strs << i;
		printf("PWM is at %f\n", i);
		std::string str = strs.str();
		motor.setPWM(str);
		strs.str("");
		strs.clear();
		sleep(0.4);
	}
	motor.closePWM();
}
*/

//Manual Test

std::string val2;
int main(int argc, char** argv){
	motor motor(argc, argv);
	double input_pwm[4];
	for (int i = 0; i < 5; i++)
	{
		printf("Give a PWM value, 0 - 100: \n");
		std::cin >> p1;
		for (int i = 0; i < 4; i++){
			input_pwm[i] = p1;
		}
		motor.setPWM(input_pwm);
		printf("Duty cycle set \n");
	}
	motor.closePWM();
}



/*
int main(int argc, char** argv){
	try{
		Python py(argc, argv);
		py.load("pwm");
		py.call("initialize");

		Arg_map args;
		printf("Give a PWM value 20 - 49: \n");
		std::cin >> val;
		args[val] = Py_long;
		py.call("set_pwm",args);
		sleep(1);
		std::cin >> val;
		args[val] = Py_long;
		py.call("set_pwm",args);
		sleep(1);
		py.call("close_pwm");


	}
	catch (Python_exception ex)
	{
		std::cout << ex.what() << '\n';
	}


}
*/




