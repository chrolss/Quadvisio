#include <iostream>
#include "pyembed.h"
#include <string>
#include "motor.h"
#include <sstream>

using namespace pyembed;
std::ostringstream strs;
std::string val;
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


int main(int argc, char** argv){
	motor motor(argc, argv);
	for (int i = 0; i < 3; i++)
	{
		printf("Give a PWM value, 20 - 49: \n");
		std::cin >> val;
		motor.setPWM(val);
		printf("Duty cycle set \n");
		sleep(2);
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




