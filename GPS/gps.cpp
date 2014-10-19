#include "gps.h"


gps::gps(int _device){
	this->device = _device;
	initialize();
}

void gps::initialize(){
	deviceName = std::string query(deviceName + std::to_string(device));
}

void gps::loadGPSDeviceTree(){
	//printf("Inside loadDeviceTree\n");

	//const char *name = pwmName.c_str();

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
		if (strstr(line, name)) {
	       printf("%s is already loaded\n", name);
	       fclose(file);
	       return 1;
	    }
	}

	    fprintf(file, name);
	    fclose(file);

	    return 0;
	}
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



