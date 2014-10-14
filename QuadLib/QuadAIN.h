#ifndef QUADAIN_H_
#define QUADAIN_H_

#include "QuadCore.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>

#define KEYLEN 7
#define MAX_BUF 64
#define AINpath "/sys/devices/ocp.3/helper.15"

class QuadAIN : protected QuadCore {

public:
    QuadAIN();

    void readAnalog(int _port);
    int getValue(){return value;}

private:
    int fd;
    int value;
    char buf[MAX_BUF];
    char ch[4];
};


#endif /* QUADAIN_H_ */
