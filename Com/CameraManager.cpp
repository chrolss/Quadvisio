//
//  CameraManager.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "CameraManager.h"

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
    frame_read = false;

    sprintf(out_name, "capture.jpg");

}

int CameraManager::initializeCamera(int _width, int _height) {

    width = _width;
    height = _height;


    open_device();
    init_device();
    start_capturing();

    return 0;
}

void CameraManager::open_device() {
    
    struct stat st;

    if (-1 == stat(dev_name, &st)) {
        fprintf(stderr, "Cannot identify '%s': %d, %s\n",
                dev_name, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (!S_ISCHR(st.st_mode)) {
        fprintf(stderr, "%s is no device\n", dev_name);
        exit(EXIT_FAILURE);
    }
    
    fd = open(dev_name, O_RDWR /* required */ | O_NONBLOCK, 0);

    if (-1 == fd) {
        fprintf(stderr, "Cannot open '%s': %d, %s\n",
                dev_name, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void CameraManager::init_device() {
    struct v4l2_capability cap;
    struct v4l2_format fmt;
    int min;
    
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

        if (read_frame()) {break;}
        /* EAGAIN - continue select loop. */
    }

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "Captured %i frames in %f seconds\n", frame_count, time_spent);
}

int CameraManager::read_frame() {
    struct v4l2_buffer buf;
    int i;
    
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
    
    //process_image(buffers[buf.index].start, buf.bytesused);
    
    jpg_buffer = buffers[buf.index].start;
    jpg_buffer_size = buf.bytesused;
    
    if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
        perror("VIDIOC_QBUF");
    
    return 1;

}

void *CameraManager::get_jpg_buffer() {
    return jpg_buffer;
}

int CameraManager::get_jpg_buffer_size() {
    return jpg_buffer_size;
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

