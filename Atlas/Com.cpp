//
//  Com.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "Com.h"

Com::Com(){
    std::thread t1(&Com::Listen, this);
    t1.detach();
}

void Com::error(const char *msg)
{
    perror(msg);
    exit(1);
}

void Com::Listen()
{
    connected = false;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(PORT);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    std::cout << "Listening for life..." << std::endl;
    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    bzero(buffer,256);
    connected = true;
    std::cout << "Connection estabilished" << std::endl;
}

void Com::sendMsg(double *input) {
    
    std::ostringstream ostr;
    ostr << input[0] << " " << input[1] << " " << input[2] << " " << input[3] << " " << input[4] << " " << input[5];
    std:: string s=ostr.str();
    ostr.clear();
    size_t strLength = s.length();
    ostr << strLength << " " << s;
    s = ostr.str();
    std::cout << s << std::endl;
    
    if (send(newsockfd, s.c_str(), s.length(), 0) == -1)
        perror("send");
}

void Com::checkClient() {
    std::cout << newsockfd << std::endl;
}

void Com::closeClient() {
    close(newsockfd);
    std::cout << "Connection closed." << std::endl;
}


