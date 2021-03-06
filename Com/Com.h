
//  Com.h
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#ifndef __Atlas__Com__
#define __Atlas__Com__

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
#include <linux/wireless.h>
#include <math.h>
#include <time.h>

#include "CameraManager.h"

#define PORT "3490"  // the port users will be connecting to
#define BACKLOG 10
#define radToDeg 57.296

struct signalInfo {
    char mac[18];
    char ssid[33];
    int bitrate;
    int level;
};

class Com{

public:
    Com();
    void Listen();
    void sendImg();
    void closeClient();
    void startListenThread();
    int getSignalInfo();
    void setSettingsData(double *params);
    void getSettingsData(double * params);

    void getNewInputData(int value);
    void setOutputData(double *out, double *pwm, double *ref, double &freq, double *err);
    void getDataFromQvis();

    bool connected;
    bool listening;
    bool imgSend;
    bool msgSend;
    bool reciveMsg;
    bool videoStream;
    bool msgStarted;
    bool motorOn;
    bool colorVideo;
    bool saveSettnings;
    bool resetIntegral;

    int vidCount;
    int vidLimit;

    double inputData[9];  // Roll:Pitch:Yaw:Throttle:rollOffset:pitchOffset:JoySen:RollOffset:PitchOffset

    std::string errMsg;

private:
    void error(const char *msg);
    void readMsg();
    void reciveClientIdentity();
    void reciveMessage();
    void qvisDevLoop();
    void qvisLightLoop();
    void sendQvisDevMsg();
    void sendQvisLightMsg();
    void sendSettingsData();

    time_t start;
    struct timeval tv;
    
    double settingsData[15];
    // angles:refangles:pwm:speed:sidespeed:altitude:Hz:bitrate:dbm:errorMessage:imgWidth:imgHeight:imgSize:imgChannels - Image
    double output[19];

    int sockfd, newsockfd, portno, n;
    int sizeOfOutput;
    int clientIdentity;
    std::string clientName;
    std::string clientIp;

    int vidRes;
    int vidResNew;
    int frameCount;

    size_t numBytes;

    socklen_t clilen;
    char recvBuf[1024];
    struct sockaddr_in serv_addr, cli_addr;
    std::ostringstream ostr;

    // Video
    
    CameraManager *camManager;
    void *jpg_buffer;
    
    ////

    std::string numberInStrings[28];

    // Message parsing
    size_t posStart;
    size_t posEnd;
    std::string msg;
    std::string msgBuffer;
    std::string subDelimiter = ":";
    std::string token;

    int msgSize;
};

#endif /* defined(__Atlas__Com__) */
