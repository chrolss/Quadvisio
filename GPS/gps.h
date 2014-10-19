#ifndef GPS_H
#define GPS_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <cstdio>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <string>

class gps
{
public:
	gps(std::string _devNum);						//constructor
	void readGPSData();						//reads serial port and updates the position
	void getGPSPosition(double *position);	//returns the coordinates to a position vector

private:
	int loadGPSDeviceTree(std::string _name);	//loads the device-tree overlay
	void initialize();						//sets the correct baud rates and read/write privelidges
	void checkFix();						//checks if there is a fix

	double longitude[3];		//degrees, minutes, seconds
	double latitude[3];			//degrees, minutes, seconds
	double altitude;			//meters
	bool fix;					//does it have a fix or not, changed by checkFix()

	std::string devNum;								//UART device number
	std::string slotsPath;							//path to the slots
	std::string deviceName = "ADAFRUIT-UART";		//name of dtbo file
};


#endif /* GPS_H_ */
