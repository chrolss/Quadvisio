//
//  main.cpp
//  MPU
//
//  Created by Toni Axelsson on 2014-06-08.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include <iostream>
#include "sensorHub.h"

int main(int argc, const char * argv[])
{
    sensorHub sensor;
    sensor.getAllData();

    return 0;
}

