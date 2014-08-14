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

	useconds_t dtime = 8; //delay for usleep
	char write0[4]; // command to set reg 0 - AKA Configuration Register A
	char write1[4]; // command to set reg 1 - AKA Configuration Register B
	char write2[4]; // command to set reg 2 - AKA Mode Register
	write0[0] = 0x00; // reg 00
 	write0[1] = 0x70; // average 8 samples, 15Hz output
   	write1[0] = 0x01; // reg 01
   	write1[1] = 0xA0; // gain 5
   	write2[0] = 0x02; // reg 02
   	write2[1] = 0x01; // mode single measurement
	double heading;
	char i2c_bus;
	int address;
	char buf[6];
	int fd;
	char *fileName;
	short hX, hY, hZ;
};


#endif /* HMC5883L_H_ */
