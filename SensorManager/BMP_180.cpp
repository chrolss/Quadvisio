//
//  BMP_180.cpp
//  BMP_180
//
//  Created by Toni Axelsson on 2014-11-01.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "BMP_180.h"

BMP180::BMP180() {
    
}

void BMP180::initialize(OversamplingSetting oss_) {

    oss = oss_;
    
    if (oss == OSS_LOW) {wait = 4500;}
    else if (oss == OSS_STANDARD) {wait = 7500;}
    else if (oss == OSS_HIGH) {wait = 13500;}
    else {wait = 25500;}
    
    fd = open("/dev/i2c-1", O_RDWR);
    
    if (fd < 0) {
        std::cout << strerror(errno) << std::endl;
        return;
    }
    
    if (ioctl(fd, I2C_SLAVE, 0x77) < 0) {
        std::cout << strerror(errno) << std::endl;
        return;
    }
    
    read_calibration_data();
    
}

void BMP180::read_calibration_data() {
    
    ac1 = read_adress(0xaa);
    std::cout << "AC1 = " << ac1 << std::endl;
    ac2 = read_adress(0xac);
    std::cout << "AC2 = " << ac2 << std::endl;
    ac3 = read_adress(0xae);
    std::cout << "AC3 = " << ac3 << std::endl;
    ac4 = (uint16_t)read_adress(0xb0);
    std::cout << "AC4 = " << ac4 << std::endl;
    ac5 = (uint16_t)read_adress(0xb2);
    std::cout << "AC5 = " << ac5 << std::endl;
    ac6 = (uint16_t)read_adress(0xb4);
    std::cout << "AC6 = " << ac6 << std::endl;
    b1 = read_adress(0xb6);
    std::cout << "B1 = " << b1 << std::endl;
    b2 = read_adress(0xb8);
    std::cout << "B2 = " << b2 << std::endl;
    mb = read_adress(0xba);
    std::cout << "MB = " << mb << std::endl;
    mc = read_adress(0xbc);
    std::cout << "MC = " << mc << std::endl;
    md = read_adress(0xbe);
    std::cout << "MD = " << md << std::endl;
}

void BMP180::get_sensor_data(struct bmp180_data *data) {
    ut = read_uncom_temp();
    up = read_uncom_press();
    
    x1 = (ut - ac6)*ac5 >> 15;
    x2 = (mc << 11) / (x1 + md);
    b5 = x1 +x2;
    
    // true temperature
    t = (b5 + 8) >> 4;
    
    b6 = b5 - 4000;
    x1 = (b2 * (b6 * b6 >> 12)) >> 11;
    x2 = ac2 * b6 >> 11;
    x3 = x1 + x2;
    b3 = (((ac1 * 4 + x3) << oss) + 2) >> 2;
    x1 = ac3 * b6 >> 13;
    x2 = (b1 * (b6 * b6 >> 12)) >> 16;
    x3 = ((x1 + x2) + 2) >> 2;
    b4 = ac4 * (unsigned long)(x3 + 32768) >> 15;
    b7 = ((unsigned long)up - b3) * (50000 >> oss);
    if (b7 < 0x80000000) p = (b7 * 2) / b4;
    else p = (b7/b4) * 2;
    long p8 = p >> 8;
    x1 = p8 * p8;
    x1 *= 3038;
    x1 >>= 16;
    x2 = (-7357 * p) >> 16;
    p += (x1 + x2 + 3791) >> 4;
    
    data->temperature = t;
    data->pressure = p;
    data->altitude = get_altitude();
}

long BMP180::read_uncom_temp() {
    memset(&buf,0,sizeof(buf));
    buf[0] = 0xf4;
    buf[1] = 0x2e;
    write(fd, buf, 2);
    usleep(4500);
    memset(&buf,0,sizeof(buf));
    buf[0] = 0xf6;
    write(fd, buf, 1);
    memset(&buf,0,sizeof(buf));
    read(fd, buf, 2);
    
    return (long)(buf[0] << 8) + buf[1];
}

long BMP180::read_uncom_press() {
    memset(&buf,0,sizeof(buf));
    buf[0] = 0xf4;
    buf[1] = 0x34 + (oss << 6);
    write(fd, buf, 2);
    
    usleep(wait);
    memset(&buf,0,sizeof(buf));
    buf[0] = 0xf6;
    write(fd, buf, 1);
    memset(&buf,0,sizeof(buf));
    read(fd, buf, 3);
    return (long) ((buf[0] << 16) + (buf[1] << 8) + buf[2]) >> (8-oss);
}

float BMP180::get_altitude() {
    double x = pow(((double)p / 101.325), ALT_EXP);
    return (float)(44330.0 * (1.0 - x));
}

int16_t BMP180::read_adress(int addr) {
    memset(&buf,0,sizeof(buf));

    buf[0] = addr;
    write(fd, buf, 1);
    
    memset(&buf,0,sizeof(buf));
    read(fd, buf, 2);
    
    int16_t ac1_le = (buf[0] << 8 ) | (buf[1] & 0xff);
    
    return (ac1_le >> 8) | (ac1_le << 8);
}
