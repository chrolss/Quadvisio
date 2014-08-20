#include "Controller.h"
#include <iostream>
#include <cstdio>
#include <unistd.h>

double params[9];
double refs[3];
double in[6];
double ut[4];

double alpha;

Controller *controller;

int main(){

	params[0] = 0.9;
	params[1] = 0.3;
	params[2] = 0.2;
	params[3] = 0.9;
	params[4] = 0.3;
	params[5] = 0.2;
	params[6] = 0.6;
	params[7] = 0.3;
	params[8] = 0.2;

	for (int j = 0; j<6; j++){
		in[j] = 0;
	}

	refs[0] = 0;
	refs[1] = 0;
	refs[2] = 0;
	controller = new Controller;
	controller->setParameters(params);
	controller->setReference(refs);
	controller->setThrust(30);

	double input[10] = {0.0, 0.0, 0.0, 0.50, 0.50, 0.50, 0.50, 0.0, 0.0, 0.0};


	for (int i=0;i<10;i++)
	{
		in[3] = input[i];

		controller->calcPWM(in,ut);

		//printf("u1 = %f, u2 = %f, u3 = %f, u4 = %f \n", ut[0], ut[1], ut[2], ut[3]);
		sleep(1);
	}

}
