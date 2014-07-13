#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <cstdio>
#include <dirent.h>
#include <inttypes.h>

#include "QuadCore.h"

QuadCore::QuadCore() {
    this->setSlotsPath();
    loadAm33xx();
}

bool QuadCore::loadAm33xx() {
    std::string file = this->getSlotsPath();
    std::ofstream slotsFile;
    slotsFile.open(file.c_str(),std::ios::out);
    slotsFile << "am33xx_pwm";
    slotsFile.close();
    return true;
}

bool QuadCore::loadDeviceTree(std::string name) {
    std::string file = this->getSlotsPath();
    this->dtboName = "bone_pwm_" + name;
    std::ofstream slotsFile;
    slotsFile.open(file.c_str(),std::ios::out);
    slotsFile << dtboName;
    slotsFile.close();
    return true;
}

void QuadCore::setSlotsPath() {
    this->slotsPath = "/sys/devices/bone_capemgr.9/slots";
}

std::string QuadCore::getSlotsPath() {
    return this->slotsPath;
}
