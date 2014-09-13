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
    listening=false;
    connected=false;
    msgStarted=false;
    videoStream=false;
    motorOn=false;
    colorVideo=true;
    vidCount = 0;
    vidLimit = 0;
    vidRes = 2; // Default 2 = 320x240
    vidResNew = 2;
    msgSize = 0;
    
    output[0]=0.0;
    output[1]=0.0;
    output[2]=0.0;
    
    sizeOfOutput = (sizeof(output)/sizeof(*output));
    
    std::cout << "Setting up camera" << std::endl;
    
    cap.open(0);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    
    if (cap.isOpened()) {
        printf("Camera opened!\n");
    }
    
    usleep(1000);
}

void Com::error(const char *msg)
{
    closeClient();
    perror(msg);
    //exit(1);
}

void Com::startListenThread() {
    std::thread t1(&Com::Listen, this);
    listening = true;
    t1.detach();
}

void Com::Listen()
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
    
    if (newsockfd < 0)
        error("ERROR on accept");
    
    connected = true;
    reciveMsg=true;
    listening=false;
    vidCount = 0;
    std::cout << "Connection estabilished" << std::endl;
    
    reciveClientIdentity();
    
    printf("%s connected with %i\n", clientName.c_str(), clientIdentity);
    //closeClient();
    //return;
    
    if (clientIdentity==1) {
        
    }
    else if (clientIdentity==2) {
        qvisLightLoop();
    }
    else if (clientIdentity==3) {
        qvisDevLoop();
    }

    closeClient();
}

void Com::qvisDevLoop() {
    while (connected) {
        
        if (reciveMsg) {
            readMsg();
            reciveMsg=false;
        }
        
        if (msgSend) {
            sendQvisDevMsg();
            reciveMsg=true;
            msgSend=false;
        }
    }
}

void Com::qvisLightLoop() {
    while (connected) {
        
        if (reciveMsg) {
            readMsg();
            reciveMsg=false;
        }
        
        if (msgSend) {
            sendQvisLightMsg();
            reciveMsg=true;
            msgSend=false;
        }
    }
}

void Com::sendQvisLightMsg() {
    
    printf("Sending message\n");
    printf("Video count: %i\n", vidCount);
    
    ostr.str("");
    
    for (int i=0; i<sizeOfOutput; i++) {
        ostr << output[i] << ":";
    }
    
    if (imgSend && videoStream) {
        if (vidResNew != vidRes) {
            switch (vidResNew) {
                case 0:
                    cap.set(CV_CAP_PROP_FRAME_WIDTH, 80);
                    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 60);
                    break;
                    
                case 1:
                    cap.set(CV_CAP_PROP_FRAME_WIDTH, 160);
                    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 120);
                    break;
                    
                case 2:
                    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
                    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
                    break;
                
                case 3:
                    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
                    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
                    break;
                    
                default:
                    break;
            }
            usleep(1000);
            printf("New resolution was set\n");
            vidRes = vidResNew;
        }
        
        cap >> sendFrame;
        
        if (colorVideo) {
            cvtColor(sendFrame, sendFrame, CV_BGR2RGB);
            ostr << sendFrame.cols << ":" << sendFrame.rows << ":";
            ostr << sendFrame.total()*3 << ":3";
        }
        
        else {
            cvtColor(sendFrame, sendFrame, CV_BGR2GRAY);
            ostr << sendFrame.cols << ":" << sendFrame.rows << ":";
            ostr << sendFrame.total() << ":1";
        }
    }
    else {
        ostr << "0:0:0:0";
    }
    
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
    
    printf("Sending message: %s\n", s.c_str());
    if (send(newsockfd, s.c_str(), s.length(),0) == -1) {
        closeClient();
        perror("send");
    }
    
    if (imgSend && videoStream) {
        sendImg();
        imgSend = false;
    }
    printf("Message sent\n");

}

void Com::sendQvisDevMsg() {
    
}

void Com::sendImg() {
    sendFrame = (sendFrame.reshape(0,1));
    if(colorVideo) {
        if (send(newsockfd, sendFrame.data, sendFrame.total()*3, 0) == -1) {
            closeClient();
            perror("send");
        }
    }
    else {
        if (send(newsockfd, sendFrame.data, sendFrame.total(), 0) == -1) {
            closeClient();
            perror("send");
        }
    }

    vidCount=0;
}

