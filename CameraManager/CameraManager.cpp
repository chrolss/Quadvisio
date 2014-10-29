//
//  CameraManager.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "CameraManager.h"

static unsigned char dht_data[DHT_SIZE] = {
    0xff, 0xc4, 0x01, 0xa2, 0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
    0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x01, 0x00, 0x03,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
    0x0a, 0x0b, 0x10, 0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05,
    0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7d, 0x01, 0x02, 0x03, 0x00, 0x04,
    0x11, 0x05, 0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22,
    0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08, 0x23, 0x42, 0xb1, 0xc1, 0x15,
    0x52, 0xd1, 0xf0, 0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x34, 0x35, 0x36,
    0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a,
    0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66,
    0x67, 0x68, 0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a,
    0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95,
    0x96, 0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8,
    0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2,
    0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5,
    0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
    0xe8, 0xe9, 0xea, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9,
    0xfa, 0x11, 0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04, 0x07, 0x05,
    0x04, 0x04, 0x00, 0x01, 0x02, 0x77, 0x00, 0x01, 0x02, 0x03, 0x11, 0x04,
    0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22,
    0x32, 0x81, 0x08, 0x14, 0x42, 0x91, 0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33,
    0x52, 0xf0, 0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34, 0xe1, 0x25,
    0xf1, 0x17, 0x18, 0x19, 0x1a, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x35, 0x36,
    0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a,
    0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66,
    0x67, 0x68, 0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a,
    0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94,
    0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba,
    0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
    0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
    0xe8, 0xe9, 0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa
};


void CameraManager::s_signal_handler (int signal_value)
{
    s_interrupted = 1;
}

static int xioctl(int fh, int request, void *arg) {
    int r;
    
    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);
    
    return r;
}

CameraManager::CameraManager() {
    
    std::cout << "Hej2" << std::endl;
    
    pixel_format = V4L2_PIX_FMT_MJPEG;
    s_interrupted = 0;
    sprintf(dev_name, "/dev/video0");
    io = IO_METHOD_MMAP;
    fd = -1;
    frame_count = 1;
    width = 640;
    height = 480;
    fps = 30;
    timeout = 1;
    timeouts_max = 1;

    sprintf(out_name, "capture.jpg");
    std::cout << "Hej3" << std::endl;

}

int CameraManager::initializeCamera(int _width, int _height) {

    width = _width;
    height = _height;
    std::cout << "Hej4" << std::endl;


    open_device();

    init_device();

    start_capturing();

    return 0;
}

