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
	double getPressure() {return pressure;}
	int readTemperature();
	short int i2cRead(char address);
	~bmp085();

private:
	char i2c_bus;
	int address;
	char buf[6];
	int fd;
	char *fileName;

	double alt, temp, pressure;

	short int ac1;
	short int ac2;
	short int ac3;
	unsigned short int ac4;
	unsigned short int ac5;
	unsigned short int ac6;
	short int b1;
	short int b2;
	short int mb;
	short int mc;
	short int md;
	int b5;
	short int res;

	void initialize();
	void calibrate();
};

#endif /* BMP085 */
