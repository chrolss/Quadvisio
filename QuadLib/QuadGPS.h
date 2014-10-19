#ifndef QuadGPS_H
#define QUadGPS_H

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
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <termios.h>

#include "QuadCore.h"

class QuadGPS : protected QuadCore
{
public:
	QuadGPS();						//constructor
	void readGPSData();						//reads serial port and updates the position
	void getGPSPosition(double *position);	//returns the coordinates to a position vector

private:
	void initialize();						//sets the correct baud rates and read/write privelidges
	void checkFix();						//checks if there is a fix

	double longitude[3];		//degrees, minutes, seconds
	double latitude[3];			//degrees, minutes, seconds
	double altitude;			//meters
	bool fix;					//does it have a fix or not, changed by checkFix()
	int fd;
};


#endif /* GPS_H_ */
