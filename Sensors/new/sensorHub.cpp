#include "sensorHub.h"


sensorHub::sensorHub()
{
    dmpReady =false;
}

void sensorHub::initializeMPU(){
    // initialize device
    printf("Initializing I2C devices...\n");
    mpu.initialize();
    
    // verify connection
    printf("Testing device connections...\n");
    printf(mpu.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");
    
    // load and configure the DMP
    printf("Initializing DMP...\n");
    devStatus = mpu.dmpInitialize();
    
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        printf("Enabling DMP...\n");
        mpu.setDMPEnabled(true);
        
        // enable Arduino interrupt detection
        //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        //attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        
        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        printf("DMP ready!\n");
        dmpReady = true;
        
        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        printf("DMP Initialization failed (code %d)\n", devStatus);
    }
}

std::string sensorHub::getAllData()
{
    return "hej";
}

std::string sensorHub::getDataMPU()
{
    return "Hej";
}


