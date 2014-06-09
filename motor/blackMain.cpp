#include <iostream>
#include "motorControl.h"

motorControl PWM;
float a;

int main(){
	while (true)
	{
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


}
