#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <chrono>
#include <math.h>

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
    cout << "Acc x: " << double(input[0]*9.82/4096.0) << endl;
    cout << "Acc y: " << double(input[1]*9.82/4096.0) << endl;
    cout << "Acc z: " << double(input[2]*9.82/4096.0) << endl;
    cout << "Gyr roll: " << input[3]*180/M_PI << endl;
    cout << "Gyr pitch: " << input[4]*180/M_PI << endl;
    cout << "Gyr yaw: " << input[5]*180/M_PI << endl;
    cout << "Alt: " << input[6] << endl;
    cout << "Press: " << input[7] << endl;
    cout << "Temp: " << input[8] << endl;
    
    double c1 = -sin(input[4])*double(input[0]/4096.0);
    double c2 = sin(input[3])*cos(input[4])*double(input[1]/4096.0);
    double c3 = cos(input[3])*cos(input[4])*double(input[2]/4096.0);
    double z = c1 + c2 + c3;
    
    cout << c1 << " " << c2 << " " << c3 << endl;
    cout << "Gravity component: " << z << endl;
}

int main(int argc, const char * argv[])
{
    BMP180::OversamplingSetting oss;
    if (atoi(argv[1])==0) {oss = BMP180::OSS_LOW;}
    else if (atoi(argv[1])==1) {oss = BMP180::OSS_STANDARD;}
    else if (atoi(argv[1])==2) {oss = BMP180::OSS_HIGH;}
    else if (atoi(argv[1])==3) {oss = BMP180::OSS_ULTRAHIGH;}
    else {
        cout << "Wrong argument" << endl;
        return 0;
    }

    
    SensorManager sm(oss);
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
        //print_sensor_data();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        
        loopSleep = 1000000/Hz - (int)duration;
        if (loopSleep>0) {
            //usleep(loopSleep);
        }
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        runTime = double(1000000)/(duration2);
        cout << "Running at: " << runTime << "Hz" << endl;
    }
}
