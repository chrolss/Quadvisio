//
//  main.cpp
//  Frequency Program
//
//  Created by Toni Axelsson on 2014-07-21.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <chrono>
#include <string>

int main(int argc, const char * argv[])
{
    double time;
    int Hz = 2;
    int sleep;
    std::string s = "020:1:4:1.0:1.0:1.0:1.0:1.0:1.0:1.0:1.0:1.0";
    std::string delimiter = ":";
    size_t pos = 0;
    std::string token;
    std::string stringList[12];
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    
    while (true) {
        auto start = std::chrono::high_resolution_clock::now();
        
        //////////////////
        // Do some work //
        //////////////////
        
        int i=0;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            std::cout << token << std::endl;
            s.erase(0, pos + delimiter.length());
            stringList[i] = token;
            i++;
        }
        stringList[11] = s;
        
        int thrust = atoi(stringList[0].c_str());
        double pRoll = atof(stringList[3].c_str());
        
        printf("thrust: %i param: %f\n",thrust, pRoll);
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        
        std::cout << duration << std::endl;

        sleep = 1000000/Hz - (int)duration;
        usleep(sleep);
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
        time = double(1000000)/(duration2);
        std::cout << "Running at: " << time << "Hz" << std::endl;

    }
    return 0;
}

