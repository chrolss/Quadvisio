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
    savePid = false;
    vidCount = 0;
    vidLimit = 0;
    vidRes = 2; // Default 2 = 320x240
    vidResNew = 2;
    msgSize = 0;
    errMsg = "Nothing wrong here!!";
    
    output[0]=0.0;
    output[1]=0.0;
    output[2]=0.0;
    output[3]=0.0;
    output[4]=0.0;
    output[5]=0.0;
    output[6]=0.0;
    output[7]=0.0;
    output[8]=0.0;
    output[9]=0.0;
    output[10]=0.0;
    output[11]=0.0;
    output[12]=0.0;
    output[13]=0.0;
    
    for (int i = 0; i<(sizeof(pidParams)/sizeof(*pidParams)); i++) {
        pidParams[i] = 1.1;
    }
    
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
    
    if (clientIdentity==1) {
        
    }
    else if (clientIdentity==2) {
        qvisLightLoop();
    }
    else if (clientIdentity==3) {
        sendPidParams();
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
    
    for (int i=0; i<3; i++) {
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
    
    ostr.str("");
    
    for (int i=0; i<sizeOfOutput; i++) {
        ostr << output[i] << ":";
    }
    
    if (errMsg.size()>0) {
        ostr << errMsg << "\n:";
        errMsg = "";
    }
    else {
        ostr << "none:";
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
            //printf("New resolution was set\n");
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
    
    //printf("Sending message: %s\n", s.c_str());
    if (send(newsockfd, s.c_str(), s.length(),0) == -1) {
        closeClient();
        perror("send");
    }
    
    if (imgSend && videoStream) {
        sendImg();
        imgSend = false;
    }
    //printf("Message sent\n");
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
    
    reciveMessage();
    
    //printf("Final message:\n");
    std::cout << msg << std::endl;
    
    size_t pos = 0;
    std::string token;
    
    int i = 0;
    while ((pos = msg.find(subDelimiter)) != std::string::npos) {
        token = msg.substr(0, pos);
        numberInStrings[i] = token;
        msg.erase(0, pos + subDelimiter.length());
        i++;
    }
    numberInStrings[i] = msg;
    
    if (atoi(numberInStrings[7].c_str())==1) {
        for (int i=8; i<20; i++) {
            pidParams[i-8] = atof(numberInStrings[i].c_str());
        }
        savePid = true;
        printf("PID parameters read and saved");
    }
    
    if (atoi(numberInStrings[20].c_str())==1) {
        videoStream = true;
    }
    else {
        videoStream = false;
        vidCount = 0;
    }
    
    if (atoi(numberInStrings[21].c_str())==1) {
        colorVideo = true;
    }
    else {
        colorVideo = false;
    }
    
    vidResNew = atoi(numberInStrings[22].c_str());
    
    if (atoi(numberInStrings[23].c_str())==1) {
        motorOn = true;
    }
    else{
        motorOn = false;
    }
    
    for (int i = 1 ; i<7; i++) {
        inputData[i-1] = atof(numberInStrings[i].c_str());
    }
    
}

void Com::reciveMessage() {
    
    //printf("Waitning for message\n");
    
    msgBuffer = "";
    msg = "";
    msgSize = 0;
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
            //std::cout << "Raw message: " << msgBuffer << std::endl;
        }
        
        if (msgSize == 0 && msgBuffer.size()>=3) {
            msgSize = atoi(msgBuffer.substr(0,3).c_str());
            //printf("Message size: %i\n", msgSize);
        }
        
        if (msgSize>0 && msgBuffer.size() == (msgSize+3)) {
            //printf("Message recived!\n");
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
    while ((pos = this->msg.find(subDelimiter)) != std::string::npos) {
        token = msg.substr(0, pos);
        std::cout << token << std::endl;
        numberInStrings[i] = token;
        msg.erase(0, pos + subDelimiter.length());
        i++;
    }
    
    numberInStrings[i] = msg;
    std::cout << msg << std::endl;
    clientIdentity = atoi(numberInStrings[1].c_str());
    clientName = numberInStrings[2];
}

void Com::sendPidParams() {
    ostr.str("");
    
    for (int i=0; i<11; i++) {
        ostr << pidParams[i] << ":";
    }
    ostr << pidParams[11];
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

int Com::getSignalInfo() {
    iwreq req;
    
    signalInfo *sigInfo;
    sigInfo = new signalInfo;
    
    strcpy(req.ifr_name, "wlan0");
    
    iw_statistics *stats;
    
    //have to use a socket for ioctl
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    //make room for the iw_statistics object
    req.u.data.pointer = (iw_statistics *)malloc(sizeof(iw_statistics));
    req.u.data.length = sizeof(iw_statistics);
    
    //this will gather the signal strength
    if(ioctl(sockfd, SIOCGIWSTATS, &req) == -1){
        //die with error, invalid interface
        fprintf(stderr, "Invalid interface.\n");
        return(-1);
    }
    else if(((iw_statistics *)req.u.data.pointer)->qual.updated & IW_QUAL_DBM){
        //signal is measured in dBm and is valid for us to use
        sigInfo->level=((iw_statistics *)req.u.data.pointer)->qual.level - 256;
    }
    
    //SIOCGIWESSID for ssid
    char buffer[32];
    memset(buffer, 0, 32);
    req.u.essid.pointer = buffer;
    req.u.essid.length = 32;
    //this will gather the SSID of the connected network
    if(ioctl(sockfd, SIOCGIWESSID, &req) == -1){
        //die with error, invalid interface
        return(-1);
    }
    else{
        memcpy(&sigInfo->ssid, req.u.essid.pointer, req.u.essid.length);
        memset(&sigInfo->ssid[req.u.essid.length],0,1);
    }
    
    //SIOCGIWRATE for bits/sec (convert to mbit)
    int bitrate=-1;
    //this will get the bitrate of the link
    if(ioctl(sockfd, SIOCGIWRATE, &req) == -1){
        fprintf(stderr, "bitratefail");
        return(-1);
    }else{
        memcpy(&bitrate, &req.u.bitrate, sizeof(int));
        sigInfo->bitrate=bitrate/1000000;
    }
    
    
    //SIOCGIFHWADDR for mac addr
    ifreq req2;
    strcpy(req2.ifr_name, "wlan0");
    //this will get the mac address of the interface
    if(ioctl(sockfd, SIOCGIFHWADDR, &req2) == -1){
        fprintf(stderr, "mac error");
        return(-1);
    }
    else{
        sprintf(sigInfo->mac, "%.2X", (unsigned char)req2.ifr_hwaddr.sa_data[0]);
        for(int s=1; s<6; s++){
            sprintf(sigInfo->mac+strlen(sigInfo->mac), ":%.2X", (unsigned char)req2.ifr_hwaddr.sa_data[s]);
        }
    }
    close(sockfd);
    
    printf("Bitrate: %i\n", sigInfo->bitrate);
    printf("Level: %i\n", sigInfo->level);
    
    return 0;
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
    output[3] = out[3];
    output[4] = out[4];
    output[5] = out[5];
    output[6] = out[6];
    output[7] = out[7];
    output[8] = out[8];
    output[9] = out[9];
    output[10] = out[10];
    output[11] = out[11];
    output[12] = out[12];
    output[13] = out[13];
}


