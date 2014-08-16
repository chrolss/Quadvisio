#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <chrono>

#include "SensorManager.h"

double input[6];
uint8_t devStatus;
bool runDMP=false;

double runTime;
int Hz = 130;
int loopSleep;

std::chrono::time_point<std::chrono::high_resolution_clock> start;

int main(int argc, const char * argv[])
{
    int i;
    std::cout << "Do you want use raw data ot DMP data? (1 or 2)" << std::endl;
    std::cin >> i;
    
    SensorManager sm;
    printf("Initializing MPU...\n");
    //sm.initializeMPU();
    
    printf("Testing device connections...\n");
    printf(sm.testMPU() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");
    
    usleep(100000);
    
    if (i ==2){
        printf("Initializing DMP...");
        if (sm.initializeMPUdmp()) {
            printf("DMP ready!\n");
            runDMP = true;
        }
        usleep(100000);
    }
    
    while (runDMP) {
        auto start = std::chrono::high_resolution_clock::now();
        sm.readDMP(input);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        
        loopSleep = 1000000/Hz - (int)duration;
        if (loopSleep>0) {
            usleep(loopSleep);
        }
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        runTime = double(1000000)/(duration2);
        std::cout << "Running at: " << runTime << "Hz" << std::endl;
    }
    /*
    if (i==1){
        while (true) {
            sm.readMPU(input);
        }
    }
    */
}
