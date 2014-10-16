//
//  Com.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

///////////////////// INFORMATION ///////////////////////////////////

// SettningsData - Holds the PID parameters, Joy. Sen and Trim values
// The first message to Qvis should be the Settnings values
// SaveSettnings is true if new values exist

// Incomning message structure:
// Yaw : Throttle : Roll : Pitch : RollOffset : PitchOffset : Reset Integral : Video : Color : Resolution : Motor on : Data ind : All PIDs : Joystick Sensitivity : RollOffset : PitchOffset

// Outgoing message structure:
// angles : refangles : pwm : speed : sidespeed : altitude : integral roll : integral pitch : integral yaw : Hz : bitrate : dbm : errorMessage : imgWidth : imgHeight : imgSize : imgChannels - Image


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
    saveSettnings = false;
    resetIntegral = false;
    vidCount = 0;
    vidLimit = 0;
    vidRes = 2; // Default 2 = 320x240
    vidResNew = 2;
    msgSize = 0;
    errMsg = "Nothing wrong here!!";
    
    for (unsigned int i = 0; i<(sizeof(output)/sizeof(*output)); i++) {
        output[i] = 0.5;
    }

    for (unsigned int i = 0; i<(sizeof(settingsData)/sizeof(*settingsData)); i++) {
        settingsData[i] = 0.5;
    }

    for (unsigned int i = 0; i<(sizeof(numberInStrings)/sizeof(*numberInStrings)); i++) {
        numberInStrings[i] = "";
    }
    
    for (unsigned int i = 0; i<(sizeof(inputData)/sizeof(*inputData)); i++) {
        inputData[i] = 0.5;
    }
    
    sizeOfOutput = (sizeof(output)/sizeof(*output));
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
    if (newsockfd < 0) {
        error("ERROR on accept");
        closeClient();
    }
    
    struct timeval tv;
    
    tv.tv_sec = 2;  /* 30 Secs Timeout */
    tv.tv_usec = 0;  // Not init'ing this can cause strange errors
    
    setsockopt(newsockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));

    connected = true;
    reciveMsg=true;
    listening=false;
    vidCount = 0;
    std::cout << "Connection estabilished" << std::endl;
    
    reciveClientIdentity();

    printf("%s connected with %i\n", clientName.c_str(), clientIdentity);

    start = time(0);

    if (clientIdentity==1) {

    }
    else if (clientIdentity==2) {
        qvisLightLoop();
    }
    else if (clientIdentity==3) {
        sendSettingsData();
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
    
    //printf("Sending message\n");
    //printf("Video count: %i\n", vidCount);

    this->getSignalInfo();
    
    ostr.str("");

    for (int i=0; i<3; i++) {
        ostr << output[i] << ":";
    }
    /*
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
    */
    ostr << "0:0:0:0";
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
    /*
    if (imgSend && videoStream) {
        sendImg();
        imgSend = false;
    }
    */
    printf("Message sent\n");

}

void Com::sendQvisDevMsg() {

    this->getSignalInfo();

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
    /*
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
    */
    ostr << "0:0:0:0";
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

    /*
    if (imgSend && videoStream) {
        sendImg();
        imgSend = false;
    }
    */
    //printf("Message sent\n");
}

void Com::sendImg() {
	/*
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
    */
}

void Com::readMsg() {
    
    reciveMessage();
    
    //printf("Final message:\n");
    //std::cout << msg << std::endl;
    
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
    
    // Yaw : Throttle : Roll : Pitch : RollOffset : PitchOffset : Reset Integral : Video : Color : Resolution : Motor on : Data ind : All PIDs : Joystick Sensitivity

    for (int i = 1 ; i<7; i++) {
        inputData[i-1] = atof(numberInStrings[i].c_str());
    }

    if (atoi(numberInStrings[7].c_str())==1) {
        resetIntegral = true;
        printf("Reset integral\n");
    }
    else {
        resetIntegral = false;
    }

    if (atoi(numberInStrings[8].c_str())==1) {
        videoStream = true;
    }
    else {
        videoStream = false;
        vidCount = 0;
    }
    
    if (atoi(numberInStrings[9].c_str())==1) {
        colorVideo = true;
    }
    else {
        colorVideo = false;
    }
    
    vidResNew = atoi(numberInStrings[10].c_str());
    
    if (atoi(numberInStrings[11].c_str())==1) {
        motorOn = true;
    }
    else{
        motorOn = false;
    }
    
    if (atoi(numberInStrings[12].c_str())==1) {
        
        for (int i=13; i<25; i++) {
            settingsData[i-13] = atof(numberInStrings[i].c_str());
        }

        inputData[6] = atof(numberInStrings[25].c_str());
        
        inputData[7] = atof(numberInStrings[26].c_str());
        
        inputData[8] = atof(numberInStrings[27].c_str());

        saveSettnings = true;
        
        printf("Joy sen: %f\n", inputData[6]);
        printf("Joy sen: %f\n", inputData[7]);
        printf("Joy sen: %f\n", inputData[8]);

        printf("PID parameters and joystick sensetivity read and saved\n");
    }
}

