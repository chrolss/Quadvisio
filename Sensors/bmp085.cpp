#include "bmp085.h"

bmp085::bmp085(){
	initialize();
	calibrate(); //probably need to calibrate a new 0-level each time we initiate it.
}

short int bmp085::i2cRead(char address){
	buf[0] = address;
	if (read(fd, buf, 1) != 1)
	{
	    printf("Unable to read from slave\n");
	    exit(1);
	}

	res = ((buf[0]<<8) & 0xFF00) | ((buf[0]>>8) & 0xFF);
	return res;
}

void bmp085::calibrate(){
	this->ac1 = i2cRead(0xAA);
	this->ac2 = i2cRead(0xAC);
	this->ac3 = i2cRead(0xAE);
	this->ac4 = i2cRead(0xB0);
	this->ac5 = i2cRead(0xB2);
	this->ac6 = i2cRead(0xB4);
	this->b1 = i2cRead(0xB6);
	this->b2 = i2cRead(0xB8);
	this->mb = i2cRead(0xBA);
	this->mc = i2cRead(0xBC);
	this->md = i2cRead(0xBE);
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
