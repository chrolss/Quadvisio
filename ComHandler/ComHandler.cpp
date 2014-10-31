//
//  ComHandler.cpp
//  ComHandler
//
//  Created by Toni Axelsson on 2014-09-26.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//
//
/////////////// INSTRUCTIONS /////////////////////////
//
//
// QvisDev
//
// Incoming Message Structure /////////////
//
// Yaw : Throttle : Roll : Pitch : RollOffset : PitchOffset : Reset Integral : Video : Color : Resolution : Motor on :
// Data ind : All PIDs : Joystick Sensitivity
//
// "controllerInputData" structure: [ Roll | Pitch | Yaw | Throttle | RollOffset | PitchOffset]
//
// "outputData" structure: [angles | refangles | pwms | speed | sidespeed | altitude | integral roll | integral pitch | integral yaw | Hz | bitrate | dbm]
//
// Outgoing Message Structure ///////////
//
// angles : refangles : pwm : speed : sidespeed : altitude : integral roll : integral pitch : integral yaw :
// Hz : bitrate : dbm : errorMessage : imgSize - Image
//
//
// SettingsData[] = [pids | trimRoll | trimPitch | JoySen]
//
//
//
//
//
//
// QvisPro
//
// Incoming Message Structure /////////////
//
// Yaw : Throttle : Roll : Pitch
//
// Outgoing Message Structure ///////////
//
// roll : pitch : yaw : refangels : pwm : wifi : data ind


/////////////// COMMUNICATION PROTOCOL ///////////////////////////
//
// Orders: 1 = Connect, 2 = Give me your identity
//
// App IDs: 1 = QvisLight, 2 = QvisPro, 3 = QvisDev
//
//
//


#include "ComHandler.h"

ComHandler::ComHandler(bool enableCamera) {
    connected = false;
    reciveMsg = false;
    sendMsg = false;
    listening = false;
    videoStream=false;
    sendImage=false;
    motorOn=false;
    colorVideo=true;
    saveSettings = false;
    resetIntegral = false;
    
    
    vidCount = 0;
    vidLimit = 0;
    vidRes = 0; // Default 0 = 320x240
    vidResNew = 0;
    errMsg = "Nothing wrong here!!";
        
    for (unsigned int i = 0; i<(sizeof(output)/sizeof(*output)); i++) {
        output[i] = 0.5;
    }
    
    sizeOfOutput = (sizeof(output)/sizeof(*output));
    
    for (unsigned int i = 0; i<(sizeof(settingsData)/sizeof(*settingsData)); i++) {
        settingsData[i] = 0.5;
    }
    
    for (unsigned int i = 0; i<(sizeof(numberInStrings)/sizeof(*numberInStrings)); i++) {
        numberInStrings[i] = "";
    }
    
    for (unsigned int i = 0; i<(sizeof(controllerInputData)/sizeof(*controllerInputData)); i++) {
        controllerInputData[i] = -1000.0;
    }
    
    if(enableCamera==true) {
        camManager = new CameraManager2(640,480);
    }
    
    sleep(1);
    
}

void ComHandler::error(const char *msg)
{
    closeClient();
    perror(msg);
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
    

    // Set up socket time out time
    struct timeval tv;
    
    tv.tv_sec = 4;  // 30 Secs Timeout
    tv.tv_usec = 0;  // Not init'ing this can cause strange errors
    
    setsockopt(newsockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));

    this->reciveMsg=true;
    this->listening=false;
    this->connected = true;
    this->sendMsg = false;
    
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
    
    std::cout << "Inside QvisDev Loop\n" << std::endl;
    std::cout << "Sending settings data" << std::endl;
    sendSettingsData();
    std::cout << "Settings data sent" << std::endl;
    
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
    
    ostr.str("");
    
    for (int i=0; i<10; i++) {
        ostr << output[i] << ":";
    }
    
    // Wifi signal
    ostr << "0:";
    
    if (vidResNew != vidRes) {
        printf("New res: %i, old res: %i\n", this->vidResNew, this->vidRes);
        /*
        switch (vidResNew) {
            case 0:
                camManager->change_res(320, 240);
                break;
                
            case 1:
                camManager->change_res(640, 480);
                break;
                
            case 2:
                camManager->change_res(1280, 720);
                break;
                
            case 3:
                camManager->change_res(1920, 1080);
                break;
                
            default:
                break;
        }
        */
        printf("New resolution was set\n");
        vidRes = vidResNew;
    }

    if (sendImage && videoStream) {
        jpg_dat = camManager->get_jpg_data();
        ostr << jpg_dat.size;
        std::cout << "JPG size" << jpg_dat.size << std::endl;
    }
    
    else {
        ostr << "0";
    }

    std::string s;
    s = ostr.str();
    ostr.str("");
    
    if ((s.length()+1)<10) {ostr << "000" << (s.length()+1) << ":" << s;}
    else if((s.length()+1)>=10 && (s.length()+1)<100) {ostr << "00" << (s.length()+1) << ":" << s;}
    else if((s.length()+1)>=100 && (s.length()+1)<1000) {ostr << "0" << (s.length()+1) << ":" << s;}
    else {ostr << (s.length()+1) << ":" << s;}
    
    s = ostr.str();
    
    //std::cout << s << std::endl;

    if (send(newsockfd, s.c_str(), s.length(),0) == -1) {
        closeClient();
        perror("send");
    }
    
    if (sendImage && videoStream) {
        send_img();
        sendImage = false;
    }
}

