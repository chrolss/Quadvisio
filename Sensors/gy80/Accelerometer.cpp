#include "Accelerometer.h"
std::vector<float> Accelerometer::get_degrees()
{
	std::vector<float> degrees;
	degrees.push_back(AccXangle);
	degrees.push_back(AccYangle);	

	return degrees;
}
bool Accelerometer::read()
{
	if(!selectDevice(fd,ADXL345_ADDRESS,"ADXL345"))
		return false;
	char buf[6];
	buf[0] = 0x32;													// This is the register we wish to read from
	if(!writeToDevice(fd,buf,2))
	{
 		return false;
	}
	
	if (::read(fd, buf, 6) != 6) {								// Read back data into buf[]
		printf("Unable to read from slave\n");
		return false;
	}
	else {

		x = (buf[1]<<8) |  buf[0]; 
 		y = (buf[3]<<8) |  buf[2];
 		z = (buf[5]<<8) |  buf[4];

 		//Convert Accelerometer values to degrees
		AccXangle = (float) (atan2(y,z)+M_PI)*RAD_TO_DEG;
        AccYangle = (float) (atan2(x,z)+M_PI)*RAD_TO_DEG;
	}
	return true;
}
bool Accelerometer::initialize(const int & fd)
{
	this->fd = fd;
	char buf[2];
	
	if(!selectDevice(fd,ADXL345_ADDRESS,"ADXL345"))
		return false;
	

	buf[0] = 0x2d;													// Commands for performing a ranging
	buf[1] = 0x18;
	
	if(!writeToDevice(fd,buf,2))
	{
 		return false;
	}

	

	buf[0] = 0x31;													// Commands for performing a ranging
	buf[1] = 0x0A; //09 4g , A 8g
	
	if(!writeToDevice(fd,buf,2))
	{
 		return false;
	}
	return true;
}