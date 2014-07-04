#include <iostream>
#include "mpu6050.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>

using namespace std;
#define MAX_BUS 64

mpu6050::mpu6050( int bus, uint8_t adress) {
    I2CBus = bus;
    I2CAdress = adress;
}

void mpu6050::initialize() {
    
    std::cout << "Setting clock source..." << std::endl;
    setClockSource(MPU6050_CLOCK_PLL_XGYRO);
    std::cout << "Setting full gyro range..." << std::endl;
    setFullScaleGyroRange(MPU6050_GYRO_FS_250);
    std::cout << "Setting full acceleration range..." << std::endl;
    setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    setSleep(false);

    std::cout << "MPU initialized!" << std::endl;
}

void mpu6050::getMotion(double* dax, double* day, double* daz, double* dgx, double* dgy, double* dgz) {
    I2Cdev::readBytes(I2CAdress, MPU6050_RA_ACCEL_XOUT_H, 14, buf);
    ax = (((int16_t)buf[0]) << 8) | buf[1];
    ay = (((int16_t)buf[2]) << 8) | buf[3];
    az = (((int16_t)buf[4]) << 8) | buf[5];
    gx = (((int16_t)buf[8]) << 8) | buf[9];
    gy = (((int16_t)buf[10]) << 8) | buf[11];
    gz = (((int16_t)buf[12]) << 8) | buf[13];
    
    *dax = (double)ax / 16384;
    
    
    /*
    this->accX = (double)x / 16384;
    this->accY = (double)y / 16384;
    this->accZ = (double)z / 16384;
     */
}

void mpu6050::setSleep(bool enabled) {
    I2Cdev::writeBit(I2CAdress, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}

void mpu6050::setClockSource(uint8_t source) {
    I2Cdev::writeBits(I2CAdress, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}

void mpu6050::setFullScaleAccelRange(uint8_t range) {
    I2Cdev::writeBits(I2CAdress, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}

void mpu6050::setFullScaleGyroRange(uint8_t range) {
    I2Cdev::writeBits(I2CAdress, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}


mpu6050::~mpu6050(){}
