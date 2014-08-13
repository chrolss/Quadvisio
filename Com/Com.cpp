//
//  Com.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "Com.h"

Com::Com(){
    msgSend=false;
    imgSend=false;
    verticalThrust=0;
    
    output[0]=0.0;
    output[1]=0.0;
    output[2]=0.0;
    output[3]=0.0;
    output[4]=0.0;
    output[5]=0.0;
    
    std::cout << "Setting up camera" << std::endl;
    cap.open(0);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    sleep(1);
    
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
    reciveMsg=true;
    std::cout << "Connection estabilished" << std::endl;
    
    while (connected) {
        
        if (videoStream) {
            cap >> sendFrame;
        }
        
        if (reciveMsg) {
            std::cout << "Reciving message" << std::endl;
            ssize_t numbytes = recv(newsockfd, recvBuf, 43, 0);
            if (numbytes==-1) {
                perror("recive");
            }
            readMsg();
            std::cout << "Message recived!" << std::endl;
            reciveMsg=false;
        }
        
        if (msgSend) {
            std::cout << "Sending message" << std::endl;
            sendMsg();
            reciveMsg=true;
            msgSend=false;
            std::cout << "Message sent!" << std::endl;
        }
    }
    
    //Add Closure stuff
}

void Com::sendMsg() {
    
    ostr.str("");
    
    ostr << output[0] << " " << output[1] << " " << output[2] << " " << output[3] << " " << output[4] << " " << output[5];
    std::string s;
    s=ostr.str();
    size_t length = s.size();
    
    ostr.str("");
    
    if (imgSend) {
        ostr << length << " 1 " << s;
        s = ostr.str();
        if (send(newsockfd, s.c_str(), s.length(), 0) == -1)
            perror("send");
        sendImg();
        imgSend=false;
    }
    else {
        ostr << length << " 0 " << s;
        s = ostr.str();
        if (send(newsockfd, s.c_str(), s.length(), 0) == -1)
            perror("send");
    }
    
}

void Com::sendImg() {
    sendFrame = (sendFrame.reshape(0,1));
    if (send(newsockfd, sendFrame.data, 230400, 0) == -1) {
        perror("send");
    }

}

void Com::readMsg() {
    std::string msg(recvBuf);
    std::cout << msg << std::endl;
    pos = 0;
    
    int i=0;
    while ((pos = msg.find(delimiter)) != std::string::npos) {
        token = msg.substr(0, pos);
        msg.erase(0, pos + delimiter.length());
        stringList[i] = token;
        i++;
    }
    stringList[11] = msg;
    
    verticalThrust = atoi(stringList[0].c_str());
    int video = atoi(stringList[1].c_str());
    int fps = atoi(stringList[2].c_str());
    
    std::cout << verticalThrust << " " << video << " " << fps << std::endl;
    
    for (int j=3; j<12; j++) {
        pidParam[j-3] = atof(stringList[j].c_str());
        std::cout << pidParam[j-3] << std::endl;
    }
    
    if (video==1) {
        videoStream=true;
    }
    else {
        videoStream=false;
    }
    
    imgSendRate = fps;
}

void Com::checkClient() {
    std::cout << newsockfd << std::endl;
}

void Com::closeClient() {
    close(newsockfd);
    std::cout << "Connection closed." << std::endl;
}

void Com::setOutputData(double *out) {
    output[0] = out[0];
    output[1] = out[1];
    output[2] = out[2];
    output[3] = out[3];
    output[4] = out[4];
    output[5] = out[5];
}


