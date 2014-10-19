#include "QuadGPS.h"


QuadGPS::QuadGPS(){
	initialize();
}

void QuadGPS::initialize(){}

void QuadGPS::checkFix(){}

void QuadGPS::readGPSData(){}

void QuadGPS::getGPSPosition(double *position){
	position[0] = longitude[0];
	position[1] = longitude[1];
	position[2] = longitude[2];
	position[3] = latitude[0];
	position[4] = latitude[1];
	position[5] = latitude[2];
	position[6] = altitude;

}



