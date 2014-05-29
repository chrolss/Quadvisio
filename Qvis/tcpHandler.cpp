//
//  tcpHandler.cpp
//  Qvis
//
//  Created by Toni Axelsson on 2014-05-28.
//
//

#include "tcpHandler.h"

tcpHandler::tcpHandler()
{
    createTCPThread();
}

void tcpHandler::error(const char *msg)
{
    perror(msg);
    exit(0);
}

void tcpHandler::listen()
{
    
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char buffer[256];

    portno = PORT;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("10.0.1.4");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    std::cout << "Connection estabilished" << std::endl;
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0)
        error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
}

void tcpHandler::createTCPThread()
{
    int rc = pthread_create(&t, NULL, TCPThread_func, static_cast<void*>(this));
    if ( rc != 0 )
    {
        std::cerr << "Error in thread creation..." << std::endl;
        std::cerr << strerror(rc) << std::endl;
        exit(EXIT_FAILURE);
    }
}