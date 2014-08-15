#ifndef HMC5883L_H
#define HMC5883L_H
#define k 0.0041175
#define m 235.62

class hmc5883l{
public:
	hmc5883l();
	int readSensorData();
	double findHeading(double roll, double pitch);
	double getXHeading(){return headingX;};
	double getYHeading(){return headingY;};
	double getZHeading(){return hZ;};
private:
	void initialize();
	int calibrate();


	double heading;
	char i2c_bus;
	int address;
	char buf[6];
	int fd;
	char *fileName;
	double hX, hY, hZ;
	double headingX, headingY;
	double measuredMagX, measuredMagY, measuredMagZ;
	double cosRoll, cosPitch, sinRoll, sinPitch;
	double magScaleX, magScaleY, magScaleZ;
	double magOffsetX, magOffsetY, magOffsetZ;
	double tmp;
};


#endif /* HMC5883L_H_ */