void CameraManager::open_device() {
    
    struct stat st;
    std::cout << "Hej5" << std::endl;

    if (-1 == stat(dev_name, &st)) {
        fprintf(stderr, "Cannot identify '%s': %d, %s\n",
                dev_name, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    std::cout << "Hej6" << std::endl;

    if (!S_ISCHR(st.st_mode)) {
        fprintf(stderr, "%s is no device\n", dev_name);
        exit(EXIT_FAILURE);
    }
    
    fd = open(dev_name, O_RDWR /* required */ | O_NONBLOCK, 0);
    std::cout << "Hej7" << std::endl;

    if (-1 == fd) {
        fprintf(stderr, "Cannot open '%s': %d, %s\n",
                dev_name, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void CameraManager::init_device() {
    struct v4l2_format fmt;
    
    CLEAR(fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = width;
    fmt.fmt.pix.height      = height;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;
    xioctl(fd, VIDIOC_S_FMT, &fmt);
    if (fmt.fmt.pix.pixelformat != V4L2_PIX_FMT_MJPEG) {
        printf("Libv4l didn't accept RGB24 format. Can't proceed.\n");
        exit(EXIT_FAILURE);
    }
    
    init_mmap();

}

void CameraManager::init_mmap() {
    struct v4l2_requestbuffers req;
    
    CLEAR(req);
    
    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    
    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s does not support "
                    "memory mapping\n", dev_name);
            exit(EXIT_FAILURE);
        } else {
            perror("VIDIOC_REQBUFS");
        }
    }
    
    if (req.count < 2) {
        fprintf(stderr, "Insufficient buffer memory on %s\n",
                dev_name);
        exit(EXIT_FAILURE);
    }
        
    if (!buffers) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
        struct v4l2_buffer buf;
        
        CLEAR(buf);
        
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;
        
        if (-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
            perror("VIDIOC_QUERYBUF");
        
        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start =
        mmap(NULL /* start anywhere */,
             buf.length,
             PROT_READ | PROT_WRITE /* required */,
             MAP_SHARED /* recommended */,
             fd, buf.m.offset);
        
        if (MAP_FAILED == buffers[n_buffers].start)
            perror("mmap");
    }

}

void CameraManager::start_capturing() {
    unsigned int i;
    enum v4l2_buf_type type;
    

    for (i = 0; i < n_buffers; ++i) {
        struct v4l2_buffer buf;
        
        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        
        if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
            perror("VIDIOC_QBUF");
    }
    
    std::cout << "Stream on" << std::endl;

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
        perror("VIDIOC_STREAMON");

}

void CameraManager::grab_frame() {
    std::cout << "Grabbing frame" << std::endl;

    clock_t begin, end;
    double time_spent;
    
    int count;
    int timeout_count;
    
    count = frame_count;
    timeout_count = timeouts_max;
    
    begin = clock();
    for (;;) {
        if (s_interrupted < 0) {
            fprintf(stderr, "\nInterrupt received - aborting capture\n");
            return;
        }
        
        fd_set fds;
        struct timeval tv;
        int r;
        
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        
        /* Timeout. */
        tv.tv_sec = timeout;
        tv.tv_usec = 0;
        
        r = select(fd + 1, &fds, NULL, NULL, &tv);
        
        if (-1 == r) {
            if (EINTR == errno)
                continue;
            perror("select");
        }
        
        if (0 == r) {
            if (timeout_count > 0) {
                timeout_count--;
            } else {
                fprintf(stderr, "select timeout\n");
                exit(EXIT_FAILURE);
            }
        }
        
        if (read_frame())
            break;
        /* EAGAIN - continue select loop. */
    }
    
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "Captured %i frames in %f seconds\n", frame_count, time_spent);
    
    
}

int CameraManager::read_frame() {
    struct v4l2_buffer buf;
    
    CLEAR(buf);
    std::cout << "reading frame" << std::endl;

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    
    if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
        switch (errno) {
            case EAGAIN:
                return 0;
                
            case EIO:
                /* Could ignore EIO, see spec. */
                
                /* fall through */
                
            default:
                perror("VIDIOC_DQBUF");
        }
    }
    
    assert(buf.index < n_buffers);

    unsigned char *tmpbuffer;
    
    memcpy (tmpbuffer, buffers[buf.index], HEADERFRAME1);
    memcpy (tmpbuffer + HEADERFRAME1, dht_data, DHT_SIZE);
    memcpy (tmpbuffer + HEADERFRAME1 + DHT_SIZE, buffers[buf.index] + HEADERFRAME1, (buf.bytesused - HEADERFRAME1));
    
    std::cout << "Bytes used: " << buf.bytesused << std::endl;
    
    process_image(tmpbuffer, buf.bytesused);
    
    if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
        perror("VIDIOC_QBUF");
    
    return 1;

}

void CameraManager::process_image(const void *p, int size) {
    if (out_buf) {
        FILE *outfile = fopen( out_name, "wb" );
        
        // try to open file for saving
        if (!outfile) {
            perror("jpeg");
        }
        // write the image and flush
        fwrite(p, size, 1, outfile);
        fflush(outfile);
        
        // close output file
        fclose(outfile);
        
        fflush(stderr);
        fprintf(stderr, ".");
    }
}


void CameraManager::stop_capturing() {
    enum v4l2_buf_type type;
    
    std::cout << "Stream off" << std::endl;

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type))
        perror("VIDIOC_STREAMOFF");
}

void CameraManager::uninit_device() {
    int i;

    for (i = 0; i < n_buffers; ++i) {
        if (-1 == munmap(buffers[i].start, buffers[i].length)) {
            perror("munmap");
        }
    }
    
    //free(buffers);

}

void CameraManager::close_device() {
    if (-1 == close(fd))
        perror("close");
    
    fd = -1;
}

void CameraManager::closeCamera() {
    stop_capturing();
    uninit_device();
    close_device();
}

