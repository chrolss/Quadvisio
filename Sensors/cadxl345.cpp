#include <iostream>
#include "cadxl345.h"
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

#define acc_x_lsb 0

//    {
//     }
//    {}
using namespace std;

cadxl345::cadxl345() {
	initialize();
}

void cadxl345::initialize(){
	int fd;                                          
   	char *fileName = "/dev/i2c-1";                        
   	int  address = 0x53;                              
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

int cadxl345::readSensorData(){
	
	int fd;                                          
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

cadxl345::~cadxl345(){}

