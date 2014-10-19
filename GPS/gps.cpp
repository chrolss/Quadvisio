#include "gps.h"


gps::gps(std::string _devNum){
	this->devNum = _devNum;
	this->deviceName = deviceName.append(devNum);
	initialize();
}

void gps::initialize(){
	loadGPSDeviceTree(deviceName);
}

int gps::loadGPSDeviceTree(std::string _name){
	FILE *file = NULL;
	char line[256];

	const char *slots = slotsPath.c_str();

	//printf("Path to slots file: %s\n", slots);

	file = fopen(slots, "r+");
	if (!file) {
	    printf("Error trying to open slots\n");
	    return -1;
	}

	while (fgets(line, sizeof(line), file)) {
		if (strstr(line, _name)) {
	       printf("%s is already loaded\n", _name);
	       fclose(file);
	       return 1;
	    }
	}

	    fprintf(file, _name);
	    fclose(file);

	    return 0;
	}


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



