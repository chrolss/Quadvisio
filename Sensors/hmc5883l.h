#ifndef HMC5883L_H
#define HMC5883L_H

class hmc5883l{
public:
	hmc5883l();
	int readSensorData();
	double getHeading(){return heading;};
private:
	void initialize();
	int calibratie();

	double heading;
	char i2c_bus;
	int address;
	char buf[6];
	int fd;
	char *fileName;
	short hX, hY, hZ;
};


#endif /* HMC5883L_H_ */
