#include "bmp085.h"

bmp085::bmp085(){
	initialize();
	calibrate(); //probably need to calibrate a new 0-level each time we initiate it.
}


void bmp085::initialize(){
	char *fileName = "/dev/i2c-1";
	int address = 0x77; //correct port
	char buf[6];

	this-> fd = open(fileName, O_RDWR);

	if ((fd = open(fileName, O_RDWR)) < 0) {               // Open port for reading and writing
     		printf("Failed to open i2c port\n");
      		exit(1);
   	}

   	if (ioctl(fd, I2C_SLAVE, address) < 0) {
      		printf("Unable to get bus access to talk to slave\n");
      		exit(1);
   	}



}

int bmp085::readSensorData(){

	return 0;
}

bmp085::~bmp085(){}
