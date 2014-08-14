#include "bmp085.h"

bmp085::bmp085(){
	initialize();
	calibrate(); //probably need to calibrate a new 0-level each time we initiate it.
}

short int bmp085::i2cRead(char address){
	buf[0] = address;
	if (read(fd, buf, 2) != 2)
	{
	    printf("Unable to read from slave\n");
	    exit(1);
	}

	res = ((buf[0]<<8) & 0xFF00) | ((buf[1]>>8) & 0xFF);
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
	int up = 0;
	int oss = 0;
	buf[0] = 0xF4;
	buf[1] = 0x34 + (oss<<6); //kommer från oversampling setting = 3

	if (write(fd,buf,2) != 2){
		printf("Failed to write to i2c bus");
		exit(1);
	}
	usleep((2 + (3<<oss)) * 1000);

	buf[0] = 0xF6;
	if ((write(fd, buf, 1)) != 1) {                        // Send the register to read from
	      	printf("Error writing to i2c slave\n");
	      	exit(1);
	}

	if (read(fd, buf, 3) != 3)
	{
	      	printf("Unable to read from slave\n");
	      	exit(1);
	}
	else
	{
		int up = ((int) buf[0] << 16) | (int) buf[1] << 8 | (int) buf[2] >> (8-oss); //uncompensated pressure reading
		//int up = (((int)buf[0] << 16) + ((int)buf[1] << 8) + ((int)buf[2]) >> (8 - oss));
		printf("Up = %d \n",up);
	}

	int x1, x2, x3, b3, b6, p;
	unsigned int b4, b7;
	std::cout << "börjar räkna" << std::endl;
	b6 = b5 - 4000;
	x1 = (b2 * (b6 * b6)>>12)>>11;
	x2 = (ac2 * b6)>>11;
	x3 = x1 + x2;
	b3 = (((((int)ac1)*4 + x3)<<oss) + 2)>>2;

	x1 = (ac3 * b6)>>13;
	x2 = (b1 * ((b6 * b6)>>12))>>16;
	x3 = ((x1 + x2) + 2)>>2;
	b4 = (ac4 * (unsigned int)(x3 + 32768))>>15;

	b7 = ((unsigned int)(up - b3) * (50000>>oss));
	if (b7 < 0x80000000)
		p = (b7<<1)/b4;
	else
		p = (b7/b4)<<1;

	x1 = (p>>8) * (p>>8);
	x1 = (x1 * 3038)>>16;
	x2 = (-7357 * p)>>16;
	p += (x1 + x2 + 3791)>>4; //final pressure value

	this->pressure = p;

	double A = p/101794.58;
	double B = 1.0/5.25588;
	double C = pow(A,B);
	C = 1 - C;
	C = C / 0.0000225577;

	this->alt = C;

	return 0;
}


bmp085::~bmp085(){}
