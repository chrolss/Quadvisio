#include <iostream>
#include "motorControl.h"

motorControl PWM;
float a;

int main(){
	while (true)
	{
		std::cout << "Enter RPM level (0-100%)" << std::endl;
		std::cin >> a;
		if (a < 101)
		{
			PWM.setPWM(a);
			std::cout << "RPM Level set to: " << a << " %" << std::endl;
		}

		else
		{
			std::cout << "Quitting" << std::endl;
			PWM.closePWM();
			break;
		}
	}


}
