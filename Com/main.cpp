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
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Com.h"

int main(int argc, const char * argv[])
{
    std::string input = "";
    Com C;
    sleep(1);
    
    cv::VideoCapture cap;
    
    cv::Mat frame, sendFrame;
    int imgSize;
    int i=0;
    
    cap.open(1);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    
    while (true) {
        cap >> frame;
        cv::imshow("Video", frame);
        if (C.connected) {
            C.sendImg(frame);
        }
        else { }
    }
    C.closeClient();
    return 0;
}

