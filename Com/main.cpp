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
#include "Com.h"

int main(int argc, const char * argv[])
{
    // Loop time measurement
    double loopTime = 0.0;
    int Hz = 75;
    int loopSleep=0;
    double avgHz[20] = {0.0};
    int HzCount = 0;
    double sumHz = 0.0;
    
    // angles:refangles:pwm:speed:sidespeed:altitude:Hz:errorMessage:imgWidth:imgHeight:imgSize:imgChannels - Image
    
    
    std::cout << "Starting communication thread" << std::endl;
    Com com;
    com.startListenThread();
    sleep(1);
    
    std::cout << "Starting main loop" << std::endl;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    while (true) {
        
        // Start clock
        auto start = std::chrono::high_resolution_clock::now();
        
        if (com.connected) {
            if (!com.reciveMsg && !com.msgSend) {
                if (com.vidCount>=2) {
                    com.imgSend = true;
                }
                com.msgSend=true;
            }
        }
        
        if (!com.connected && !com.listening) {
            com.startListenThread();
        }
        
        com.vidCount++;
        
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
        //std::cout << "Running at: " << loopTime << "Hz" << std::endl;
    }
    
    com.closeClient();
    return 0;
}

