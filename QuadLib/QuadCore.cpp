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
    if (!this->deviceTreeLoaded("am33xx_pwm")) {
        loadDeviceTree("am33xx_pwm");
        this->am33Loaded = true;
    }
}

int QuadCore::loadDeviceTree(std::string pwmName) {
    
    const char *name = pwmName.c_str();
    
    FILE *file = NULL;
    char line[256];
    
    const char *slots = slotsPath.c_str();
    
    printf("Slots path is: %s\n", slots);
    
    file = fopen(slots, "r+");
    if (!file) {
        printf("Error trying to open slots");
        return -1;
    }
    
    while (fgets(line, sizeof(line), file)) {
        //the device is already loaded, return 1
        if (strstr(line, name)) {
            printf("%s is already loaded\n", name);
            fclose(file);
            return 0;
        }
    }
    
    //if the device isn't already loaded, load it, and return
    fprintf(file, name);
    fclose(file);
    
    return 0;
}

int QuadCore::unloadDeviceTree(std::string pwmName) {
    
    return 0;
}

bool QuadCore::deviceTreeLoaded(std::string pwmName) {
    const char *name = pwmName.c_str();
    
    FILE *file = NULL;
    char line[256];
    
    const char *slots = slotsPath.c_str();
    
    printf("Slots path is: %s\n", slots);
    
    file = fopen(slots, "r+");
    if (!file) {
        printf("Error trying to open slots");
        return false;
    }
    
    while (fgets(line, sizeof(line), file)) {
        //the device is already loaded, return 1
        if (strstr(line, name)) {
            fclose(file);
            return true;
        }
    }

    return false;
}

void QuadCore::setSlotsPath() {
    this->slotsPath = "/sys/devices/bone_capemgr.9/slots";
}