//
//  CameraManager.h
//  Atlas Software
//
//  Created by Toni Axelsson on 2014-10-16.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <libv4l2.h>
#include <sys/time.h>
#include <sys/types.h>
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
    int initializeCamera(int width, int heigth);
    void * getImageBuffer();
    size_t getImageBufferSize();
    void closeCamera();
    
private:
    
    int r, fd;
    
    fd_set fds;
    struct timeval tv;
    
    int image_number;
    char out_name[256];

    void *jpg_buffer;
    size_t jpg_buffer_size;
    struct buffer buffers[2];
    struct v4l2_buffer buf;
    unsigned int i, n_buffers;
    enum v4l2_buf_type type;
};