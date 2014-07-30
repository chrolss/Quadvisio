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
    std::string input = "";
    Com C;
    sleep(1);
    
    cv::VideoCapture cap;
    
    cv::Mat frame, sendFrame;
    
    cap.open(0);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    
    while (true) {
        cap >> frame;
        //cv::imshow("Video", frame);
        /*
        imgSize = (int)frame.total()*(int)frame.elemSize();
        std::cout << imgSize << std::endl;
        */
        if (C.connected) {
            C.sendImg(frame);
        }
        if(cv::waitKey(30) >= 0) break;
        usleep(1000000);
    }
    C.closeClient();
    return 0;
}