void ComHandler::sendQvisDevMsg() {
    
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
    
    if (vidResNew != vidRes) {
        printf("New res: %i, old res: %i\n", this->vidResNew, this->vidRes);
        switch (vidResNew) {
            case 0:
                camManager->change_res(320, 240);
                break;
                
            case 1:
                camManager->change_res(640, 480);
                break;
                
            case 2:
                camManager->change_res(1280, 720);
                break;
                
            case 3:
                camManager->change_res(1920, 1080);
                break;
                
            default:
                break;
        }
        printf("New resolution was set\n");
        vidRes = vidResNew;
    }
    
    if (sendImage && videoStream) {
        jpg_dat = camManager->get_jpg_data();
        ostr << jpg_dat.size;
    }
    
    else {
        ostr << "0";
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
    
    if (sendImage && videoStream) {
        send_img();
        sendImage = false;
    }

}


void ComHandler::sendQvisLightMsg() {
    
}

void ComHandler::send_img() {
    if (send(newsockfd, jpg_dat.buffer, jpg_dat.size, 0) == -1) {
        closeClient();
        perror("send");
    }
    vidCount=0;
}

void ComHandler::readQvisProMsg() {
    
    std::string msg = this->reciveMessage();
    
    //printf("Final message:\n");
    //std::cout << msg << std::endl;
    
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

    for (int i = 1 ; i<5; i++) {
           controllerInputData[i-1] = atof(numberInStrings[i].c_str());
       }

    if (atoi(numberInStrings[5].c_str())==1) {
        motorOn = true;
    }
    else{
        motorOn = false;
    }
    
    if (atoi(numberInStrings[6].c_str())==0) {
        return;
    }
    
    else if(atoi(numberInStrings[6].c_str())==3){
        printf("Applying camara settings\n");
        if(atoi(numberInStrings[7].c_str())==1) {videoStream = true;}
        else {videoStream = false;}
        vidResNew = atoi(numberInStrings[8].c_str());
    }
}

void ComHandler::readQvisDevMsg() {
    
    std::string msg = this->reciveMessage();
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
    
    for (int i = 1 ; i<7; i++) {
        controllerInputData[i-1] = atof(numberInStrings[i].c_str());
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
        
        for (int i=13; i<26; i++) {
            settingsData[i-13] = atof(numberInStrings[i].c_str());
        }
        
        settingsData[13] = controllerInputData[4];
        settingsData[14] = controllerInputData[5];
        
        controllerInputData[6] = atof(numberInStrings[25].c_str());
        
        saveSettings = true;
        
        printf("Joy sen: %f\n", controllerInputData[6]);
        printf("PID parameters and joystick sensetivity read and saved\n");
    }

}

void ComHandler::readQvisLightMsg() {
    
}

Client ComHandler::reciveOrder() {
    
    std::string msg = this->reciveMessage();
    
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
    
    Client clientData;
    
    clientData.name = numberInStrings[1];
    clientData.type = atoi(numberInStrings[2].c_str());
    clientData.order = atoi(numberInStrings[3].c_str());
    
    //uncomment for QvisDev, comment for Pro
    //sendMsg = true;
    //reciveMsg = false;

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
        
        if (numBytes == -1) {
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
        }
        
        if (msgSize == 0 && msgBuffer.size()>=3) {
            msgSize = atoi(msgBuffer.substr(0,3).c_str());
        }
        
        if (msgSize>0 && msgBuffer.size() == (msgSize+3)) {
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

void ComHandler::sendSettingsData() {
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
    reciveMsg = true;
    sendMsg = false;
}


int ComHandler::getSigStrength() {
    return 60;
}

int ComHandler::getSignalInfo() {
    /*
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
    
    */
    return 0;
}


void ComHandler::closeClient() {
    close(newsockfd);
    close(sockfd);
    std::cout << "Connection closed." << std::endl;
    sleep(2);
    connected = false;
}

void ComHandler::setOutputData(double *out, double *pwm, double *ref, double &freq, double *err) {
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

void ComHandler::setSettingsData(double *params) {
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
    settingsData[12] = params[12];
    settingsData[13] = params[13];
    settingsData[14] = params[14];
}

void ComHandler::getSettingsData(double *params){
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
    params[12] = settingsData[12];
    params[13] = settingsData[13];
    params[14] = settingsData[14];
}
