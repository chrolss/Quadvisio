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
	for (int i = 0; i < 20; i++){
        mpu.readSensorData();
        double x = mpu.getAccX();
        double y = mpu.getAccY();
        double z = mpu.getAccZ();
        std::cout<<"x:"<<x<<"\ty:"<<y<<"\tz:"<<z<<std::endl;
	}
}
