//Test program for BlackLib, written for Quadvisio

#include <iostream>
#include <unistd.h>
#include <BlackLib/BlackLib.h>

using namespace std;

int main()
	{
	BlackPWM	pwm13(EHRPWM2B);
	pwm13.setRunState(run);
	float percent = 0.0;
	float duty = 0.0;

	pwm13.setPeriodTime(5000000);
	pwm13.setDutyPercent(0.0);

	sleep(1);

	while (true)
		{
		cout << "Set new duty cycle: " << endl;
		cin >> duty;

		if (duty > 100)
			break;

		if (pwm13.fail(BlackPWM::outOfRangeErr))
			cout << "New percentage out of range" << endl;


		pwm13.setDutyPercent(duty);
		}
	}
