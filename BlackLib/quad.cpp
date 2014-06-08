//Test program for BlackLib, written for Quadvisio

#include <iostream>
#include <unistd.h>
#include "BlackLib.h"

using namespace std;

int main()
	{
	BlackPWM	pwm13(EHRPWM2B);

	float percent = 0.0;

	pwm13.setPeriodTime(5000000);
	pwm13.setDutyPercent(0.0);

	sleep(1);

	while (true)
		{
		cout << "Duty cycle: " << pwm13.getDutyValue() << endl;

		if (pwm13.fail(BlackPWM::outOfRangeErr))
			cout << "New percentage out of range" << endl;

		sleep(1);
		pwm13.setDutyPercent(percent);
		percent += 5.0;
		}
	}
