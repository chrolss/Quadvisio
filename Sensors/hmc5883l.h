#ifndef HMC5883L_H
#define HMC5883L_H

#define degToRad 0.01745

class hmc5883l{
public:
	hmc5883l();
	int readSensorData();
	int getData(double roll, double pitch);
	int getX(){return headingX;}
	int getY(){return headingY;}
	int getZ(){return headingZ;}
	short getMX(){return measuredX;}
	short getMY(){return measuredY;}
	short getMZ(){return measuredZ;}
private:
	void initialize();

	double heading;
	char i2c_bus;
	int address;
	char buf[6];
	int fd;
	char *fileName;
	double Xh, Yh;
	int headingX, headingY, headingZ, tiltHeading;
	short measuredX, measuredY, measuredZ;
};


#endif /* HMC5883L_H_ */
