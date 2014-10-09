#pragma once
#include <stdio.h>
#include "Sensors.h"
#include <vector>
const short  L3G4200D_ADDRESS = 0x69;
const float G_GAIN = 0.07;
const float DT = 0.02; // [s/loop] loop period. 20ms


#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22  
#define CTRL_REG4 0x23  // CTRL_REG4 controls the full-scale range, among other things:
#define CTRL_REG5 0x24  // CTRL_REG5 controls high-pass filtering of outputs

class GyroScope : private Sensors
{
	
	float rate_gyr_x , rate_gyr_y, rate_gyr_z;
	float gyroXangle,gyroYangle,gyroZangle;
public:
	
	GyroScope():rate_gyr_x(0.0),rate_gyr_y(0.0),rate_gyr_z(0.0),gyroXangle(0.0),gyroYangle(0.0),gyroZangle(0.0){}
	bool initialize(const int & fd);
	bool read();

	using  Sensors::getxyz;

	std::vector<float> get_degrees();
	std::vector<float> get_angels();
};