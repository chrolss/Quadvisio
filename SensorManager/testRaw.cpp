#include <iostream>

#include "SensorManager.h"
#include "I2Cdev.h"

int16_t input[6];

int main(int argc, const char * argv[])
{
    SensorManager sm;
    sm.initializeMPU();
    sm.readMPU(input);
}
