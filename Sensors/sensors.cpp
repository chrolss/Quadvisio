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

int main(int argc, char *argv[]){
/*
	double deg = 180/M_PI;
	kalman filter(0.1, 0.1, 0, 10);
	kalman filter2(0.1, 0.1, 0, 10);
	kalman headF(0.1,0.1,180,10);
	adxl345 adxl;
	hmc5883l hmc;
	while (true){
		adxl.readSensorData();
		hmc.readSensorData();
		double roll = adxl.getRoll();
		double pitch = adxl.getPitch();
		double roll2 = filter.estimate(roll);
		double pitch2 = filter2.estimate(pitch);
		hmc.getData(roll2,pitch2);
		double heading = headF.estimate(hmc.getX());
		//printf("-Roll: %f, -Pitch: %f \nRoll2: %f, Pitch2: %f \n", roll*deg, pitch*deg, roll2*deg, pitch2*deg);
		//printf("head: %f\n", heading);
		usleep(10000);
	}
	*/
/*

	hmc5883l hmc;
	for (int i = 0; i<1000; i++){
		hmc.readSensorData();
		hmc.getData(0.0, 0.35);
		int X = hmc.getX();
		printf("X: %d\n", X);
		usleep(200000);
	}
	l3g4200d l3g;
	kalman filter2(0.1,0.1,10,10);
	while (true){
		l3g.readSensorData();
		short x = l3g.getAngleX();
		//short y = l3g.getAngleY();
		//short z = l3g.getAngleZ();
		est = filter2.estimate(x);
		std::cout<< "measured x: " << x << ", and estimated: " 
<< est << std::endl;
	}
*/

	bmp085 bmp;
	bmp.readSensorData();
	bmp.readTemperature();
	double altitude = bmp.getAltitude();
	double pressure = bmp.getPressure();
	double temperature = bmp.getTemperature();
	std::cout << "Current altitude: " << altitude << " Current pressure: " << pressure << std::endl;
	std::cout << "Temperature: " << temperature << std::endl;
	usleep(100000);


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
