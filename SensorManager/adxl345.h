
#ifndef ADXL345_H
#define ADXL345_H

#define SCALE 0.004

class adxl345
{
public:
	adxl345();
	double getPitch();
	double getRoll();
	int readSensorData(); //When called, sensor data will be read and eventually returned as readable data
	short getAccX() {return accX;}
	short getAccY() {return accY;}
	short getAccZ() {return accZ;} // All three called by readSensorData() and will pass the values
	~adxl345();
		
private:
	char i2c_bus;
	int address;
	char buf[6];
	int fd;
	char *fileName;    

	short accX, accY, accZ;
	double pitch, roll;

	void initialize();
};

#endif /* ADXL345_H_ */
