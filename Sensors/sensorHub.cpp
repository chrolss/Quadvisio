#include "sensorHub.h"


sensorHub::sensorHub()
{};

void intializeMPU(){
	mpu = new mpu6050;
}
	
void initializeADXL(){
	adxl = new adxl345;
}

std::string sensorHub::getAllData(){
	mpu->readSensorData();	
	double x = mpu->getAccX();
	double y = mpu->getAccY();
	double z = mpu->getAccZ();

}


