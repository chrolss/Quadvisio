#ifndef COMMUNICATE_H
#define COMMUNICATE_H

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

class Communicate
{
public:
    Communicate();
    void Listen();
    void sendMsg(std::string s, size_t i);
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
    std::string msg;
};

#endif