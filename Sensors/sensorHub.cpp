#include "sensorHub.h"


sensorHub::sensorHub()
{};

void sensorHub::initializeMPU(){
	mpu = new mpu6050;
}
	
void sensorHub::initializeADXL(){
	adxl = new adxl345;
}

std::string sensorHub::getAllData(){
	mpu->readSensorData();	
	double x = mpu->getAccX();
	double y = mpu->getAccY();
	double z = mpu->getAccZ();
    return "hej";
}


