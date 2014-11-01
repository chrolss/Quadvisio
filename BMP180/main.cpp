//
//  main.cpp
//  BMP_180
//
//  Created by Toni Axelsson on 2014-11-01.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "BMP_180.h"

using namespace std;

int main(int arc, const char *argv[]) {
    
    BMP180::OversamplingSetting oss;
    if (atoi(argv[1])==0) {oss = BMP180::OSS_LOW;}
    else if (atoi(argv[1])==1) {oss = BMP180::OSS_STANDARD;}
    else if (atoi(argv[1])==2) {oss = BMP180::OSS_HIGH;}
    else if (atoi(argv[1])==3) {oss = BMP180::OSS_ULTRAHIGH;}
    else {
        cout << "Wring argument" << endl;
        return 0;
    }
    
    BMP180 bmp;
    bmp.initialize(oss);
    
    struct bmp180_data *bmp_data;
    bmp_data = new bmp180_data;
    
    while (true) {
        bmp.get_sensor_data(bmp_data);
        std::cout << "Altitude: " << bmp_data->altitude << std::endl;
        std::cout << "Temperature: " << bmp_data->temperature << std::endl;
        std::cout << "Pressure: " << bmp_data->pressure << std::endl;
    }
    
    return 0;
}
