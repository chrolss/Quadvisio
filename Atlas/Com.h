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

#define PORT "3490"  // the port users will be connecting to
#define BACKLOG 10

class Com{

public:
    Com();
    void Listen();
    void sendMsg(std::string s, int i);
    void checkClient();
    void closeClient();
    
    bool connected;
    
private:
    void error(const char *msg);
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;    
};

#endif /* defined(__Atlas__Com__) */
