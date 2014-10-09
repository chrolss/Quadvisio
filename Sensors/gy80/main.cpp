#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <sys/time.h>
#include "Gyroscope.h"
#include "Accelerometer.h"

using std::vector;

float AA = 0.98; // complementary filter constant

int mymillis()
{
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return (tv.tv_sec) * 1000 + (tv.tv_usec)/1000;
}

int main(int argc, char **argv)
{

	int fd;
	char *fileName = "/dev/i2c-1";

	if ((fd = open(fileName, O_RDWR)) < 0) 
	{					// Open port for reading and writing
		printf("Failed to open i2c port\n");
		return false;
	}

	Accelerometer accel;
	GyroScope gyro;

	if(!accel.initialize(fd))
	{
		printf("Failed to init accel\n");
		return false;
	}	
	if(!gyro.initialize(fd))
	{
		printf("Failed to init gyro\n");
		return false;
	}		

	int startInt;	

	vector<short> accel_xyz;
	vector<float> accel_degrees;

	vector<short> gyro_xyz;
	vector<float> gyro_degrees;
	vector<float> gyro_angels;

	float CFangleX = 0.0;
    float CFangleY = 0.0;

	while(accel.read() && gyro.read())
	{
		startInt = mymillis();

		accel_xyz = accel.getxyz();
		accel_degrees = accel.get_degrees(); 

		gyro_xyz = gyro.getxyz();
		gyro_degrees = gyro.get_degrees();
		gyro_angels = gyro.get_angels();

		// Complementary filter used to combine the accelerometer and gyro values
		CFangleX=AA*(CFangleX+gyro_degrees[0]*DT) +(1 - AA) * accel_degrees[0];
        CFangleY=AA*(CFangleY+gyro_degrees[1]*DT) +(1 - AA) * accel_degrees[1];
        
        printf ("   GyroX  %7.3f \t AccXangle \e[m %7.3f \t \033[22;31mCFangleX %7.3f\033[0m\t GyroY  %7.3f \t AccYangle %7.3f \t \033[22;36mCFangleY %7.3f\t\033[0m\n",gyro_angels[0],accel_degrees[0],CFangleX,gyro_angels[1],accel_degrees[1],CFangleY);

        //Each loop should be at least 20ms.
        while(mymillis() - startInt < 20)
        {
            usleep(100);
        }	
	}



	return 0;
}