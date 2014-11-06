//
//  SensorManager.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "SensorManager.h"
#include "MPU6050_6AXIS_MOTIONAPPS20.h"

MPU6050 *mpu;
BMP180 *bmp;
kalman *vz_filter;
kalman *hz_filter;


Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector

SensorManager::SensorManager(BMP180::OversamplingSetting oss){
    vz_est = 0.0;
    hz_est = 0.0;
	vz_filter = new kalman(0.1,4.0,0.0,10);
	hz_filter = new kalman(0.1,4.0,0.0,10);
	//checkForSensors();
	initializeMPU();
    initializeBMP(oss);
}

void SensorManager::initializeMPU() {

    mpu = new MPU6050(0x68);
    mpu->initialize();
    printf("Mpu initialized\n");
}

bool SensorManager::initializeMPUdmp() {
    devStatus = mpu->dmpInitialize();
    if (devStatus==0) {
        printf("Enabling DMP...\n");
        mpu->setDMPEnabled(true);
        
        mpuIntStatus = mpu->getIntStatus();
        
        packetSize = mpu->dmpGetFIFOPacketSize();
        dmpReady = true;
        return dmpReady;
    }
    printf("DMP Initialization failed (code %d)\n", devStatus);
    return false;
}

void SensorManager::initializeBMP(BMP180::OversamplingSetting oss) {
    printf("Initializing BMP180\n");
    bmp = new BMP180();
    bmpData = new bmp180_data;
    bmp->initialize(oss);
    printf("BMP180 initialized\n");
    get_bmp_offset();
    
}

bool SensorManager::testMPU() {
    if (mpu->testConnection()) {
        return true;
    }
    else {
        return false;
    }
    return false;
}

void SensorManager::readDMP(double *input) {

    	if (!dmpReady) {
    		return;
    	}
    
    	fifoCount = mpu->getFIFOCount();
    
    	if (fifoCount == 1024) {
    		mpu->resetFIFO();
    		printf("FIFO overflow! Reseting...\n");
    		return;
    	}
    
    	while (fifoCount<42) {
    		fifoCount = mpu->getFIFOCount();
    	}
    	if (fifoCount>=42) {
    		mpu->getFIFOBytes(fifoBuffer, packetSize);
        
    		// display Euler angles in degrees
    		mpu->dmpGetQuaternion(&q, fifoBuffer);
    		mpu->dmpGetGravity(&gravity, &q);
    		mpu->dmpGetYawPitchRoll(ypr, &q, &gravity);
    		//printf("ypr  %7.2f %7.2f %7.2f    ", ypr[0] * 180/M_PI, ypr[1] * 180/M_PI, ypr[2] * 180/M_PI);
        
    		//printf("\n");
        
    		mpu->dmpGetQuaternion(&q, fifoBuffer);
    		mpu->dmpGetAccel(&aa, fifoBuffer);
    		mpu->dmpGetGravity(&gravity, &q);
    		mpu->dmpGetLinearAccel(&aaReal, &aa, &gravity);
    		//printf("areal %6f %6f %6f    ", double(aaReal.x/4096.0), double(aaReal.y/4096.0), double(aaReal.z/4096.0));
        
    		//printf("\n");

    		input[0] = aaReal.x;
    		input[1] = aaReal.y;
    		input[2] = aaReal.z;
    		input[3] = (ypr[2]+offsetRoll);
    		input[4] = (ypr[1]+offsetPitch);
    		input[5] = ypr[0];
        }
    	else {
    		printf("not reading");
    	}
}

void SensorManager::readBMP(double *input) {
    bmp->get_sensor_data(bmpData);
    
    double c1 = -sin(input[4])*double(input[0]/4096.0);
    double c2 = sin(input[3])*cos(input[4])*double(input[1]/4096.0);
    double c3 = cos(input[3])*cos(input[4])*double(input[2]/4096.0);
    double az = 9.82*((c1 + c2 + c3) - 1.0);
    
    std::cout << "Acc: " << az << std::endl;
    input[2] = az;
    
    vz_est = vz_est + az*DT;
    hz_est = hz_est + vz_est*DT;
    
    std::cout << "Acc velocity: " << vz_est << std::endl;
    std::cout << "Acc altitude: " << hz_est << std::endl;
    
    vz_est =  vz_est + 0.1*(bmpData->altitude - h_offset - hz_est);
    hz_est =  hz_est + 0.8*(bmpData->altitude - h_offset - hz_est);
    
    std::cout << "Combo velocity: " << vz_est << std::endl;
    std::cout << "Combo altitude: " << hz_est << std::endl;
    
    vz_est = vz_filter->estimate(vz_est);
    hz_est = hz_filter->estimate(hz_est);

    std::cout << "Final velocity: " << vz_est << std::endl;
    std::cout << "Final altitude: " << hz_est << std::endl;
    
    input[6] = hz_est;
    input[7] = vz_est;
    input[8] = bmpData->temperature;
}

void SensorManager::get_bmp_offset() {
    h_offset = 0.0;
    for (int i = 0 ; i<50; i++) {
        bmp->get_sensor_data(bmpData);
        h_offset += bmpData->altitude;
        printf("Alt: %f", h_offset);
    }
    h_offset = double(h_offset/50.0);
    printf("Altitude offset: %f\n", h_offset);
}

