#include <iostream>

#include "SensorManager.h"
#include "I2Cdev.h"

int main(int argc, const char * argv[])
{
    SensorManager sm;
    sm.initializeMPU();
}
