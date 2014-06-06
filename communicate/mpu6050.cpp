#include <iostream>
#include "mpu6050.h"
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


using namespace std;

mpu6050::mpu6050() {
	initialize();
}

void mpu6050::initialize(){
	this-> fd = open(fileName, O_RDWR); // fd address, kept constant. Open port
	char *fileName = "/dev/i2c-1";                        // Name of the portwe will be using
    	int  address = 0x68;                              // Address of the SRF02 shifted right one bit
    	char buf[6];                              // Buffer for data being read/ written on the i2c bus
   	
    	

    	if ((fd = open(fileName, O_RDWR)) < 0) {               // Open port for reading and writing
        	printf("Failed to open i2c port\n");
       		exit(1);
    	}
    
    	if (ioctl(fd, I2C_SLAVE, address) < 0) {               // Set the port options and set the address of the device we wish to speak to
        	printf("Unable to get bus access to talk to slave\n");
        	exit(1);
    	}

    	buf[0] = 0x6b;          // Commands for performing a ranging CHANGED FROM 0x2d to 0x6b
   	buf[1] = 0;             //CHANGED FROM 0x18 to 0
   
    	if ((write(fd, buf, 2)) != 2) {                         // Write commands to the i2c port
        	printf("Error writing to i2c slave\n");
        	exit(1);
    	}
}

int mpu6050::readSensorData(){

	char *fileName = "/dev/i2c-1";
	int address = 0x68;
	char buf[6];
	double accX,accY,accZ;
	int x,y,z;


   	buf[0] = 0x3b;                                           // This is the register we wish to read from 59 or
   	if ((write(fd, buf, 1)) != 1) {                          // Send the register to read from
      		printf("Error writing to i2c slave\n");
      		exit(1);
   	}

    	usleep(1000);
    	memset(&buf,0,sizeof(buf));

    	if (read(fd, buf, 6) != 6) {                        // Read back data into buf[]
        	printf("Unable to read from slave\n");
        	exit(1);
    	}
    	else {
        	x=y=z=0;
	
        	x = buf[0]<<8;
        	x += buf[1];
        	y = buf[2]<<8;
        	y += buf[3];
        	z = buf[4]<<8;
        	z += buf[5];
        	if (x & 1<<15)
        	{
            		x -= 1<<16;
    		}
    		if (y & 1<<15)
    		{
        		y -= 1<<16;
    		}
    		if (z & 1<<15)
    		{
     		   	z -= 1<<16;
    		}
		this->accX = (double)x / 16384;
    		this->accY = (double)y / 16384;
    		this->accZ = (double)z / 16384;

   	}

   return 0;
}

mpu6050::~mpu6050(){}