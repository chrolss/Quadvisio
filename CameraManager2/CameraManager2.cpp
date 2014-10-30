//
//  CameraManager.cpp
//  Atlas Software
//
//  Created by Quadvisio on 2014-06-06 as part of the Atlas Project.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include "CameraManager2.h"

CameraManager2::CameraManager2() {
    
    struct vdIn *videoIn = new vdIn;
    char outputfile[40];
    
    init_videoIn(videoIn, "/dev/video0", 640, 480, V4L2_PIX_FMT_MJPEG, 1);
    
    std::cout << videoIn->isstreaming << std::endl;
    
    for (int i = 0; i<6; i++) {
        sprintf(outputfile, "snap%i.jpg", i);
        if (uvcGrab(videoIn) < 0) {
            fprintf (stderr, "Error grabbing\n");
        }
        else {
            FILE *file = fopen(outputfile, "wb");
            fwrite(videoIn->tmpbuffer, videoIn->buf.bytesused + DHT_SIZE, 1, file);
        }
        
    }
    
    close_v4l2(videoIn);
    
    
}

int CameraManager2::init_videoIn(struct vdIn *vd, char *device, int width, int height, int format, int grabmethod)
{
    
    if (vd == NULL || device == NULL)
        return -1;
    if (width == 0 || height == 0)
        return -1;
    if (grabmethod < 0 || grabmethod > 1)
        grabmethod = 1;		//mmap by default;
    vd->videodevice = NULL;
    vd->status = NULL;
    vd->pictName = NULL;
    vd->videodevice = (char *) calloc (1, 16 * sizeof (char));
    vd->status = (char *) calloc (1, 100 * sizeof (char));
    vd->pictName = (char *) calloc (1, 80 * sizeof (char));
    snprintf (vd->videodevice, 12, "%s", device);
    vd->toggleAvi = 0;
    vd->getPict = 0;
    vd->signalquit = 1;
    vd->width = width;
    vd->height = height;
    vd->formatIn = format;
    vd->grabmethod = grabmethod;
    vd->isstreaming = 0;
    if (init_v4l2 (vd) < 0) {
        fprintf (stderr, " Init v4L2 failed !! exit fatal \n");
        goto error;;
    }
    /* alloc a temp buffer to reconstruct the pict */
    vd->framesizeIn = (vd->width * vd->height << 1);

    vd->tmpbuffer = (unsigned char *) calloc (1, (size_t) vd->framesizeIn);
    if (!vd->tmpbuffer)
        goto error;
    vd->framebuffer = (unsigned char *) calloc (1, (size_t) vd->width * (vd->height + 8) * 2);

    if (!vd->framebuffer)
        goto error;
    return 0;
    
error:
    free (vd->videodevice);
    free (vd->status);
    free (vd->pictName);
    close (vd->fd);
    return -1;
}

