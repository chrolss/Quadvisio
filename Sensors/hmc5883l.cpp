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

double hmc5883l::findHeading(double roll, double pitch){	//user input roll and pitch
	cosRoll = cos(roll);	//given in radians
	cosPitch = cos(pitch);
	sinRoll = sin(roll);
	sinPitch = sin(pitch);

	hX = ((double)measuredMagX * magScaleX + magOffsetX) * cosPitch + \
	     ((double)measuredMagY * magScaleY + magOffsetY) * sinRoll * sinPitch + \
	     ((double)measuredMagZ * magScaleZ + magOffsetZ) * cosRoll * sinPitch;

    hY = ((double)measuredMagY * magScaleY + magOffsetY) * cosRoll - \
         ((double)measuredMagZ * magScaleZ + magOffsetZ) * sinRoll;

    tmp = sqrt(hX*hX + hY*hY);


    this->headingX = hX/tmp;
    this->headingY = -hY/tmp;

    return 0.0;
}

void hmc5883l::initialize(){
	useconds_t dtime = 8; //delay for usleep
	char write0[4]; // command to set reg 0 - AKA Configuration Register A
	char write1[4]; // command to set reg 1 - AKA Configuration Register B
	char write2[4]; // command to set reg 2 - AKA Mode Register
	write0[0] = 0x00; // reg 00
	write0[1] = 0x70; // average 8 samples, 15Hz output
	write1[0] = 0x01; // reg 01
	write1[1] = 0xA0; // gain 5
	write2[0] = 0x02; // reg 02
	write2[1] = 0x01; // mode single measurement

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

   	// Find offset and scale readings
   	/*
   	this->magScaleX = 2.0 / (1.0 - (-1.0));
   	this->magOffsetX = -(magScaleX * (-1.0)) - 1.0;
   	this->magScaleY = 2.0 / (1.0 - (-1.0));
   	this->magOffsetY = -(magScaleY * (-1.0)) - 1.0;
   	this->magScaleZ = 2.0 / (1.0 - (-1.0));
   	this->magOffsetZ = -(magScaleZ * (-1.0)) - 1.0;
   	*/
   	this->magScaleX = 2.0;
   	this->magOffsetX = -(magScaleX * (-1.0)) - 1.0;
   	this->magScaleY = 2.0;
   	this->magOffsetY = -(magScaleY * (-1.0)) - 1.0;
   	this->magScaleZ = 2.0;
   	this->magOffsetZ = -(magScaleZ * (-1.0)) - 1.0;
   	calibrate();
}

int hmc5883l::calibrate(){
	this->calX = 1.0;
	this->calY = 1.0;
	this->calZ = 1.0;
	double expected_xy = 1264.4f;
	double expected_z = 1177.2f;
	readSensorData();

	this->calX = fabs(expected_xy / measuredMagX);
	this->calY = fabs(expected_xy / measuredMagY);
	this->calZ = fabs(expected_z / measuredMagZ);
	std::cout << "Calibration successfull" << std::endl;



	return 0;
}

int hmc5883l::readSensorData() {
	useconds_t dtime = 8; //delay for usleep
	char write0[4]; // command to set reg 0 - AKA Configuration Register A
	char write1[4]; // command to set reg 1 - AKA Configuration Register B
	char write2[4]; // command to set reg 2 - AKA Mode Register
	write0[0] = 0x00; // reg 00
	write0[1] = 0x70; // average 8 samples, 15Hz output
	write1[0] = 0x01; // reg 01
	write1[1] = 0xA0; // gain 5
	write2[0] = 0x02; // reg 02
	write2[1] = 0x01; // mode single measurement

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
	this->measuredMagX = (((short)buf[1]<<8) | (short) buf[0])*calX;	//byta plats gav inget
	this->measuredMagZ = -(((short)buf[3]<<8) | (short) buf[2])*calZ;	//z kommer föra y av ngn anledning
	this->measuredMagY = -(((short)buf[5]<<8) | (short) buf[4])*calY;

	return 0;
}

