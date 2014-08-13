#include <iostream>
#include "hmc5883l.h"
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

hmc5883l::hmc5883l() {
	initialize();
}

void hmc5883l::initialize(){
	this-> fd = open(fileName, O_RDWR);  //fd blir en address till den öppna porten och måste vara en och samma genom hela klassen. Den får inte omdeklareras i readSensorData() och och måste då ha en this->

   	char *fileName = "/dev/i2c-1";
   	int address = 0x1e;					//korrekta addressen
   	char buf[8];

   	if ((fd = open(fileName, O_RDWR)) < 0) {               // Open port for reading and writing
     		printf("Failed to open i2c port\n");
      		exit(1);
   	}

   	if (ioctl(fd, I2C_SLAVE, address) < 0) {
      		printf("Unable to get bus access to talk to slave\n");
      		exit(1);
   	}

   	buf[0] = 0x3C;                                       // wake up
   	buf[1] = 0x00;
   	buf[2] = 0x70;

   	if ((write(fd, buf, 3)) != 3) {                        // Write commands to the i2c port
      		printf("Error writing to i2c slave\n");
      		exit(1);
   	}

   	buf[0] = 0x3C;                                       // Set gain to 5
   	buf[1] = 0x01;
   	buf[2] = 0xA0;

   	if ((write(fd, buf, 3)) != 3) {                        // Write commands to the i2c port
      		printf("Error writing to i2c slave\n");
      		exit(1);
   	}

   	buf[0] = 0x3C;                                       // Set continous measuring mode
   	buf[1] = 0x02;
   	buf[2] = 0x00;

   	if ((write(fd, buf, 3)) != 3) {                        // Write commands to the i2c port
   	      	printf("Error writing to i2c slave\n");
   	      	exit(1);
   	}
}

int hmc5883l::readSensorData() {

	buf[0] = 0x3D;
	buf[1] = 0x06;
	                                     			// Skriv "read-kod" och till vilken address vi vill läsa ifrån
	if ((write(fd, buf, 2)) != 2) {                        // Send the register to read from
	    printf("Error writing to i2c slave\n");
	    exit(1);
	}

	usleep(1000);
	memset(&buf,0,sizeof(buf));
	if (read(fd, buf, 6) != 6) {                        // Read back data into buf[]
	      	printf("Unable to read from slave\n");
	      	exit(1);
	}


	this->hX = ((short)buf[1]<<8) | (short) buf[0];
	this->hY = ((short)buf[3]<<8) | (short) buf[2];
	this->hZ = ((short)buf[5]<<8) | (short) buf[4];

	return 0;
}

