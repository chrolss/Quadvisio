#include<iostream>
#include "communicate.h"

Communicate::Communicate()
{
    senHub = new sensorHub;
    senHub->initializeMPU();
    std::thread t1(&Communicate::Listen, this);
    t1.join();
}

// Function to remove all dead processes

void Communicate::error(const char *msg)
{
    perror(msg);
    exit(1);
}

void Communicate::Listen()
{
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
    std::cout << "Connection estabilished" << std::endl;
    std::cout << "Whaiting for income.." << std::endl;
    n = (int)read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    
    // Send message
    msg = senHub->getDataMPU();
    
    n = (int)write(newsockfd,msg.c_str(),msg.length());
    
    if (n < 0) error("ERROR writing to socket");
    close(sockfd);
}

void Communicate::sendMsg(std::string s) {
    if (send(newsockfd, "Hello, world!", 13, 0) == -1)
        perror("send");
}

void Communicate::checkClient() {
    std::cout << newsockfd << std::endl;
}

void Communicate::closeClient() {
    close(newsockfd);
    std::cout << "Connection closed." << std::endl;
}
