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
	kalman filter(0.01, 0.1, 10, 10);
	adxl345 adxl345;
	while (true){
		adxl345.readSensorData();
		short x = adxl345.getAccX();
		est = filter.estimate(x);
		//short y = adxl345.getAccY();
		//short z = adxl345.getAccZ();
		//std::cout<<"x:"<<x<<"\ty:"<<y<<"\tz:"<<z<<std::endl;
		std::cout << "measured: " << x << ", estimated: " << est << std::endl;
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


	bmp085 bmp;
	bmp.readSensorData();
	bmp.readTemperature();
	double altitude = bmp.getAltitude();
	double pressure = bmp.getPressure();
	double temperature = bmp.getTemperature();
	std::cout << "Current altitude: " << altitude << " Current pressure: " << pressure << std::endl;
	std::cout << "Temperature: " << temperature << std::endl;

*/
	hmc5883l hmc;
	hmc.readSensorData();
	double X = hmc.getXHeading();
	double Y = hmc.getYHeading();
	double Z = hmc.getZHeading();

	printf("X: %f, Y: %f, Z: %f\n", X, Y, Z);

}
