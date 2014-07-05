#include <iostream>
#include <unistd.h>
#include <BlackLib/BlackLib.h>

float mapper(float b){
	float val = float(float(29.0/100.0)*b) + float(20); //Konverterar input 0 - 100 till pwmsignal
	return val;
}

BlackPWM pwm1(P8_13);
BlackPWM pwm2(P8_19);

float val;

int main(){
	pwm1.setRunState(run);
	pwm2.setRunState(run);
	sleep(1);
	pwm1.setPeriodTime(5000000);
	pwm2.setPeriodTime(5000000);
	sleep(1);
	pwm1.setDutyPercent(0.0);
	pwm2.setDutyPercent(0.0);
	sleep(1);
	pwm1.setDutyPercent(20.0);
	pwm2.setDutyPercent(20.0); //Speciellt för vår ESC
	sleep(1);
	while (true){
		printf("Give pwm value 0 - 100\n");
		std::cin >> val;
		if (val > 100){
			printf("Shutting down\n");
			pwm1.setDutyPercent(20.0);
			pwm2.setDutyPercent(20.0);
			pwm1.setRunState(stop);
			pwm2.setRunState(stop);
			exit(1);
		}
		pwm1.setDutyPercent(mapper(val));
		pwm2.setDutyPercent(mapper(val));
		}
}
