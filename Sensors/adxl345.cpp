

#include <iostream>
#include "adxl345.h"
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



//    {
//     }
//    {}
using namespace std;

adxl345::adxl345() {
	initialize();
}

void adxl345::initialize(){
	this-> fd = open(fileName, O_RDWR);  //fd blir en address till den öppna porten och måste vara en och samma genom hela klassen. Den får inte omdeklareras i readSensorData() och och måste då ha en this-> 
                                         
   	char *fileName = "/dev/i2c-1";                        
   	int address = 0x53;
   	char buf[6];                              
   	short accX,accY,accZ;
   	if ((fd = open(fileName, O_RDWR)) < 0) {               // Open port for reading and writing
     		printf("Failed to open i2c port\n");
      		exit(1);
   	}

   	if (ioctl(fd, I2C_SLAVE, address) < 0) {
      		printf("Unable to get bus access to talk to slave\n");
      		exit(1);
   	}
   	buf[0] = 0x2d;                                       // Commands for performing a ranging
   	buf[1] = 0x18;
   
   	if ((write(fd, buf, 2)) != 2) {                        // Write commands to the i2c port
      		printf("Error writing to i2c slave\n");
      		exit(1);
   	}

   	buf[0] = 0x31;                                       // Commands for performing a ranging
   	buf[1] = 0x09;
   
   	if ((write(fd, buf, 2)) != 2) {                        // Write commands to the i2c port
      		printf("Error writing to i2c slave\n");
      		exit(1);
   	}
}

double adxl345::getRoll(){
	double tmp = sqrt(double (accX*accX) + double (accZ *accZ));
	double roll = atan2(accY,tmp)*180/M_PI;

	return roll;
}

double adxl345::getPitch(){
	double tmp = sqrt(double (accY*accY) + double (accZ *accZ));
	double pitch = atan2(accX,tmp)*180/M_PI;

	return pitch;

}

int adxl345::readSensorData(){
	
	//int fd;                                          
   	char *fileName = "/dev/i2c-1";                        
   	int  address = 0x53;                              
   	char buf[6];                              
   	short accX,accY,accZ;
	
	buf[0] = 0x32;                                       // This is the register we wish to read from
   	if ((write(fd, buf, 1)) != 1) {                        // Send the register to read from
      		printf("Error writing to i2c slave\n");
      		exit(1);
   	}
   	

	usleep(1000);
  	memset(&buf,0,sizeof(buf));
   	if (read(fd, buf, 6) != 6) {                        // Read back data into buf[]
      		printf("Unable to read from slave\n");
      		exit(1);
   	}
   	else 
	{ 
	accX=accY=accZ=0;

	this->accX = ((short)buf[1]<<8) | (short) buf[0];
    this->accY = ((short)buf[3]<<8) | (short) buf[2];
    this->accZ = ((short)buf[5]<<8) | (short) buf[4];


	return 0;
	}
}

adxl345::~adxl345(){}

