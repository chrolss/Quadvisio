#include "Gyroscope.h"
std::vector<float> GyroScope::get_degrees()
{
	std::vector<float> degrees;
	degrees.push_back(rate_gyr_x);
	degrees.push_back(rate_gyr_y);
	degrees.push_back(rate_gyr_z);

	return degrees;
}
std::vector<float> GyroScope::get_angels()
{
	std::vector<float> angels;
	angels.push_back(gyroXangle);
	angels.push_back(gyroYangle);
	angels.push_back(gyroZangle);

	return angels;
}
bool GyroScope::read()
{
	if(!selectDevice(fd,L3G4200D_ADDRESS,"L3G4200D"))
		return false;

	char buf[6];
	buf[0] = 0x28;													// This is the register we wish to read from
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
 		
 		//Convert Gyro raw to degrees per second
		rate_gyr_x = (float)x * G_GAIN;
		rate_gyr_y = (float)y * G_GAIN;
		rate_gyr_z = (float)z * G_GAIN;
		//Calculate the angles from the gyro
		gyroXangle+=rate_gyr_x*DT;
        gyroYangle+=rate_gyr_y*DT;
        gyroZangle+=rate_gyr_z*DT;




	}
	return true;
}
bool GyroScope::initialize(const int & fd)
{
	this->fd = fd;
	char buf[2];

	if(!selectDevice(fd,L3G4200D_ADDRESS,"L3G4200D"))
		return false;
	 // Enable x, y, z and turn off power down:
	buf[0] = CTRL_REG1;													// Commands for performing a ranging
	buf[1] = 0x0F;
	
	if(!writeToDevice(fd,buf,2))
	{
 		return false;
	}
	// If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
	buf[0] = CTRL_REG2;													// Commands for performing a ranging
	buf[1] = 0x00;
	
	if(!writeToDevice(fd,buf,2))
	{
 		return false;
	}
	// Configure CTRL_REG3 to generate data ready interrupt on INT2
    // No interrupts used on INT1, if you'd like to configure INT1
    // or INT2 otherwise, consult the datasheet:
	buf[0] = CTRL_REG3;													// Commands for performing a ranging
	buf[1] = 0x08;
	
	if(!writeToDevice(fd,buf,2))
	{
 		return false;
	}

	buf[0] = CTRL_REG4;													// Commands for performing a ranging
	buf[1] = 0x30;//0x30 - 2000
	
	if(!writeToDevice(fd,buf,2))
	{
 		return false;
	}

	buf[0] = CTRL_REG5;													// Commands for performing a ranging
	buf[1] = 0x00;
	
	if(!writeToDevice(fd,buf,2))
	{
 		return false;
	}

return true;
}