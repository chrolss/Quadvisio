//
//  ComHandler.h
//  ComHandler
//
//  Created by Toni Axelsson on 2014-09-26.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#ifndef __ComHandler__ComHandler__
#define __ComHandler__ComHandler__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <thread>
#include <sstream>
#include <string>
//#include <linux/wireless.h>
#include <math.h>
#include <time.h>

#include "CameraManager.h"

#define PORT "3490"  // the port users will be connecting to
#define radToDeg 57.296

struct signalInfo {
    char mac[18];
    char ssid[33];
    int bitrate;
    int level;
};

struct Client {
    std::string name;
    int type;
    int order;
};

class ComHandler {
    
public:
    ComHandler();
    void startListenThread();
    void closeClient();
    
    void setOutputData(double *out, double *pwm, double *ref, double &freq, double *err);
    void setSettingsData(double *params);
    void getSettingsData(double *params);
    
    bool connected, reciveMsg, sendMsg, listening, sendImage;
    bool resetIntegral, videoStream, colorVideo, saveSettnings, motorOn;
    
    double controllerInputData[9];  // Roll:Pitch:Yaw:Throttle:rollOffset:pitchOffset:JoySen
    
    int vidCount;
    int vidLimit;
    
    // Error message to be sent to Qvis
    std::string errMsg;
    
private:
    void Listen();
    void error(const char *msg);
    Client reciveOrder();
    void sendIdentity();
    void send_img();
    std::string reciveMessage();
    
    void qvisDevLoop();
    void qvisProLoop();
    void qvisLightLoop();
    
    void readQvisProMsg();
    void readQvisDevMsg();
    void readQvisLightMsg();
    
    void sendQvisProMsg();
    void sendQvisDevMsg();
    void sendQvisLightMsg();
    
    int getSigStrength();
    int getSignalInfo();
    
    
    // Video
    CameraManager *camManager;
    int vidRes;
    int vidResNew;
    int frame_count;
    struct jpg_data jpg_dat;
    
    // PID Params : Joy Sen : RollTrim : PitchTrim
    double settingsData[15];
    
    double output[19];
    int sizeOfOutput;

    int sockfd, newsockfd, portno, n;
    char recvBuf[1024];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    
    time_t start;
    
    // Stringstream used for composing messages
    std::ostringstream ostr;
    
    std::string subDelimiter = ":";
    std::string token;
    std::string numberInStrings[28];

};

#endif /* defined(__ComHandler__ComHandler__) */
