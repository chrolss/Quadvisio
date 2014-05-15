#ifndef CADXL345_H
#define CADXL345_H

class cadxl345
{
public:
	cadxl345();
	int readSensorData(); //When called, sensor data will be read and eventually returned as readable data
	short getAccX() {return accX;}
	short getAccY() {return accY;}
	short getAccZ() {return accZ;} // All three called by readSensorData() and will pass the values
	~cadxl345();
		
private:
	char i2c_bus;
	int address;
	char buf[6];
	int fd;
	char *fileName;    

	short accX, accY, accZ;

	void initialize();
};

#endif /* CADXL345_H_ */
