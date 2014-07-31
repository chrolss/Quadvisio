//
//  main.cpp
//  Communicate
//
//  Created by Toni Axelsson on 2014-05-15.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Com.h"

int main(int argc, const char * argv[])
{
    double output[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    int count = 0;
    std::cout << "Starting communication thread" << std::endl;
    Com C;
    sleep(1);
    
    cv::VideoCapture cap;
    cv::Mat frame;
    
    std::cout << "Setting up camera" << std::endl;
    cap.open(0);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    sleep(1);
    
    std::cout << "Clearing video buffer" << std::endl;
    
    for (int i=0; i<21; i++) {
        cap >> frame;
    }
    
    std::cout << "Starting main loop" << std::endl;
    while (true) {
        if (C.connected && !C.reciveMsg) {
            C.setOutputData(output);
            
            if (count>=5) {
                std::cout << "capturing frame" << std::endl;
                cap >> frame;
                //cv::imshow("window", frame);
                C.sendFrame = frame;
                std::cout << "frame captured" << std::endl;
                C.imgSend = true;
                count=0;
            }
            C.msgSend=true;
        }
        
        if(cv::waitKey(30) >= 0) break;
        count++;
        usleep(100000);
    }
    C.closeClient();
    return 0;
}