void Com::readMsg() {
    printf("Waitning for message\n");
    
    msgBuffer = "";
    msg = "";
    bzero(recvBuf, 1024);
    
    while (1) {
        numBytes = recv(newsockfd, recvBuf, sizeof(recvBuf), 0);
        if (numBytes < 0) {
            closeClient();
            perror("read");
            break;
        }
        
        else if (numBytes == 0) {
            printf("Maybe lost connection to client, closing socket and starting to listing\n");
            connected = false;
            return;
        }
        
        else {
            msgBuffer = std::string(recvBuf);
            std::cout << "Raw message: " << msgBuffer << std::endl;
            
            // If msg is a complete message
            if ((posStart = msgBuffer.find(startDelimiter)) != std::string::npos && (posEnd = msgBuffer.find(endDelimeter)) != std::string::npos) {
                msg = msgBuffer.substr(posStart + 1, posEnd - 1);
                //std::cout << msg << std::endl;
                //printf("1");
                break;
            }
            
            // If msg is the start of a message
            else if (posStart != std::string::npos && posEnd == std::string::npos) {
                msg = msgBuffer.substr(posStart + 1, msg.length());
                //std::cout << msg << std::endl;
                msgStarted = true;
                printf("2");
            }
            
            // If msg is the end of a message
            else if (posStart == std::string::npos && posEnd != std::string::npos) {
                msg.append(msgBuffer);
                msg.erase(msg.length(),1);
                //std::cout << msg << std::endl;
                msgStarted = false;
                printf("3");
                break;
            }
            
            // If msg is a middle part of a message
            else {
                msg.append(msgBuffer);
                printf("4");
                //std::cout << msg << std::endl;
            }
        }
    }
    
    printf("Final message:\n");
    std::cout << msg << std::endl;
    
    size_t pos = 0;
    std::string token;
    
    int i = 0;
    while ((pos = msg.find(subDelimiter)) != std::string::npos) {
        token = msg.substr(0, pos);
        //std::cout << token << std::endl;
        numberInStrings[i] = token;
        msg.erase(0, pos + subDelimiter.length());
        i++;
    }
    //std::cout << msg << std::endl;
    numberInStrings[7] = msg;
    
    if (atoi(numberInStrings[4].c_str())==1) {
        videoStream = true;
    }
    else {
        videoStream = false;
    }
    
    if (atoi(numberInStrings[5].c_str())==1) {
        colorVideo = true;
    }
    else {
        colorVideo = false;
    }
    
    vidResNew = atoi(numberInStrings[6].c_str());
    //printf("Video res %i\n", vidResNew);
    
    if (atoi(numberInStrings[7].c_str())==1) {
        motorOn = true;
    }
    else{
        motorOn = false;
    }
    
    for (int i = 0 ; i<4; i++) {
        stateBuf[i] = atof(numberInStrings[i].c_str());
    }
}

void Com::reciveMessage() {
    
    printf("Waitning for message\n");
    
    msgBuffer = "";
    msg = "";
    bzero(recvBuf, 1024);
    
    while (1) {
        numBytes = recv(newsockfd, recvBuf, sizeof(recvBuf), 0);
        if (numBytes < 0) {
            connected = false;
            perror("read");
            return;
        }
        
        else if (numBytes == 0) {
            printf("Maybe lost connection to client, closing socket and starting to listing\n");
            connected = false;
            return;
        }
        
        else {
            msgBuffer = std::string(recvBuf);
            std::cout << "Raw message: " << msgBuffer << std::endl;
        }
        
        if (msgSize == 0 && msgBuffer.size()>=3) {
            msgSize = atoi(msgBuffer.substr(0,3).c_str());
            printf("Message size: %i", msgSize);
        }
        
        if (msgSize>0 && msgBuffer.size() == (msgSize+3)) {
            printf("Message recived!\n");
            msg = msgBuffer;
            break;
        }
        
    }
    
}

void Com::reciveClientIdentity() {
    
    reciveMessage();
    
    printf("Final message:\n");
    std::cout << msg << std::endl;
    
    size_t pos = 0;
    std::string token;
    
    int i = 0;
    while ((pos = msg.find(subDelimiter)) != std::string::npos) {
        token = msg.substr(0, pos);
        std::cout << token << std::endl;
        numberInStrings[i] = token;
        msg.erase(0, pos + subDelimiter.length());
        i++;
    }
    numberInStrings[i] = msg;
    
    clientIdentity = atoi(numberInStrings[1].c_str());
    clientName = numberInStrings[2];
}

void Com::checkClient() {
    std::cout << newsockfd << std::endl;
}

void Com::closeClient() {
    close(newsockfd);
    close(sockfd);
    std::cout << "Connection closed." << std::endl;
    sleep(2);
    connected = false;
}

void Com::setOutputData(double *out) {
    output[0] = out[0];
    output[1] = out[1];
    output[2] = out[2];
}


