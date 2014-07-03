#ifndef MPU6050_H_
#define MPU6050_H_

class mpu6050 {

private:
    int I2CBus;
    uint8_t I2CAdress;
    void convertAcc();
    
	uint8_t buf[14];
	int fd;
	char *fileName;
    
	int16_t accX, accY, accZ;
	int16_t ax,ay,az,gx,gy,gz;
    
    double pitch, roll, yaw;
    
	void initialize();

public:
	mpu6050(int bus, uint8_t adress);
	int8_t readRawMotion();
    
	double getAccX() {return accX;}
	double getAccY() {return accY;}
	double getAccZ() {return accZ;}
	virtual ~mpu6050();
};

#endif /* MPU6050_H_ */
