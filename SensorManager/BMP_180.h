//
//  BMP_180.h
//  BMP_180
//
//  Created by Toni Axelsson on 2014-11-01.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#ifndef __BMP_180__BMP_180__
#define __BMP_180__BMP_180__

#include <stdio.h>
#include <string>
#include <exception>
#include <inttypes.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define ALT_EXP 0.190294957

struct bmp180_data {
    double altitude;
    double pressure;
    double temperature;
};

class BMP180 {
    
public:
    enum OversamplingSetting {
        OSS_LOW = 0,
        OSS_STANDARD = 1,
        OSS_HIGH = 2,
        OSS_ULTRAHIGH = 3
    };
    
    BMP180();
    void initialize(OversamplingSetting oss_);
    void get_sensor_data(struct bmp180_data *data);
    
private:
    void read_calibration_data();
    int16_t read_adress(int addr);
    long read_uncom_temp();
    long read_uncom_press();
    float get_altitude();
        
    int fd;
    int wait;
    
    char buf[3];
    
    OversamplingSetting oss;
    
    int16_t ac1;
    int16_t ac2;
    int16_t ac3;
    uint16_t ac4;
    uint16_t ac5;
    uint16_t ac6;
    int16_t b1;
    int16_t b2;
    int16_t mb;
    int16_t mc;
    int16_t md;
    
    long ut, up, x1, x2, x3, b3, b5, b6, t, p;
    unsigned long b4, b7;
};

#endif /* defined(__BMP_180__BMP_180__) */
