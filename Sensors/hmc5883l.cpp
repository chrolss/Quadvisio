#include <iostream>
#include "hmc5883l.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

using namespace std;

hmc5883l::hmc5883l() {
	initialize();
}

void hmc5883l::getData(double roll, double pitch){	//user input roll and pitch
	double angle = atan2(measuredY, measuredX) * 180 / M_PI;
    printf("angle = %0.1f\n\n", angle);

}

void hmc5883l::initialize(){
	char buf[2];
	this-> fd = open("/dev/i2c-1", O_RDWR);	//open port
	if (ioctl(fd, I2C_SLAVE, address) < 0){
		printf("Unable to open hmc5883l port\n");
		exit(1);
	}
	buf[0] = 0x01;
	buf[1] = 32;
	if(write(fd,buf,2)!=2){
		printf("Unable to write to device\n");
		exit(1);
	}
	buf[0] = 0x02;
	buf[1] = 0;
	if(write(fd,buf,2)!=2){
		printf("Unable to write to device\n");
		exit(1);
	}
}

int hmc5883l::readSensorData() {
	buf[0] = 0x03;

	if ((write(fd, buf, 1)) != 1)	//send to register we want to read
	{
		printf("Unable to point to register\n");
		exit(1);
	}

	if (read(fd, buf, 6) != 6) {
		printf("Unable to read from hmc5883l\n");
		exit(1);
	}
	else {
	            this->measuredX = (buf[0] << 8) | buf[1];
	            this->measuredY = (buf[4] << 8) | buf[5];
	            this->measuredZ = (buf[2] << 8) | buf[3];
	}
	return 0;
}

