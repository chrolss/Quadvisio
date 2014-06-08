#ifndef sensorHub_H_
#define sensorHub_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

class sensorHub
{
public:
	sensorHub();
	std::string getAllData();
    std::string getDataMPU();    
private:

};

#endif /* sensorHub */
