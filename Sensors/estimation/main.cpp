#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include "adxl345.h"
#include <Kalman/kalman.h>
#include "math.h"

adxl345 adxl;			//sensor
double ax, ay, az;		//read acceleration values from adxl
double roll, pitch;		//read angles from adxl
double T = 0.1;			//length of one loop in seconds
double values[8] = {&ax &ay &az &roll &pitch &T &vx &vx0};		//vector carrying all important values
double vx, vx0;				//velocity in x-direction

void estimate(double *vector){
	double abx = vector[0] - cos(vector[5]*1.0);	//calculate the body acc in x-dir
	vector[7] = vector[8] + abx*vector[6];			//return new vx velocity
}

int main(){
	for (int i = 0; i < 100; i++){
		adxl.readSensorData();
		ax = adxl.getAccX();
		ay = adxl.getAccY();
		az = adxl.getAccZ();
		roll = adxl.getRoll();
		pitch = adxl.getPitch();
		estimate(values);
		printf("ax: %f, axb: %f, vx: %f\n", values[0], values[0] - cos(values[5])*1.0, values[6]);



		usleep(500000);
	}



}
