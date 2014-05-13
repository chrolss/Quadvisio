#ifndet CADXL345_H
#define CADXL345_H

class CADXL345
{
public:
	CADXL345();
	~CADXL345();
		
private:
	char i2c_bus;
	int address;
	char buf[6];	
	void getSensorReadings();
};

#endif
