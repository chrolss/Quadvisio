#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <iostream>

#ifndef BMP085_H
#define BMP085_H

class bmp085
{
public:
	bmp085();
	int readSensorData();
	double getAltitude() {return alt;}
	double getTemperature() {return temp;}
	~bmp085();

private:
	char i2c_bus;
	int address;
	char buf[6];
	int fd;
	char *fileName;

	double alt, temp;

	void initialize();
	void calibrate();
};

#endif /* BMP085 */
