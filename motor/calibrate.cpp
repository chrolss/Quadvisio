#include <iostream>
#include <unistd.h>
#include "motorControl.h"

int input;
int input2;

int main()
	{
	motorControl pwm13;
	float percent = 0.0;
	float duty = 0.0;
	std::cout << "set max, waiting for user" << std::endl;
	std::cin >> input;
	pwm13.setPWM(100);
	std::cout << "set bottom, waiting for user" << std::endl;
	std::cin >> input2;
	pwm13.setPWM(0);
	}
