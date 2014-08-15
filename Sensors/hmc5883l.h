#ifndef HMC5883L_H
#define HMC5883L_H
#define k 0.0041175
#define m 235.62

class hmc5883l{
public:
	hmc5883l();
	int readSensorData();
	int findHeading(short _x, short _z);
	double getXHeading(){return heading;};
	double getYHeading(){return hY;};
	double getZHeading(){return hZ;};
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
