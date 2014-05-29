#ifndef sensorHub_H_
#define sensorHub_H_

#include <string>
#include "adxl345.h"
#include "mpu6050.h"


class sensorHub
{
public:
	sensorHub();
	std::string getAllData();
	void initializeMPU();
	void initializeADXL();
private:
	mpu6050 *mpu;
	adxl345 *adxl;

};

#endif /* sensorHub */
