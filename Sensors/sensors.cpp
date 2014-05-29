#include <iostream>
#include <string>
#include <unistd.h>
#include "adxl345.h"
#include "mpu6050.h"
#include "l3g4200d.h"

// []
// {}

using namespace std;

int main(int argc, char *argv[]){
		
	mpu6050 mpu;
	while (true){
        mpu.readSensorData();
        double x = mpu.getAccX();
        double y = mpu.getAccY();
        double z = mpu.getAccZ();
        std::cout<<"x:"<<x<<"\ty:"<<y<<"\tz:"<<z<<std::endl;
	}
/*

	adxl345 adxl;
	for (int i=0; i<20; i++){
	adxl.readSensorData();
	short x = adxl.getAccX();
	std::cout << "x: " << x << std::endl;
	}
*/
}
