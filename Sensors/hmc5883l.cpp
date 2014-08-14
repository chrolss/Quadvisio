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

int hmc5883l::findHeading(short _x, short _z){
	if (_z > 0){
		heading = k*_x + m;
	}
	else{
		heading = 360 - k*_x - m;
	}
	return heading;
}

void hmc5883l::initialize(){

   	char *fileName = "/dev/i2c-1";
   	int address = 0x1e;					//korrekta addressen
   	char buf[10];

   	this-> fd = open(fileName, O_RDWR);  //fd

   	if (ioctl(fd, I2C_SLAVE, address) < 0) {
      		printf("Unable to get bus access to talk to slave\n");
      		exit(1);
   	}

   	if (write(fd,write0,2) != 2) {
   	   printf("Write to zero failed\n");
   	}
   	//Set reg 1
   	if (write(fd,write1,2) != 2) {
   	   printf("Write to one failed\n");
   	}
   	//Set reg 2
   	if (write(fd,write2,2) != 2) {
   	   printf("Write to two failed\n");
   	}
}



int hmc5883l::readSensorData() {

	if (write(fd,write0,2) != 2) {
	   printf("Write to zero failed\n");
	}
	//Set reg 1
	if (write(fd,write1,2) != 2) {
	   printf("Write to one failed\n");
	}
	//Set reg 2
	if (write(fd,write2,2) != 2) {
	   printf("Write to two failed\n");
	}

	//datasheet says to delay here.
	if ( usleep(dtime)  < 0) {
	   printf("sleep error\n");
	}

	//read the 6 data.
	if (read(fd, buf, 6) != 6) {
	   printf("Read failed\n");
	}
	short hX = ((short)buf[1]<<8) | (short) buf[0];
	short hY = ((short)buf[3]<<8) | (short) buf[2];
	short hZ = ((short)buf[5]<<8) | (short) buf[4];
	this->heading = findHeading(hX,hZ);
	return 0;
}

