#ifndef GPS_H
#define GPS_H


class gps
{
public:
	gps(int _device);						//constructor
	void readGPSData();						//reads serial port and updates the position
	void getGPSPosition(double *position);	//returns the coordinates to a position vector

private:
	void loadGPSDeviceTree();	//loads the device-tree overlay
	void initialize();						//sets the correct baud rates and read/write privelidges
	void checkFix();						//checks if there is a fix

	double longitude[3];		//degrees, minutes, seconds
	double latitude[3];			//degrees, minutes, seconds
	double altitude;			//meters
	bool fix;					//does it have a fix or not, changed by checkFix()
	int device;					//UART device number
};


#endif /* GPS_H_ */
