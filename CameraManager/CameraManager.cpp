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
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    struct v4l2_streamparm frameint;
    int min;

    
    
    CLEAR(fmt);
    
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (set_format) {
        fmt.fmt.pix.width = width;
        fmt.fmt.pix.height = height;
        fmt.fmt.pix.pixelformat = pixel_format;
        fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
        
        if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt))
            perror("VIDIOC_S_FMT");
        
        if (fmt.fmt.pix.pixelformat != pixel_format) {
            fprintf(stderr,"Libv4l didn't accept pixel format. Can't proceed.\n");
            exit(EXIT_FAILURE);
        }
        
        /* Note VIDIOC_S_FMT may change width and height. */
    } else {
        /* Preserve original settings as set by v4l2-ctl for example */
        if (-1 == xioctl(fd, VIDIOC_G_FMT, &fmt))
            perror("VIDIOC_G_FMT");
    }
    
    /*
    CLEAR(frameint);
    
    // Attempt to set the frame interval.
    frameint.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    frameint.parm.capture.timeperframe.numerator = 1;
    frameint.parm.capture.timeperframe.denominator = fps;
    if (-1 == xioctl(fd, VIDIOC_S_PARM, &frameint))
        fprintf(stderr, "Unable to set frame interval.\n");
    
    // Buggy driver paranoia.
    min = fmt.fmt.pix.width * 2;
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;
    */
    
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
    
    switch (io) {
        case IO_METHOD_READ:
            /* Nothing to do. */
            break;
            
        case IO_METHOD_MMAP:
            for (i = 0; i < n_buffers; ++i) {
                struct v4l2_buffer buf;
                
                CLEAR(buf);
                buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory = V4L2_MEMORY_MMAP;
                buf.index = i;
                
                if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
                    perror("VIDIOC_QBUF");
            }
            type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
                perror("VIDIOC_STREAMON");
            break;
            
        case IO_METHOD_USERPTR:
            for (i = 0; i < n_buffers; ++i) {
                struct v4l2_buffer buf;
                
                CLEAR(buf);
                buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory = V4L2_MEMORY_USERPTR;
                buf.index = i;
                buf.m.userptr = (unsigned long) buffers[i].start;
                buf.length = buffers[i].length;
                
                if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
                    perror("VIDIOC_QBUF");
            }
            type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            if (-1 == xioctl(fd, VIDIOC_STREAMON, &type))
                perror("VIDIOC_STREAMON");
            break;
    }
}

void CameraManager::grab_frame() {
    
    clock_t begin, end;
    double time_spent;
    
    unsigned int count;
    unsigned int timeout_count;
    
    count = frame_count;
    timeout_count = timeouts_max;
    
    begin = clock();
    for (;;) {
        if (s_interrupted) {
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
    unsigned int i;
    
    switch (io) {
        case IO_METHOD_READ:
            if (-1 == read(fd, buffers[0].start, buffers[0].length)) {
                switch (errno) {
                    case EAGAIN:
                        return 0;
                        
                    case EIO:
                        /* Could ignore EIO, see spec. */
                        
                        /* fall through */
                        
                    default:
                        perror("read");
                }
            }
            
            process_image(buffers[0].start, buffers[0].length);
            break;
            
        case IO_METHOD_MMAP:
            CLEAR(buf);
            
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
            
            process_image(buffers[buf.index].start, buf.bytesused);
            
            if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
                perror("VIDIOC_QBUF");
            break;
            
        case IO_METHOD_USERPTR:
            CLEAR(buf);
            
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_USERPTR;
            
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
            
            for (i = 0; i < n_buffers; ++i)
                if (buf.m.userptr == (unsigned long) buffers[i].start
                    && buf.length == buffers[i].length)
                    break;
            
            assert(i < n_buffers);
            
            process_image((void *) buf.m.userptr, buf.bytesused);
            
            if (-1 == xioctl(fd, VIDIOC_QBUF, &buf))
                perror("VIDIOC_QBUF");
            break;
    }
    
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
    
    switch (io) {
        case IO_METHOD_READ:
            /* Nothing to do. */
            break;
            
        case IO_METHOD_MMAP:
        case IO_METHOD_USERPTR:
            type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type))
                perror("VIDIOC_STREAMOFF");
            break;
    }
}

void CameraManager::uninit_device() {
    unsigned int i;
    
    switch (io) {
        case IO_METHOD_READ:
            free(buffers[0].start);
            break;
            
        case IO_METHOD_MMAP:
            for (i = 0; i < n_buffers; ++i)
                if (-1 == munmap(buffers[i].start, buffers[i].length))
                    perror("munmap");
            break;
            
        case IO_METHOD_USERPTR:
            for (i = 0; i < n_buffers; ++i)
                free(buffers[i].start);
            break;
    }
    
    free(buffers);

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

