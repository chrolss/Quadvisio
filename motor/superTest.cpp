#include <iostream>
#include <unistd.h>
#include <BlackLib/BlackLib.h>
#include <vector>

float mapper(float b){
	float val = float(float(29.0/100.0)*b) + float(20); //Konverterar input 0 - 100 till pwmsignal
	return val;
}


BlackPWM* pwms[] = {new BlackPWM(P8_13), new BlackPWM(P8_19)};

float val;

int main(){
	pwms[0]->setRunState(run);
	usleep(1000);
	pwms[1]->setRunState(run);
	usleep(1000);
	pwms[0]->setPeriodTime(5000000);
	usleep(1000);
	pwms[1]->setPeriodTime(5000000);
	usleep(1000);
	pwms[0]->setDutyPercent(0.0);
	usleep(1000);
	pwms[1]->setDutyPercent(0.0);
	usleep(1000);
	pwms[0]->setDutyPercent(20.0);
	usleep(1000);
	pwms[1]->setDutyPercent(20.0); //Speciellt för vår ESC
	usleep(1000);
	while (true){
		printf("Give pwm value 0 - 100\n");
		std::cin >> val;
		if (val > 100){
			printf("Shutting down\n");
			pwms[0]->setDutyPercent(20.0);
			pwms[1]->setDutyPercent(20.0);
			pwms[0]->setRunState(stop);
			pwms[1]->setRunState(stop);
			exit(1);
		}
		pwms[0]->setDutyPercent(mapper(val));
		pwms[1]->setDutyPercent(mapper(val));
		}
}
