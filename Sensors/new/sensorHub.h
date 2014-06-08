#ifndef sensorHub_H_
#define sensorHub_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

class sensorHub
{
public:
	sensorHub();
	std::string getAllData();
    std::string getDataMPU();    
private:
    void initializeMPU();

};

#endif /* sensorHub */
