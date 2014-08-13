//
//  main.cpp
//  Communicate
//
//  Created by Toni Axelsson on 2014-05-15.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Com.h"

int main(int argc, const char * argv[])
{
    double output[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    int count = 0;
    std::cout << "Starting communication thread" << std::endl;
    Com C;
    sleep(1);
    
    std::cout << "Starting main loop" << std::endl;
    while (true) {
        
        if (C.connected && !C.reciveMsg) {
            C.setOutputData(output);
            if (count>=int(((double(5.0/C.imgSendRate))-1)*10) && C.videoStream) {
                C.imgSend = true;
                count=0;
            }
            C.msgSend=true;
        }
    count++;
    }
    C.closeClient();
    return 0;
}

