#include <iostream>
#include "mpu6050.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>


using namespace std;
#define MAX_BUS 64

mpu6050::mpu6050( int bus, int adress) {
    I2CBus = bus;
    I2CAdress = adress
	initialize();
}

void mpu6050::initialize(){
	
    char namebuf[MAX_BUS];
    
    snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBus);
    
    int file;
    
    // Open port for reading and writing
    if ((file = open(namebuf, O_RDWR)) < 0) {
        printf("Failed to open i2c port\n");
        exit(1);
    }
    
    // Set the port options and set the address of the device we wish to speak to
    if (ioctl(fd, I2C_SLAVE, I2CAddress) < 0) {
        printf("Unable to get bus access to talk to slave\n");
        exit(1);
    }

    // Wake up the mpu6050 by sending a wake-up call to adress 0x6b
    buf[0] = 0x6b;
   	buf[1] = 0;
   
    if ((write(fd, buf, 2)) != 2) {
        printf("Error writing to i2c slave\n");
        exit(1);
    }
}

int mpu6050::readSensorData()
{
   	buf[0] = 0x3b;                                  // This is the register we wish to
   	if ((write(fd, buf, 1)) != 1) {                 // Send the register to read from
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
        convertAcc();
   	}

   return 0;
}

void mpu6050::convertAcc()
{
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

mpu6050::~mpu6050(){}
