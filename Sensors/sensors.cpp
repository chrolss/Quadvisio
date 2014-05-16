#include <iostream>
#include <string>
#include <unistd.h>
#include "adxl345.h"
#include "mpu6050.h"

// []
// {}

using namespace std;

int main(int argc, char *argv[]){
	adxl345 adxl345;
	for (int i = 0; i < 20; i++){
		adxl345.readSensorData();
		short x = adxl345.getAccX();
		short y = adxl345.getAccY();
		short z = adxl345.getAccZ();
		std::cout<<"x:"<<x<<"\ty:"<<y<<"\tz:"<<z<<std::endl;
	}
}
