#ifndef HMC5883L_H
#define HMC5883L_H

class hmc5883l{
public:
	hmc5883l();
	int readSensorData();
	void getData(double roll, double pitch);
	double getXHeading(){return headingX;};
	double getYHeading(){return headingY;};
	double getZHeading(){return headingZ;};
private:
	void initialize();
	int calibrate();


	double heading;
	char i2c_bus;
	int address = 0x1E;
	char buf[6];
	int fd;
	char *fileName;
	double headingX, headingY, headingZ;
	double measuredX, measuredY, measuredZ;
	double cosRoll, cosPitch, sinRoll, sinPitch;
	double tmp;
};


#endif /* HMC5883L_H_ */
