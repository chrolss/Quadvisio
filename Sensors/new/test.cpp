//
//  main.cpp
//  SensorsHub
//
//  Created by Toni Axelsson on 2014-05-29.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "mpu6050.h"
#include <linux/i2c-dev.h>


int16_t ax, ay, az;
int16_t gx, gy, gz;

using namespace std;

void setup() {
    // initialize device
    printf("Initializing I2C devices...\n");
    
    mpu6050 mpu;
    
    // verify connection
    printf("Testing device connections...\n");
    printf(mpu.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");
}

void loop() {
    // read raw accel/gyro measurements from device
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);
    
    // display accel/gyro x/y/z values
    printf("a/g: %6hd %6hd %6hd   %6hd %6hd %6hd\n",ax,ay,az,gx,gy,gz);
}

int main(int argc, const char * argv[])
{
    setup();
    
    for (;;)
        loop();
    
    return 0;
}

