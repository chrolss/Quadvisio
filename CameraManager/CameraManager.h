//
//  CameraManager.h
//  Atlas Software
//
//  Created by Toni Axelsson on 2014-10-16.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

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

#include <linux/videodev2.h>

#define CLEAR(x) memset(&(x), 0, sizeof(x))

enum io_method {
    IO_METHOD_READ,
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
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
    
private:
    void open_device();
    void init_device();
    void start_capturing();
    void stop_capturing();
    void uninit_device();
    void close_device();
    void init_mmap();
    void read_frame();
    void s_signal_handler (int signal_value);
    
    int s_interrupted;
    char *dev_name;
    enum io_method io;
    int fd;
    buffer buffers[4];
    unsigned int n_buffers;
    int out_buf;
    int frame_count = 1;
    int set_format;
    unsigned int width;
    unsigned int height;
    unsigned int fps;
    unsigned int timeout;
    unsigned int timeouts_max;
    char *out_name;

};