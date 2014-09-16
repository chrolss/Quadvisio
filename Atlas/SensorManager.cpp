//
//  SensorManager.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "SensorManager.h"
#include "MPU6050_6AXIS_MOTIONAPPS20.h"
#include <Sensors/adxl345.h>
#include <Kalman/kalman.h>

MPU6050 *mpu;
adxl345 *adxl;
kalman *aFilter;
kalman *bFilter;

Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector

SensorManager::SensorManager(){
	aFilter = new kalman(0.1,0.1,10,10);
	bFilter = new kalman(0.1,0.1,10,10);
	checkForSensors();
	initializeSensor();
}

void SensorManager::initializeSensor() {
	if (mpuMode){
		mpu = new MPU6050(0x68);
		mpu->initialize();
		printf("Mpu initialized\n");
	}
	else{
		adxl = new adxl345();
		printf("adxl345 initialized\n");
	}
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
    if(mpuMode){
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

    		input[0] = double(aaReal.x/4096.0);
    		input[1] = double(aaReal.y/4096.0);
    		input[2] = double(aaReal.z/4096.0);
    		input[3] = aFilter->estimate(ypr[2]+offsetRoll);
    		input[4] = bFilter->estimate(ypr[1]+offsetPitch);
    		input[5] = ypr[0];

    	}
    	else {
    		printf("not reading");
    	}
    }
    else{
    	adxl->readSensorData();
    	input[0] = adxl->getAccX();
    	input[1] = adxl->getAccY();
    	input[2] = adxl->getAccZ();
    	input[3] = aFilter->estimate(adxl->getRoll());
    	input[4] = bFilter->estimate(adxl->getPitch());
        input[5] = 0.0;			// return value from hmc5883l later
        printf("Pitch: %f, Roll: %f\n", input[4],input[3]);
    }
}

void SensorManager::checkForSensors(){
	char *fileName = "/dev/i2c-1";
	int adxlAddress = 0x53;
	int mpuAddress = 0x68;
	int fd = open(fileName, O_RDWR);

	if (fd < 0) {
	     printf("Failed to open i2c port\n");
	     exit(1);
	}

	if (ioctl(fd, I2C_SLAVE, adxlAddress) > -1) {
		char buf[6];
		buf[0] = 0x2d;
		buf[1] = 0x18;

		if ((write(fd, buf, 2)) != 2) {
		    printf("Gy-80 not found, going into MPU mode\n");
		    this->mpuMode = true;
		}
		else{
			printf("Going into gy-80 mode\n");
			this->mpuMode = false;
		}

	}
	else{
		printf("Going into gy-80 mode\n");
		this->mpuMode = false;
	}

}

