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

#define CLEAR(x) memset(&(x), 0, sizeof(x))

struct buffer {
    void   *start;
    size_t length;
};

class CameraManager{
    
public:
    CameraManager();
    int initializeCamera();
    void getImageBuffer();
    void closeCamera();
    void setResolution(int width, int height);
    
private:
    
    int fd;
    
    int image_number;
    char out_name[256];

    void *buffer;
    struct buffer *buffers;
    struct v4l2_buffer buf;
    
};