#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <cstdio>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#include <inttypes.h>

#include "QuadCore.h"

QuadCore::QuadCore() {
    this->setSlotsPath();
    loadDeviceTree("am33xx_pwm");
    this->am33Loaded = true;
}

int QuadCore::loadDeviceTree(std::string pwmName) {
    
    std::string file = this->slotsPath;
    std::ofstream slotsFile;
    if (am33Loaded) {
        std::string file = this->slotsPath;
        this->dtboName = "bone_pwm_" + pwmName;
        slotsFile << this->dtboName;
		slotsFile.close();
        std::ofstream slotsFile;

    }
    else {
        slotsFile.open(file.c_str(),std::ios::out);
        slotsFile << pwmName;
        slotsFile.close();
    }
	
    return 0;
}

void QuadCore::setSlotsPath() {
    this->slotsPath = "/sys/devices/bone_capemgr.9/slots";
}