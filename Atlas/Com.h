//
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
#include <netinet/in.h>
#include <thread>
#include <sstream>
#include <string>
#include <opencv2/highgui/highgui.hpp>

#define PORT "3490"  // the port users will be connecting to
#define BACKLOG 10

class Com{

public:
    Com();
    void Listen();
    void sendMsg();
    void sendImg();
    void checkClient();
    void closeClient();
    
    void getNewInputData(int value);
    void setOutputData(double *output);
    
    bool connected;
    bool imgSend;
    bool msgSend;
    bool reciveMsg;
    bool videoStream=false;
    
    double output[6];
    int verticalThrust, imgSendRate;
    
    cv::Mat sendFrame;
    
private:
    void error(const char *msg);
    void readMsg();
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    char recvBuf[44];
    struct sockaddr_in serv_addr, cli_addr;
    std::ostringstream ostr;
    
    cv::VideoCapture cap;
    
    double pidParam[9];
    size_t pos;
    std::string stringList[12];
    std::string delimiter = ":";
    std::string token;

};

#endif /* defined(__Atlas__Com__) */
