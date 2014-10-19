//
//  CameraManager.h
//  Atlas Software
//
//  Created by Toni Axelsson on 2014-10-16.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>             /* getopt_long() */
#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <time.h>
#include <thread>

#include <linux/videodev2.h>

#define CLEAR(x) memset(&(x), 0, sizeof(x))

enum io_method {
    IO_METHOD_READ,
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
};

struct jpg_data {
    void *buffer;
    int size;
};

struct buffer {
    void   *start;
    size_t length;
};

class CameraManager{
    
public:
    CameraManager();
    int initializeCamera(int _width, int _heigth);
    void grab_frame();
    void closeCamera();
    jpg_data get_jpg_data();
    int get_jpg_buffer_size();
    void change_res(int _width, int _height);
    
private:
    void open_device();
    void init_device();
    void start_capturing();
    void stop_capturing();
    void uninit_device();
    void close_device();
    void init_mmap();
    int read_frame();
    void process_image(const void *p, int size);
    void s_signal_handler (int signal_value);
    void startCameraThread();
    
    int s_interrupted;
    char dev_name[256];
    enum io_method io;
    int fd;
    buffer buffers[4];
    unsigned int n_buffers;
    int out_buf;
    int frame_count = 1;
    int set_format;
    int width;
    int height;
    int fps;
    int timeout;
    int timeouts_max;
    char out_name[256];
    
    void *jpg_buffer;
    int jpg_buffer_size;
    bool frame_read;
    bool saving_buffer;
    
    unsigned int pixel_format;

};