int CameraManager2::init_v4l2 (struct vdIn *vd)
{
    int i;
    int ret = 0;
    
    if ((vd->fd = open (vd->videodevice, O_RDWR)) == -1) {
        perror ("ERROR opening V4L interface \n");
        exit (1);
    }
    
    memset (&vd->cap, 0, sizeof (struct v4l2_capability));
    ret = ioctl (vd->fd, VIDIOC_QUERYCAP, &vd->cap);
    if (ret < 0) {
        fprintf (stderr, "Error opening device %s: unable to query device.\n",
                 vd->videodevice);
        goto fatal;
    }
    
    if ((vd->cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0) {
        fprintf (stderr,
                 "Error opening device %s: video capture not supported.\n",
                 vd->videodevice);
        goto fatal;;
    }
    if (vd->grabmethod) {
        if (!(vd->cap.capabilities & V4L2_CAP_STREAMING)) {
            fprintf (stderr, "%s does not support streaming i/o\n",
                     vd->videodevice);
            goto fatal;
        }
    } else {
        if (!(vd->cap.capabilities & V4L2_CAP_READWRITE)) {
            fprintf (stderr, "%s does not support read i/o\n", vd->videodevice);
            goto fatal;
        }
    }
    /* set format in */
    memset (&vd->fmt, 0, sizeof (struct v4l2_format));
    vd->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vd->fmt.fmt.pix.width = vd->width;
    vd->fmt.fmt.pix.height = vd->height;
    vd->fmt.fmt.pix.pixelformat = vd->formatIn;
    vd->fmt.fmt.pix.field = V4L2_FIELD_ANY;
    ret = ioctl (vd->fd, VIDIOC_S_FMT, &vd->fmt);
    if (ret < 0) {
        fprintf (stderr, "Unable to set format: %d.\n", errno);
        goto fatal;
    }
    if ((vd->fmt.fmt.pix.width != vd->width) ||
        (vd->fmt.fmt.pix.height != vd->height)) {
        fprintf (stderr, " format asked unavailable get width %d height %d \n",
                 vd->fmt.fmt.pix.width, vd->fmt.fmt.pix.height);
        vd->width = vd->fmt.fmt.pix.width;
        vd->height = vd->fmt.fmt.pix.height;
        /* look the format is not part of the deal ??? */
        //vd->formatIn = vd->fmt.fmt.pix.pixelformat;
    }
    /* request buffers */
    memset (&vd->rb, 0, sizeof (struct v4l2_requestbuffers));
    vd->rb.count = NB_BUFFER;
    vd->rb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vd->rb.memory = V4L2_MEMORY_MMAP;
    
    ret = ioctl (vd->fd, VIDIOC_REQBUFS, &vd->rb);
    if (ret < 0) {
        fprintf (stderr, "Unable to allocate buffers: %d.\n", errno);
        goto fatal;
    }
    /* map the buffers */
    for (i = 0; i < NB_BUFFER; i++) {
        memset (&vd->buf, 0, sizeof (struct v4l2_buffer));
        vd->buf.index = i;
        vd->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        vd->buf.memory = V4L2_MEMORY_MMAP;
        ret = ioctl (vd->fd, VIDIOC_QUERYBUF, &vd->buf);
        if (ret < 0) {
            fprintf (stderr, "Unable to query buffer (%d).\n", errno);
            goto fatal;
        }
        if (debug)
            fprintf (stderr, "length: %u offset: %u\n", vd->buf.length,
                     vd->buf.m.offset);
        vd->mem[i] = mmap (0 /* start anywhere */ , vd->buf.length, PROT_READ, MAP_SHARED, vd->fd,
                           vd->buf.m.offset);
        if (vd->mem[i] == MAP_FAILED) {
            fprintf (stderr, "Unable to map buffer (%d)\n", errno);
            goto fatal;
        }
        if (debug)
            fprintf (stderr, "Buffer mapped at address %p.\n", vd->mem[i]);
    }
    /* Queue the buffers. */
    for (i = 0; i < NB_BUFFER; ++i) {
        memset (&vd->buf, 0, sizeof (struct v4l2_buffer));
        vd->buf.index = i;
        vd->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        vd->buf.memory = V4L2_MEMORY_MMAP;
        ret = ioctl (vd->fd, VIDIOC_QBUF, &vd->buf);
        if (ret < 0) {
            fprintf (stderr, "Unable to queue buffer (%d).\n", errno);
            goto fatal;;
        }
    }
    return 0;
    
fatal:
    return -1;
}

int CameraManager2::video_enable(struct vdIn *vd) {
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int ret;
    std::cout << "Hej5" << std::endl;

    ret = ioctl (vd->fd, VIDIOC_STREAMON, &type);
    if (ret < 0) {
        fprintf (stderr, "Unable to %s capture: %d.\n", "start", errno);
        return ret;
    }
    std::cout << "Hej6" << std::endl;

    vd->isstreaming = 1;
    return 0;
}

int CameraManager2::video_disable(struct vdIn *vd) {
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int ret;
    
    ret = ioctl (vd->fd, VIDIOC_STREAMOFF, &type);
    if (ret < 0) {
        fprintf (stderr, "Unable to %s capture: %d.\n", "stop", errno);
        return ret;
    }
    vd->isstreaming = 0;
    return 0;

}

int CameraManager2::uvcGrab(struct vdIn *vd) {
    int ret;
    
    
    if (vd->isstreaming==0)
        std::cout << "Hej4" << std::endl;
        if (video_enable (vd))
            goto err;
    
    std::cout << vd->isstreaming << std::endl;
    std::cout << "Hej7" << std::endl;

    memset (&vd->buf, 0, sizeof (struct v4l2_buffer));
    vd->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    vd->buf.memory = V4L2_MEMORY_MMAP;
    
    std::cout << "Hej8" << std::endl;
    
    ret = ioctl (vd->fd, VIDIOC_DQBUF, &vd->buf);
    if (ret < 0) {
        fprintf (stderr, "Unable to dequeue buffer (%d).\n", errno);
        goto err;
    }
    
    std::cout << "Hej9" << std::endl;
    
    switch (vd->formatIn) {
        case V4L2_PIX_FMT_MJPEG:
            
            memcpy (vd->tmpbuffer, vd->mem[vd->buf.index], HEADERFRAME1);
            memcpy (vd->tmpbuffer + HEADERFRAME1, dht_data, DHT_SIZE);
            memcpy (vd->tmpbuffer + HEADERFRAME1 + DHT_SIZE,
                    vd->mem[vd->buf.index] + HEADERFRAME1,
                    (vd->buf.bytesused - HEADERFRAME1));
            if (debug)
                fprintf (stderr, "bytes in used %d \n", vd->buf.bytesused);
            break;
        case V4L2_PIX_FMT_YUYV:
            if (vd->buf.bytesused > vd->framesizeIn)
                memcpy (vd->framebuffer, vd->mem[vd->buf.index],
                        (size_t) vd->framesizeIn);
            else
                memcpy (vd->framebuffer, vd->mem[vd->buf.index],
                        (size_t) vd->buf.bytesused);
            break;
        default:
            goto err;
            break;
    }
    
    std::cout << "Hej10" << std::endl;
    
    ret = ioctl (vd->fd, VIDIOC_QBUF, &vd->buf);
    if (ret < 0) {
        fprintf (stderr, "Unable to requeue buffer (%d).\n", errno);
        goto err;
    }
    
    return 0;
err:
    vd->signalquit = 0;
    return -1;

}

int CameraManager2::save_jpg() {
    
}

int CameraManager2::close_v4l2(struct vdIn *vd) {
    int i;
    
    if (vd->isstreaming)
        video_disable (vd);
    
    /* If the memory maps are not released the device will remain opened even
     after a call to close(); */
    for (i = 0; i < NB_BUFFER; i++) {
        munmap (vd->mem[i], vd->buf.length);
    }
    
    if (vd->tmpbuffer)
        free (vd->tmpbuffer);
    vd->tmpbuffer = NULL;
    free (vd->framebuffer);
    vd->framebuffer = NULL;
    free (vd->videodevice);
    free (vd->status);
    free (vd->pictName);
    vd->videodevice = NULL;
    vd->status = NULL;
    vd->pictName = NULL;
    close (vd->fd);
    return 0;
}


