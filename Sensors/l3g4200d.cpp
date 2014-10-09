#include <iostream>
#include "l3g4200d.h"
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

l3g4200d::l3g4200d(){
	initialize();
}

void l3g4200d::initialize(){
	this-> fd = open(fileName,O_RDWR);

	char *fileName = "/dev/i2c-1";
	int address = 0x69;
	char buf[6];

	if ((fd = open(fileName, O_RDWR)) < 0) {               // Open port for reading and writing
     		printf("Failed to open i2c port\n");
      		exit(1);
  	}

	if (ioctl(fd, I2C_SLAVE, address) < 0) {
	      		printf("Unable to get bus access to talk to slave\n");
	      		exit(1);
	   	}

	 buf[0] = CTRL_REG1;                                       // Commands for performing a ranging
  	 buf[1] = 0x0F;
   
   	if ((write(fd,buf,2)) != 2){
		std::cout << (write(fd,buf,2)) << std::endl;
		printf("Error writing to i2c slave\n");
		exit(1);
	}
   	// If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
   	

	buf[0] = CTRL_REG2;                                       // Commands for performing a ranging
   	buf[1] = 0x00;
   
   	if((write(fd,buf,2)) != 2)
   	{
       		printf("Failed to write\n");
		exit(1);
   	}
   	// Configure CTRL_REG3 to generate data ready interrupt on INT2
    	// No interrupts used on INT1, if you'd like to configure INT1
    	// or INT2 otherwise, consult the datasheet:
   	buf[0] = CTRL_REG3;                                       // Commands for performing a ranging
   	buf[1] = 0x08;
   
   	if((write(fd,buf,2)) != 2)
   	{
       		printf("Failed to write \n");
   		exit(1);
	}

   	buf[0] = CTRL_REG4;                                       // Commands for performing a ranging
   	buf[1] = 0x30;//0x30 - 2000
   
   	if((write(fd,buf,2)) != 2)
   	{
       		printf("Failed to write\n");
		exit(1);
   	}
/*
   	buf[0] = CTRL_REG5;                                       // Commands for performing a ranging
   	buf[1] = 0x00;
   
   	if((write(fd,buf,2)) != 2)
   	{
       		printf("Failed to write\n");
   		exit(1);
	}
	*/
}

int l3g4200d::readSensorData(){

	float G_GAIN = 0.07;
	float DT = 0.02; // loop period	
	char buf[7];
   	buf[0] = 0x28;  
	short x,y,z;                                     // This is the register we wish to read from
   	if ((write(fd, buf, 1)) != 1) {
		printf("Error writing to i2c slave\n");
		exit(1);
		return 0;
	}
   
   	if (read(fd, buf, 2) != 2) {                        // Read back data into buf[]
      		printf("Unable to read from slave\n");
      		return 0;
   	}
   	else {
      	rawX = (short)(buf[1]<<8) |  (short)buf[0];
      	printf("a: %d \t b: %d\n", buf[1], buf[0]);
   	}

   	buf[0] = 0x2A;
   	if ((write(fd, buf, 1)) != 1) {
		printf("Error writing to i2c slave\n");
		exit(1);
		return 0;
	}

   	if (read(fd, buf, 4) != 4) {                        // Read back data into buf[]
      		printf("Unable to read from slave\n");
      		return 0;
   	}
   	else{
       	rawY = (short)(buf[1]<<8) |  (short)buf[0];
       	rawZ = (short)(buf[3]<<8) |  (short)buf[2];
   	}



	
   	short gx,gy,gz;

   	float rate_gyr_x(0.0),rate_gyr_y(0.0),rate_gyr_z(0.0);
   	float gyroAngleX(0.0),gyroAngleY(0.0),gyroAngleZ(0.0);

   	float AccYangle(0.0),AccXangle(0.0);
   
   	float CFangleX = 0.0;
    	float CFangleY = 0.0;
   	
   	usleep(100000);
   
   	   //Convert Gyro raw to degrees per second
      	rate_gyr_x = (float)rawX * G_GAIN;
      	rate_gyr_y = (float)rawY * G_GAIN;
      	rate_gyr_z = (float)rawZ * G_GAIN;
      	printf("Gx: %d \t Gy: %d \t Gz: %d \n", rate_gyr_x, rate_gyr_y, rate_gyr_z);
      	//Calculate the angles from the gyro
      	this->gyroAngleX =rate_gyr_x*DT;
        this->gyroAngleY =rate_gyr_y*DT;
        this->gyroAngleZ =rate_gyr_z*DT;
        

	//Convert Accelerometer values to degrees
      	/*
	AccXangle = (float) (atan2(ay,az)+M_PI)*RAD_TO_DEG;
        AccYangle = (float) (atan2(ax,az)+M_PI)*RAD_TO_DEG;

         //Change the rotation value of the accelerometer to -/+ 180
        if (AccXangle >180)
        {
                AccXangle -= (float)360.0;
        }
        if (AccYangle >180)
                AccYangle -= (float)360.0;

       */

        return 0;


}

l3g4200d::~l3g4200d(){}
