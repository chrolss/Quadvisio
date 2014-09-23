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
    this->setOcpPath();
    loadDeviceTree("am33xx_pwm");
}

int QuadCore::loadDeviceTree(const char *name) {
    //printf("Inside loadDeviceTree\n");
    
    //const char *name = pwmName.c_str();
    
    FILE *file = NULL;
    char line[256];
    
    const char *slots = slotsPath.c_str();
    
    //printf("Path to slots file: %s\n", slots);
    
    file = fopen(slots, "r+");
    if (!file) {
        printf("Error trying to open slots\n");
        return -1;
    }
    
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, name)) {
            printf("%s is already loaded\n", name);
            fclose(file);
            return 1;
        }
    }
    
    fprintf(file, name);
    fclose(file);
    
    return 0;
}

int QuadCore::unloadDeviceTree(std::string pwmName) {
    
    return 0;
}

bool QuadCore::deviceTreeLoaded(std::string pwmName) {
    //printf("Inside deviceTreeLoaded\n");
    const char *name = pwmName.c_str();
    
    FILE *file = NULL;
    char line[256];
    
    const char *slots = slotsPath.c_str();
    
    file = fopen(slots, "r+");
    if (!file) {
        printf("Error trying to open slots");
        return false;
    }
    
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, name)) {
            printf("%s is already loaded\n", name);
            fclose(file);
            return true;
        }
    }
    return false;
}

int QuadCore::buildPath(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len)
{
    DIR *dp;
    struct dirent *ep;
    
    dp = opendir (partial_path);
    if (dp != NULL) {
        while ((ep = readdir (dp))) {
            // Enforce that the prefix must be the first part of the file
            char* found_string = strstr(ep->d_name, prefix);
            
            if (found_string != NULL && (ep->d_name - found_string) == 0) {
                snprintf(full_path, full_path_len, "%s/%s", partial_path, ep->d_name);
                (void) closedir (dp);
                return 1;
            }
        }
        (void) closedir (dp);
    } else {
        return 0;
    }
    
    return 0;
}

void QuadCore::setSlotsPath() {
    this->slotsPath = "/sys/devices/bone_capemgr.9/slots";
}

void QuadCore::setOcpPath() {
    this->ocpPath = "/sys/devices/ocp.3";
}

std::string QuadCore::getOcpPath() {
    return this->ocpPath;
}
