#ifndef MPU6050_H_
#define MPU6050_H_

#include <linux/i2c-dev.h>

class mpu6050
{
public:
	mpu6050();
	int readSensorData();
	double getAccX() {return accX;}
	double getAccY() {return accY;}
	double getAccZ() {return accZ;}
	~mpu6050();

private:
    
    void convertAcc();
    
	char i2c_bus;
	int address;
	char buf[6];
	int fd;
	char *fileName;

	double accX, accY, accZ;
	int x,y,z;	

	void initialize();

};

#endif /* MPU6050_H_ */
