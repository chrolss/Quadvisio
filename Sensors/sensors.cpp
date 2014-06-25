#include <iostream>
#include <string>
#include <unistd.h>
#include "adxl345.h"
#include "mpu6050.h"
#include "l3g4200d.h"
#include <Kalman/kalman.h>

// []
// {}

using namespace std;

short est;

int main(int argc, char *argv[]){

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

/*
	l3g4200d l3g;
	while (true){
		l3g.readSensorData();
		short x = l3g.getAngleX();
		short y = l3g.getAngleY();
		short z = l3g.getAngleZ();
		std::cout << "x: " << x << "\ty: " << y << "\tz: " << z << std::endl;
	}
*/
}
