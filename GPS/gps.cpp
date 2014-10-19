#include "gps.h"


gps::gps(int _device){
	this->device = _device;
	initialize();
}

void gps::initialize(){}

void gps::loadGPSDeviceTree(){}

void gps::checkFix(){}

void gps::readGPSData(){}

void gps::getGPSPosition(double *position){
	position[0] = longitude[0];
	position[1] = longitude[1];
	position[2] = longitude[2];
	position[3] = latitude[0];
	position[4] = latitude[1];
	position[5] = latitude[2];
	position[6] = altitude;

}



