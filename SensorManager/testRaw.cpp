#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include "SensorManager.h"

double input[6];
uint8_t devStatus;
bool runDMP=false;

int main(int argc, const char * argv[])
{
    int i;
    std::cout << "Do you want use raw data ot DMP data? (1 or 2)" << std::endl;
    std::cin >> i;
    
    SensorManager sm;
    printf("Initializing MPU...\n");
    sm.initializeMPU();
    
    printf("Testing device connections...\n");
    printf(sm.testMPU() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");
    
    usleep(100000);
    
    printf("Initializing DMP...\n");
    if (sm.initializeMPUdmp() && i ==2){
        printf("DMP ready!\n");
        runDMP = true;
        usleep(100000);
    }
    
    while (runDMP) {
        sm.readDMP();
    }
    
    if (i==1){
        while (true) {
            sm.readMPU(input);
        }
    }
    
}
