#include<iostream>
#include "communicate.h"

Communicate::Communicate()
{
    std::thread t1(&Communicate::Listen, this);
    t1.detach();
}

void Communicate::error(const char *msg)
{
    perror(msg);
    exit(1);
}

void Communicate::Listen()
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
    
    std::cout << "Whaiting for income.." << std::endl;
    n = (int)read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    
    // Send message
    msg = "0.965 -0.234 0.543 0.4 0.3 0.6";
    n = (int)write(newsockfd,msg.c_str(),msg.length());
    if (n < 0) error("ERROR writing to socket");
}

void Communicate::sendMsg(std::string s, size_t i) {
    
    std::ostringstream ostr;
    ostr << i << s;
    s=ostr.str();
    std::cout << s << std::endl;
    if (send(newsockfd, s.c_str(), s.length(), 0) == -1)
        perror("send");
}

void Communicate::checkClient() {
    std::cout << newsockfd << std::endl;
}

void Communicate::closeClient() {
    close(newsockfd);
    std::cout << "Connection closed." << std::endl;
}