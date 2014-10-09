#pragma once
#include "Sensors.h"
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <vector>

const short  ADXL345_ADDRESS = 0x53;
const float RAD_TO_DEG = 57.29578; 

class Accelerometer : private Sensors
{
  

	float AccYangle ,AccXangle;
public:
	Accelerometer():AccYangle(0.0),AccXangle(0.0){}
	virtual bool initialize(const int & fd);
	std::vector<float> get_degrees();
	using  Sensors::getxyz;
	bool read();
};