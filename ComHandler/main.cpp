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
    // Loop time measurement
    double loopTime;
    int Hz = 60;
    int loopSleep=0;
    
    double output[8] = {1.45345, 2.34545, 3.345, 320.0, 240.0};
    std::cout << "Starting communication thread" << std::endl;
    Com C;
    C.startListenThread();
    sleep(1);
    
    std::cout << "Starting main loop" << std::endl;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    while (true) {
        
        // Start clock
        auto start = std::chrono::high_resolution_clock::now();
        
        if (C.connected) {
            if (!C.reciveMsg && !C.msgSend) {
                printf("Setting output and send to true\n");
                C.setOutputData(output);
                if (C.vidCount>100) {
                    C.imgSend = true;
                }
                C.msgSend=true;
            }
        }
        
        if (!C.connected && !C.listening) {
            C.startListenThread();
        }
        C.vidCount++;
        
        // Measure duration
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        
        loopSleep = 1000000/Hz - (int)duration;
        
        
        // Sleep
        if (loopSleep>0) {
            usleep(loopSleep);
        }
        
        // Measure duration again and print out the frequency
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        
        loopTime = double(1000000)/(duration2);
        std::cout << "Running at: " << loopTime << "Hz" << std::endl;
    }
    
    C.closeClient();
    return 0;
}

