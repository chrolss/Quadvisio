#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include "adxl345.h"
#include "mpu6050.h"
#include "l3g4200d.h"
#include "bmp085.h"
#include "hmc5883l.h"
#include <Kalman/kalman.h>

// []
// {}

using namespace std;

short est;
double min1 = 110.0;
double max1 = -100.0;

int find_min_max(double &input){
	if (input > max1){
		max1 = input;
		printf("New max at %f\n", max1);
		return 0;
	}
	else if(input < min1){
		min1 = input;
		printf("New min at %f\n", min1);
		return 0;
	}
	else
		printf("Max: %f, min: %f, current: %f \n", max1, min1, input);
		return 0;
}

int main(int argc, char *argv[]){
/*
	double deg = 180/M_PI;
	kalman filter(0.1, 0.1, 0, 10);
	kalman filter2(0.1, 0.1, 0, 10);
	kalman headF(0.1,0.1,180,10);
	adxl345 adxl;
	while (true){
		adxl.readSensorData();
		double roll = adxl.getRoll();
		double pitch = adxl.getPitch();
		double roll2 = filter.estimate(roll);	//error of 0.3 degrees
		double pitch2 = filter2.estimate(pitch); //error of 1.35 degrees
		find_min_max(pitch);
		usleep(10000);
	}



	hmc5883l hmc;
	for (int i = 0; i<1000; i++){
		hmc.readSensorData();
		hmc.getData(0.0, 0.35);
		int X = hmc.getX();
		printf("X: %d\n", X);
		usleep(200000);
	}
*/
	l3g4200d l3g;
	kalman filter2(0.1,0.1,10,10);
	while (true){
		l3g.readSensorData();
		short xr = l3g.getRawX();
		short yr = l3g.getRawY();
		short zr = l3g.getRawZ();
		short x = l3g.getAngleX();
		short y = l3g.getAngleY();
		short z = l3g.getAngleZ();
		est = filter2.estimate(x);
		//printf("X: %d, Y: %d, Z: %d\n", x, y ,z);
		printf("rX: %d, rY: %d. rZ: %d\n", xr, yr, zr);
	}

/*
	bmp085 bmp;
	bmp.readSensorData();
	bmp.readTemperature();
	double altitude = bmp.getAltitude();
	double pressure = bmp.getPressure();
	double temperature = bmp.getTemperature();
	std::cout << "Current altitude: " << altitude << " Current pressure: " << pressure << std::endl;
	std::cout << "Temperature: " << temperature << std::endl;
	usleep(100000);

*/
	/*
	int a;
	while(true){
	printf("Place chip in correct direction, press 1 to continue\n");
	std::cin >> a;
	for (int i = 0; i<5; i++){
			hmc.readSensorData();
			usleep(100000);
	}
	printf("X: %f, Y: %f, Z: %f\n", hmc.getXHeading(), hmc.getYHeading(), hmc.getZHeading());
	}
	*/
	/*
	int a;
	double N[2], S[2], W[2], E[2];
	printf("Point it towards north, press enter to continue\n");
	std::cin >> a;
	for (int i = 0; i<5; i++){
		hmc.readSensorData();
		usleep(100000);
	}
	hmc.findHeading(0.0, 0.0);
	N[0] = hmc.getXHeading();
	N[1] = hmc.getYHeading();

	printf("Point it towards east, press enter to continue\n");
	std::cin >> a;
	for (int i = 0; i<5; i++){
		hmc.readSensorData();
		usleep(100000);
	}
	hmc.findHeading(0.0, 0.0);
	E[0] = hmc.getXHeading();
	E[1] = hmc.getYHeading();

	printf("Point it towards south, press enter to continue\n");
	std::cin >> a;
	for (int i = 0; i<5; i++){
		hmc.readSensorData();
		usleep(100000);
	}
	hmc.findHeading(0.0, 0.0);
	S[0] = hmc.getXHeading();
	S[1] = hmc.getYHeading();

	printf("Point it towards west, press enter to continue\n");
	std::cin >> a;
	for (int i = 0; i<5; i++){
		hmc.readSensorData();
		usleep(100000);
	}
	hmc.findHeading(0.0, 0.0);
	W[0] = hmc.getXHeading();
	W[1] = hmc.getYHeading();

	printf("North, X: %f, Y: %f\n",N[0],N[1]);
	printf("East, X: %f, Y: %f\n",E[0],E[1]);
	printf("South, X: %f, Y: %f\n",S[0],S[1]);
	printf("West, X: %f, Y: %f\n",W[0],W[1]);

*/




}
