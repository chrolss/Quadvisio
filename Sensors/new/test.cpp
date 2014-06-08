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

using namespace std;


int main(int argc, const char * argv[])
{
    printf("Initializing I2C devices...\n");
    mpu6050 mpu;
    printf("Testing device connections...\n");
    printf(mpu.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");
    return 0;
}

