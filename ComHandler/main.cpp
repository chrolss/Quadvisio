//
//  main.cpp
//  ComHandler
//
//  Created by Toni Axelsson on 2014-09-25.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include "ComHandler.h"


int main(int argc, const char * argv[]) {
    
    // Loop time measurement
    double loopTime = 0.0;
    int Hz = 75;
    int loopSleep=0;
    
    std::cout << "Starting communication thread" << std::endl;
    ComHandler comHandler;
    comHandler.startListenThread();
    sleep(1);
    
    std::cout << "Starting main loop" << std::endl;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    while(true) {
        // Start clock
        auto start = std::chrono::high_resolution_clock::now();
        
        if (comHandler.connected) {
            if (!comHandler.reciveMsg && !comHandler.sendMsg) {
                if (comHandler.vidCount>=2) {
                    std::cout << "Hej" << std::endl;
                    comHandler.sendImage = true;
                }
                comHandler.sendMsg=true;
            }
        }
        
        comHandler.vidCount++;
        
        if (!comHandler.connected && !comHandler.listening) {
            comHandler.startListenThread();
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
    
    return 0;
}
