#include <iostream>

#include "SensorManager.h"
#include "I2Cdev.h"

double input[6];

int main(int argc, const char * argv[])
{
    SensorManager sm;
    sm.initializeMPU();
    sm.readMPU(input);
    
    for (int i = 0; i<6; i++) {
        std::cout  << input[i] << std::endl;
    }
}
