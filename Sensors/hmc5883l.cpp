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

int hmc5883l::getData(double roll, double pitch){	//user input roll and pitch IN DEGREES
	if (roll>0.78){
		roll  = 0.78;
	}
	if (roll<-0.78){
		roll  = -0.78;
	}
	if (pitch>0.78){
		pitch  = 0.78;
	}
	if (pitch<-0.78){
		pitch  = -0.78;
	}
	double cos_roll = cos(roll);
	double cos_pitch = cos(pitch);
	double sin_roll = sin(roll);
	double sin_pitch = sin(pitch);
	double Xth = measuredX*sin(pitch)+77.0;
	double Yth = measuredY*sin(roll)+15;
	double tyh = measuredY + (pitch*180/M_PI)*10;
	double txh = measuredX + (roll*180/M_PI)*10;
	double testHead = atan2(Yth,Xth) * 180 / M_PI;
	int tmp2 = atan2(tyh,txh) * 180 / M_PI;
	int tmp = atan2(measuredY, measuredX) * 180 / M_PI;
	printf("Heading: %d\n", tmp);
	printf("Testhead: %d\n", tmp2);
	//printf("mX: %d, mY: %d, mZ: %d\n", measuredX, measuredY, measuredZ);
	//printf("xth: %f, yth: %f\n", Xth, Yth);
	Xh = (measuredX * cos(pitch)) + (measuredZ * sin(pitch));
	Yh = (measuredX * sin(roll) * sin(pitch)) + (measuredY * cos(roll)) - (measuredZ * sin(roll) * cos(pitch));
	tiltHeading = atan2(Yh,Xh) * 180 / M_PI;
	if (tiltHeading<0){
		tiltHeading = 360.0 + tiltHeading;
	}
	this->headingX = tiltHeading;
	std::cout << "Tilted Heading: " << tiltHeading << std::endl;
	/*
	int tmp = atan2(measuredY, measuredX) * 180 / M_PI;
	if (tmp<0){
		this->headingX = 360.0 + tmp;
	}
	else{
		this->headingX = tmp;
	}
	*/
	return 0.0;
}

void hmc5883l::initialize(){
	int address = 0x1E;
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
    unsigned char buf[16];
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