void Com::reciveMessage() {

    //printf("Waitning for message\n");

    msgBuffer = "";
    msg = "";
    msgSize = 0;
    //printf("Setting Buffer to zero\n");
    bzero(recvBuf, 1024);

    while (1) {

        numBytes = recv(newsockfd, recvBuf, sizeof(recvBuf), 0);
        //printf("Done with recv\n");
        if (static_cast<unsigned int>(numBytes) == -1) {
            connected = false;
            printf("Time-out\n");
            perror("read");
            return;
        }

        else if (numBytes == 0) {
            printf("Maybe lost connection to client, closing socket and starting to listing\n");
            connected = false;
            return;
        }

        else {
            //printf("convert buffer to string\n");
            msgBuffer = std::string(recvBuf);
            //std::cout << "Raw message: " << msgBuffer << std::endl;
        }

        if (msgSize == 0 && msgBuffer.size()>=3) {
            msgSize = atoi(msgBuffer.substr(0,3).c_str());
            //printf("Message size: %i\n", msgSize);
        }

        if (msgSize>0 && msgBuffer.size() == static_cast<unsigned int>((msgSize+3))) {
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
        //std::cout << token << std::endl;
        numberInStrings[i] = token;
        msg.erase(0, pos + subDelimiter.length());
        i++;
    }

    numberInStrings[i] = msg;
    //std::cout << msg << std::endl;
    clientIdentity = atoi(numberInStrings[1].c_str());
    clientName = numberInStrings[2];
}

void Com::sendSettingsData() {
    ostr.str("");

    for (int i=0; i<14; i++) {
        ostr << settingsData[i] << ":";
    }
    ostr << settingsData[14];
    
    
    
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

    strcpy(req.ifr_name, "wlan1");

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
    strcpy(req2.ifr_name, "wlan1");
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

    this->output[17] = sigInfo->bitrate;
    this->output[18] = (double)sigInfo->level;
    
    return 0;
}

void Com::closeClient() {
    close(newsockfd);
    close(sockfd);
    std::cout << "Connection closed." << std::endl;
    sleep(2);
    connected = false;
}

void Com::setOutputData(double *out, double *pwm, double *ref, double &freq, double *err) {
    output[0] = out[3]*radToDeg;
    output[1] = out[4]*radToDeg;
    output[2] = out[5]*radToDeg;
    output[3] = ref[0]*radToDeg;
    output[4] = ref[1]*radToDeg;
    output[5] = ref[2]*radToDeg;
    output[6] = pwm[0];
    output[7] = pwm[1];
    output[8] = pwm[2];
    output[9] = pwm[3];
    output[10] = cos(out[4])*out[0]-sin(out[4]);
    output[11] = cos(out[3])*out[1]-sin(out[3]);
    output[12] = out[2];
    output[13] = err[0];
    output[14] = err[1];
    output[15] = err[2];
    output[16] = freq;
}

void Com::setSettingsData(double *params) {
    settingsData[0] = params[0];
    settingsData[1] = params[1];
    settingsData[2] = params[2];
    settingsData[3] = params[3];
    settingsData[4] = params[4];
    settingsData[5] = params[5];
    settingsData[6] = params[6];
    settingsData[7] = params[7];
    settingsData[8] = params[8];
    settingsData[9] = params[9];
    settingsData[10] = params[10];
    settingsData[11] = params[11];

}

void Com::getSettingsData(double *params){
	params[0] = settingsData[0];
	params[1] = settingsData[1];
	params[2] = settingsData[2];
	params[3] = settingsData[3];
	params[4] = settingsData[4];
	params[5] = settingsData[5];
	params[6] = settingsData[6];
	params[7] = settingsData[7];
	params[8] = settingsData[8];
	params[9] = settingsData[9];
	params[10] = settingsData[10];
	params[11] = settingsData[11];
}
