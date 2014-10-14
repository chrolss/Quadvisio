#ifndef QUADGPIO_H_
#define QUADGPIO_H_

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
#define path "/sys/devices/ocp.3/helper.15"

class QuadAIN : protected QuadCore {

public:
    QuadAIN();

    void readAnalog(int _port);

private:
    bool initialized;
    int fd;
    char buf[MAX_BUF];
    char ch;
    unsigned int gpio;
};


#endif /* QUADPWM_H_ */
