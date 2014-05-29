//
//  tcpHandler.h
//  Qvis
//
//  Created by Toni Axelsson on 2014-05-28.
//
//

#ifndef __Qvis__tcpHandler__
#define __Qvis__tcpHandler__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#define PORT 3490

class tcpHandler
{
public:
    tcpHandler();
    void listen();
    void createTCPThread();
    static void* TCPThread_func(void *pThisArg)
    {
        tcpHandler *pThis = static_cast<tcpHandler*>(pThisArg);
        pThis->listen();
        return NULL;
    }

private:
    void error(const char *msg);
    void listenPro();
    pthread_t t;
};

#endif /* defined(__Qvis__tcpHandler__) */
