#include <iostream>

#include "SensorManager.h"
#include "I2Cdev.h"

double input[6];

int main(int argc, const char * argv[])
{
    SensorManager sm;
    sm.initializeMPU();
    
    while (true) {
        sm.readMPU(input);
    }
    
}
