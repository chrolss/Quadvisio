#pragma once
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <cmath>


class Sensors
{
	
public:
	short x,y,z;
	int fd;
	bool selectDevice(int i2c, int addr, char * name);
	bool writeToDevice(int i2c, char * buf, int len);
	virtual bool initialize(const int & fd) = 0;
	virtual bool read() = 0 ;
	virtual std::vector<float> get_degrees() = 0;
	virtual ~Sensors(){}
	const std::vector<short> getxyz();
	
};