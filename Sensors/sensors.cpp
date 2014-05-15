#include <iostream>
#include <string>
#include <unistd.h>
#include "cadxl345.h"

// []
// {}

using namespace std;

int main(int argc, char *argv[]){
	cadxl345 adxl345;
	adxl345.readSensorData();
	short x = adxl345.getAccX();
	short y = adxl345.getAccY();
	short z = adxl345.getAccZ();

	std::cout<<"x:"<<x<<"\ty:"<<y<<"\tz:"<<z<<std::endl;

}
