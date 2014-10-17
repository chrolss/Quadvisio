//
//  CameraManager.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "CameraManager.h"

static int xioctl(int fd, int request, void *arg)
{
    int r;
    
    do r = ioctl (fd, request, arg);
    while (-1 == r && EINTR == errno);
    
    return r;
}

CameraManager::CameraManager() {
    
    image_number = 0;
    fd = -1;
    
    //this->initializeCamera();
}

int CameraManager::initializeCamera(int width, int height) {
    
    fd = open("/dev/video0", O_RDWR|O_NONBLOCK, 0);
    if (fd == -1)
    {
        perror("Opening video device");
    }
    /*
    struct v4l2_capability caps = {0};
    
    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &caps))
    {
        perror("Querying Capabilities");
    }
    
    printf( "Driver Caps:\n"
           "  Driver: \"%s\"\n"
           "  Card: \"%s\"\n"
           "  Bus: \"%s\"\n"
           "  Version: %d.%d\n"
           "  Capabilities: %08x\n",
           caps.driver,
           caps.card,
           caps.bus_info,
           (caps.version>>16)&&0xff,
           (caps.version>>24)&&0xff,
           caps.capabilities);
    
    
    struct v4l2_cropcap cropcap;
    CLEAR(cropcap);
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl (fd, VIDIOC_CROPCAP, &cropcap))
    {
        perror("Querying Cropping Capabilities");
    }
    
    printf( "Camera Cropping:\n"
           "  Bounds: %dx%d+%d+%d\n"
           "  Default: %dx%d+%d+%d\n"
           "  Aspect: %d/%d\n",
           cropcap.bounds.width, cropcap.bounds.height, cropcap.bounds.left, cropcap.bounds.top,
           cropcap.defrect.width, cropcap.defrect.height, cropcap.defrect.left, cropcap.defrect.top,
           cropcap.pixelaspect.numerator, cropcap.pixelaspect.denominator);
    
    int support_grbg10 = 0;
    
    struct v4l2_fmtdesc fmtdesc = {0};
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    char fourcc[5] = {0};
    char c, e;
    printf("  FMT : CE Desc\n--------------------\n");
    while (0 == xioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc))
    {
        strncpy(fourcc, (char *)&fmtdesc.pixelformat, 4);
        if (fmtdesc.pixelformat == V4L2_PIX_FMT_SGRBG10)
            support_grbg10 = 1;
        c = fmtdesc.flags & 1? 'C' : ' ';
        e = fmtdesc.flags & 2? 'E' : ' ';
        printf("  %s: %c%c %s\n", fourcc, c, e, fmtdesc.description);
        fmtdesc.index++;
    }
    */
    
    struct v4l2_format fmt;
    CLEAR(fmt);
    
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    fmt.fmt.pix.field = V4L2_FIELD_NONE;
    
    if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
    {
        perror("Setting Pixel Format");
    }
    /*
    strncpy(fourcc, (char *)&fmt.fmt.pix.pixelformat, 4);
    printf( "Selected Camera Mode:\n"
           "  Width: %d\n"
           "  Height: %d\n"
           "  PixFmt: %s\n"
           "  Field: %d\n",
           fmt.fmt.pix.width,
           fmt.fmt.pix.height,
           fourcc,
           fmt.fmt.pix.field);
    */
    struct v4l2_requestbuffers req;
    CLEAR(req);
    req.count = 2;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    
    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req))
    {
        perror("Requesting Buffer");
    }
    
    
    for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
        CLEAR(buf);
        
        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = n_buffers;
        
        if(-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf))
        {
            perror("Querying Buffer");
        }
        
        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start = v4l2_mmap(NULL, buf.length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
        printf("Length: %d\nAddress: %p\n", buf.length, buffer);
        printf("Image Length: %d\n", buf.bytesused);
        
        if (MAP_FAILED == buffers[n_buffers].start) {
            perror("mmap");
            return -1;
        }
    }
    
    for (i = 0; i < n_buffers; ++i) {
        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        if(-1 == xioctl(fd, VIDIOC_QBUF, &buf))
        {
            perror("Query Buffer");
        }
    }
    
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    
    if(-1 == xioctl(fd, VIDIOC_STREAMON, &type))
    {
        perror("Start Capture");
    }
    
    return 0;
}

void * CameraManager::getImageBuffer() {
    
    do {
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        
        /* Timeout. */
        tv.tv_sec = 2;
        tv.tv_usec = 0;
        
        r = select(fd + 1, &fds, NULL, NULL, &tv);
    } while ((r == -1 && (errno = EINTR)));
    
    if(-1 == r)
    {
        perror("Waiting for Frame");
    }
    
    CLEAR(buf);
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    
    if(-1 == xioctl(fd, VIDIOC_DQBUF, &buf))
    {
        perror("Retrieving Frame");
    }
    
    jpg_buffer = (void*)buffers[buf.index].start;
    jpg_buffer_size =(size_t)buffers[buf.index].length;
    
    /*
    printf ("saving image\n");
    
    IplImage* frame;
    printf("Converting to Mat\n");
    CvMat cvmat = cvMat(480, 640, CV_8UC3, (void*)buffers[buf.index].start);
    printf("Decoding\n");
    frame = cvDecodeImage(&cvmat, 1);
    printf("Waitkey\n");
    cvWaitKey(0);
    printf("Saving\n");
    sprintf(out_name, "frame%03d.jpg", image_number);
    image_number++;
    cvSaveImage(out_name, frame, 0);
     */
    
    xioctl(fd, VIDIOC_QBUF, &buf);
    return jpg_buffer;
}

size_t CameraManager::getImageBufferSize() {
    return jpg_buffer_size;
}

void CameraManager::closeCamera() {
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    xioctl(fd, VIDIOC_STREAMOFF, &type);
    for (i = 0; i < n_buffers; ++i)
        v4l2_munmap(buffers[i].start, buffers[i].length);
    v4l2_close(fd);
}

