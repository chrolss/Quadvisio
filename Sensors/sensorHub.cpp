#include "sensorHub.h"


sensorHub::sensorHub()
{};

void sensorHub::initializeMPU(){
	mpu = new mpu6050;
}
	
void sensorHub::initializeADXL(){
	adxl = new adxl345;
}

std::string sensorHub::getAllData()
{
    return "hej";
}

std::string sensorHub::getDataMPU()
{
    mpu->readSensorData();

    double x = mpu->getAccX();
	double y = mpu->getAccY();
	double z = mpu->getAccZ();
    
    std::ostringstream strs;
    strs << x << " " << y << " " << z;
    std::string str = strs.str();
    
    return str;
}


