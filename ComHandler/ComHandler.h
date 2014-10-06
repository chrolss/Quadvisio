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
#include <time.h>

#define PORT "3490"  // the port users will be connecting to

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
    
    bool connected, reciveMsg, sendMsg, listening;
    
private:
    void Listen();
    void error(const char *msg);
    Client reciveOrder();
    void sendIdentity();
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
        
    int sockfd, newsockfd, portno, n;
    char recvBuf[1024];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    
    time_t start;
    struct timeval tv;
    fd_set readfds;
    
    std::string subDelimiter = ":";
    std::string token;
    std::string numberInStrings[25];

};

#endif /* defined(__ComHandler__ComHandler__) */
