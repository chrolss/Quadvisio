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
}

int QuadCore::loadDeviceTree(std::string nameTree) {
    
    std::string file = this->slotsPath;
    std::ofstream slotsFile;
    
	slotsFile.open(file.c_str(),std::ios::out);
    slotsFile << nameTree;
    slotsFile.close();
    return 0;
}

void QuadCore::setSlotsPath() {
    this->slotsPath = "/sys/devices/bone_capemgr.9/slots";
}