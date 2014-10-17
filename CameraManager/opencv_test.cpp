//
//  main.cpp
//  CameraManager
//
//  Created by Toni Axelsson on 2014-10-16.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int main(int argc, const char * argv[]) {

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    

    Mat frame;
    frame = cap.grab();
    std::cout << frame.total() << std::endl;

    return 0;
}