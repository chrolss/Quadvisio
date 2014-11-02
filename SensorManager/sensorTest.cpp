#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <chrono>

#include "SensorManager.h"

using namespace std;

double input[9];
uint8_t devStatus;
bool runDMP=false;

double runTime;
int Hz = 80;
int loopSleep;

std::chrono::time_point<std::chrono::high_resolution_clock> start;

void print_sensor_data() {
    cout << "Acc x: " << input[0]*9.82/4096 << endl;
    cout << "Acc y: " << input[1]*9.82/4096 << endl;
    cout << "Acc z: " << input[2]*9.82/4096 << endl;
    cout << "Gyr roll: " << input[3]*180/M_PI << endl;
    cout << "Gyr pitch: " << input[4]*180/M_PI << endl;
    cout << "Gyr yaw: " << input[5]*180/M_PI << endl;
    cout << "Alt: " << input[6] << endl;
    cout << "Press: " << input[7] << endl;
    cout << "Temp: " << input[8] << endl;
}

int main(int argc, const char * argv[])
{
    
    SensorManager sm;
    printf("Testing device connections...\n");
    printf(sm.testMPU() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");
    
    usleep(1000000);
    

    printf("Initializing DMP...");
    if (sm.initializeMPUdmp()) {
        printf("DMP ready!\n");
        runDMP = true;
    }
    usleep(1000000);
    
    while (runDMP) {
        auto start = std::chrono::high_resolution_clock::now();
        sm.readDMP(input);
        sm.readBMP(input);
        print_sensor_data();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        
        loopSleep = 1000000/Hz - (int)duration;
        if (loopSleep>0) {
            usleep(loopSleep);
        }
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        runTime = double(1000000)/(duration2);
        cout << "Running at: " << runTime << "Hz" << endl;
    }
}