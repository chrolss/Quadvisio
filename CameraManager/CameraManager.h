//
//  CameraManager.h
//  Atlas Software
//
//  Created by Toni Axelsson on 2014-10-16.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class CameraManager{
    
public:
    CameraManager();
    int initializeCamera();
    void getImageBuffer();
    void closeCamera();
    
private:
    
    int fd;

    uint8_t *buffer;
    
};