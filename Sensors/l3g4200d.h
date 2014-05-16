#ifndef L3G4200D_H_
#define L3G4200D_H_

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22  
#define CTRL_REG4 0x23  // CTRL_REG4 controls the full-scale range, among other things:
#define CTRL_REG5 0x24 


class l3g4200d
{
public:
	l3g4200d();
	int readSensorData();
	short getAccX() {return accX;}
	short getAccY() {return accY;}
	short getAccZ() {return accZ;}
	~l3d4200d();

private:
	char i2c_bus;
	int address;
	char buf[6];
	int fd;
	char *fileName;

	short accX, accY, accZ;
	
	void initialize();
	
};

#endif /* L3G4200D_H_ */

