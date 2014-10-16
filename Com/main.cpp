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
    
    double output[16] = {1.45345, 2.34545, 1.0, 0.0, 0.0, 0.0, 15.0, 16.0, 17.0, 18.0, 0.0, 0.0, 0.0, 0.0, 0.0, 100.0};
    
    std::cout << "Starting communication thread" << std::endl;
    Com C;
    C.startListenThread();
    sleep(1);
    
    std::cout << "Starting main loop" << std::endl;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    while (true) {
        
        // Start clock
        auto start = std::chrono::high_resolution_clock::now();
        
        if (HzCount==20) {
            HzCount = 0;
        }
        
        if (output[2]>360.0) {
            output[2] = 0.0;
            output[0] = 0.0;
        }
        
        if (output[5]>360.0) {
            output[5] = 0.0;
            output[3] = 0.0;
        }
        
        avgHz[HzCount] = loopTime;
        
        for(int i=0;i<20;i++)
            sumHz+=avgHz[i];
        
        output[13] = sumHz/20.0;
        sumHz = 0.0;
        HzCount++;
        output[2] = output[2] + 2.0;
        output[5] = output[5] + 0.2;
        output[0] = output[2] + 2.0;
        output[3] = output[5] + 0.2;

        
        if (C.connected) {
            if (!C.reciveMsg && !C.msgSend) {
                if (C.vidCount>=2) {
                    C.imgSend = true;
                }
                C.msgSend=true;
            }
        }
        
        if (!C.connected && !C.listening) {
            C.startListenThread();
        }
        
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
    
    C.closeClient();
    return 0;
}

