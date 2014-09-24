#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <Sensors/adxl345.h>
#include <Kalman/kalman.h>
#include "math.h"

adxl345 adxl;			//sensor
double ax, ay, az;		//read acceleration values from adxl
double roll, pitch;		//read angles from adxl
double T = 0.1;			//length of one loop in seconds
double vx, vx0;			//velocity in x-direction
double values[8];		//vector carrying all important values

void estimate(double *vector){
	double abx = vector[0] - sin(vector[4])*1.0;	//calculate the body acc in x-dir
	vector[6] = vector[7] + abx*vector[5];			//return new vx velocity
}
double est;

kalman filter(0.1, 0.1, 0, 10);

int main(){
	for (int i = 0; i < 10000; i++){
		adxl.readSensorData();
		ax = adxl.getAccX();
		ay = adxl.getAccY();
		az = adxl.getAccZ();
		roll = adxl.getRoll();
		pitch = adxl.getPitch();
		values[0] = ax/256;
		values[1] = ay/256;
		values[2] = az/256;
		values[3] = roll;
		values[4] = pitch;
		values[5] = T;
		values[6] = vx;
		values[7] = vx0;
		estimate(values);
		est = filter.estimate(values[6]);
		//printf("azT: %f, roll: %f \n", values[2], values[3]);
		//printf("ax: %f, axb: %f, vx: %f\n", values[0], values[0] - sin(values[4])*1.0, values[6]);
		printf("vx: %f\n", est);


		usleep(100000);
	}



}
