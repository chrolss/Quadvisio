#include <iostream>
#include "motorControl.h"

motorControl PWM;
float a;

int main(){
	std::cin >> a;
	if (a < 101)
	{
		PWM.setPWM(a);
		std::cout << "Duty cycle set to: " << a << " %" << std::endl;
	}

	else
	{
		std::cout << "Quitting" << std::endl;
		PWM.closePWM();
	}



}
