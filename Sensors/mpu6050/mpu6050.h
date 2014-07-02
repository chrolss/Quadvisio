#ifndef MPU6050_H_
#define MPU6050_H_

class mpu6050 {

private:
    int I2CBus, I2CAdress
    void convertAcc();
    
	char i2c_bus;
	int address;
	char buf[6];
	int fd;
	char *fileName;
    
	double accX, accY, accZ;
	int x,y,z;
    
    double pitch, roll, yaw;
    
	void initialize();

public:
	mpu6050(int bus, int adress);
	int readSensorData();
	double getAccX() {return accX;}
	double getAccY() {return accY;}
	double getAccZ() {return accZ;}
	virtual ~mpu6050();
};

#endif /* MPU6050_H_ */
