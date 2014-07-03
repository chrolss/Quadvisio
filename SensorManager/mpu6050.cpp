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

mpu6050::mpu6050( int bus, uint8_t adress) {
    I2CBus = bus;
    I2CAdress = adress;
}

void mpu6050::initialize() {

    char namebuf[MAX_BUS];

    snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBus);
    
    // Open port for reading and writing
    if ((fd = open(namebuf, O_RDWR)) < 0) {
        printf("Failed to open i2c port\n");
        exit(1);
    }
    
    // Set the port options and set the address of the device we wish to speak to
    if (ioctl(fd, I2C_SLAVE, I2CAdress) < 0) {
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

int8_t mpu6050::readRawMotion()
{
    int8_t count = 0;
    buf[0] = 0x3b;
    // This is the register we wish to
   	if ((write(fd, buf, 1)) != 1) {
        printf("Error writing to i2c slave\n");
        return(-1);
   	}

    usleep(1000);
    memset(&buf,0,sizeof(buf));

    count = read(fd, buf, 14);
    if ( count != 14) {                        // Read back data into buf[]
        fprintf(stderr, "Short read  from device, expected %d, got %d\n", 14, count);
        return(-1);
    }
    else {
        convertAcc();
   	}
    
    return count;
}

void mpu6050::convertAcc()
{
	
    ax = (((int16_t)buf[0]) << 8) | buf[1];
    ay = (((int16_t)buf[2]) << 8) | buf[3];
    az = (((int16_t)buf[4]) << 8) | buf[5];
    gx = (((int16_t)buf[8]) << 8) | buf[9];
    gy = (((int16_t)buf[10]) << 8) | buf[11];
    gz = (((int16_t)buf[12]) << 8) | buf[13];
    /*
    this->accX = (double)x / 16384;
    this->accY = (double)y / 16384;
    this->accZ = (double)z / 16384;
     */
}

mpu6050::~mpu6050(){}
