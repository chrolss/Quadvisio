//
//  ComHandler.cpp
//  ComHandler
//
//  Created by Toni Axelsson on 2014-09-26.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "ComHandler.h"

ComHandler::ComHandler() {
    
}

void ComHandler::error(const char *msg)
{
    closeClient();
    perror(msg);
    //exit(1);
}

void ComHandler::startListenThread() {
    std::thread t1(&ComHandler::Listen, this);
    listening = true;
    t1.detach();
}

void ComHandler::Listen()
{
    int yes = 1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }
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
    if (newsockfd < 0) {
        error("ERROR on accept");
        closeClient();
    }
    
    // Prepare select
    // Clear set
    //FD_ZERO(&readfds);
    
    //
    //FD_SET(newsockfd, &readfds);
    
    n = newsockfd + 1;
    
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    
    connected = true;
    reciveMsg=true;
    listening=false;
    std::cout << "Connection estabilished" << std::endl;
    
    Client clientData = this->reciveOrder();

    printf("Order ID: %i\n", clientData.order);
    printf("App type: %i\n", clientData.type);
    
    // connect
    if(clientData.order==1) {
        if (clientData.type==1) {
            qvisLightLoop();
        }
        else if (clientData.type==2) {
            qvisProLoop();
        }
        else if (clientData.type==3) {
            //sendPidParams();
            qvisDevLoop();
        }
    }
    
    // send identity
    else if (clientData.order==2) {
        this->sendIdentity();
    }
    closeClient();
}

void ComHandler::qvisProLoop() {
    std::cout << "In Pro Loop" << std::endl;
    while (connected) {
        if (reciveMsg) {
            readQvisProMsg();
            reciveMsg=false;
        }
        
        if (sendMsg) {
            sendQvisProMsg();
            reciveMsg=true;
            sendMsg=false;
        }
    }

}

void ComHandler::qvisDevLoop() {
    while (connected) {
        
        if (reciveMsg) {
            readQvisDevMsg();
            reciveMsg=false;
        }
        
        if (sendMsg) {
            sendQvisDevMsg();
            reciveMsg=true;
            sendMsg=false;
        }
    }
}

void ComHandler::qvisLightLoop() {
    while (connected) {
        
        if (reciveMsg) {
            readQvisLightMsg();
            reciveMsg=false;
        }
        
        if (sendMsg) {
            sendQvisLightMsg();
            reciveMsg=true;
            sendMsg=false;
        }
    }
}

void ComHandler::sendQvisProMsg() {
    
    std::string s = "0002:0";
    
    if (send(newsockfd, s.c_str(), s.length(),0) == -1) {
        closeClient();
        perror("send");
    }
}

void ComHandler::sendQvisDevMsg() {
    
}

void ComHandler::sendQvisLightMsg() {
    
}

void ComHandler::readQvisProMsg() {
    
    std::string msg = this->reciveMessage();
    
    printf("Final message:\n");
    std::cout << msg << std::endl;
    
    size_t pos = 0;
    std::string token;
    
    // length:orderID
    
    int i = 0;
    while ((pos = msg.find(subDelimiter)) != std::string::npos) {
        token = msg.substr(0, pos);
        numberInStrings[i] = token;
        msg.erase(0, pos + subDelimiter.length());
        i++;
    }
    
    numberInStrings[i] = msg;
    
}

void ComHandler::readQvisDevMsg() {
    
}

void ComHandler::readQvisLightMsg() {
    
}

Client ComHandler::reciveOrder() {
    
    std::string msg = this->reciveMessage();
    
    printf("Final message:\n");
    std::cout << msg << std::endl;
    
    size_t pos = 0;
    std::string token;
    
    // length:orderID
    
    int i = 0;
    while ((pos = msg.find(subDelimiter)) != std::string::npos) {
        token = msg.substr(0, pos);
        numberInStrings[i] = token;
        msg.erase(0, pos + subDelimiter.length());
        i++;
    }
    
    numberInStrings[i] = msg;
    
    Client clientData;
    
    clientData.name = numberInStrings[1];
    clientData.type = atoi(numberInStrings[2].c_str());
    clientData.order = atoi(numberInStrings[3].c_str());
    
    sendMsg = true;
    reciveMsg = false;

    return clientData;
}

std::string ComHandler::reciveMessage() {
    //printf("Waitning for message\n");
    
    std::string msgBuffer = "";
    std::string msg = "";
    int msgSize = 0;
    
    bzero(recvBuf, 1024);
    
    while (1) {
        ssize_t numBytes = recv(newsockfd, recvBuf, sizeof(recvBuf), 0);
        
        if (numBytes < 0) {
            connected = false;
            perror("read");
            return "";
        }
        
        else if (numBytes == 0) {
            printf("Maybe lost connection to client, closing socket and starting to listing\n");
            connected = false;
            return "";
        }
        
        else {
            msgBuffer = std::string(recvBuf);
            //std::cout << "Raw message: " << msgBuffer << std::endl;
        }
        
        if (msgSize == 0 && msgBuffer.size()>=3) {
            msgSize = atoi(msgBuffer.substr(0,3).c_str());
            //printf("Message size: %i\n", msgSize);
        }
        
        if (msgSize>0 && msgBuffer.size() == (msgSize+3)) {
            //printf("Message recived!\n");
            msg = msgBuffer;
            return msg;
        }
        
    }
    return "";
}

void ComHandler::sendIdentity() {
    std::ostringstream ostr;
    ostr.str("");
    
    int sig = this->getSigStrength();
    
    ostr << "1:" << sig;
    
    std::string s;
    s = ostr.str();
    ostr.str("");
    
    if ((s.length()+1)<10) {
        ostr << "000" << (s.length()+1) << ":" << s;
    }
    else if((s.length()+1)>=10 && (s.length()+1)<100) {
        ostr << "00" << (s.length()+1) << ":" << s;
    }
    else if((s.length()+1)>=100 && (s.length()+1)<1000) {
        ostr << "0" << (s.length()+1) << ":" << s;
    }
    else {
        ostr << (s.length()+1) << ":" << s;
    }
    
    s = ostr.str();
    if (send(newsockfd, s.c_str(), s.length(),0) == -1) {
        closeClient();
        perror("send");
    }
}

int ComHandler::getSigStrength() {
    return 50;
}

void ComHandler::closeClient() {
    close(newsockfd);
    close(sockfd);
    std::cout << "Connection closed." << std::endl;
    sleep(2);
    connected = false;
}