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
    //this->setSlotsPath();
    loadDeviceTree("am33xx_pwm");
}

int QuadCore::loadDeviceTree(std::string nameTree) {
    const char *name = nameTree.c_str();
    FILE *file = NULL;
    char slots[40];
    char line[256];
    
    buildPath("/sys/devices", "bone_capemgr", ctrl_dir, sizeof(ctrl_dir));
    snprintf(slots, sizeof(slots), "%s/slots", ctrl_dir);
    
    file = fopen(slots, "r+");
    
    while (fgets(line, sizeof(line), file)) {
        //the device is already loaded, return 1
        if (strstr(line, name)) {
            fclose(file);
            return 1;
        }
    }
    
    //if the device isn't already loaded, load it, and return
    fprintf(file, name);
    fclose(file);
    
    //0.2 second delay
    sleep(1);
    return 1;
}

int QuadCore::unloadDeviceTree(std::string nameTree) {
    const char *name = nameTree.c_str();
    FILE *file = NULL;
    char slots[40];
    char line[256];
    char *slot_line;
    
    buildPath("/sys/devices", "bone_capemgr", ctrl_dir, sizeof(ctrl_dir));
    snprintf(slots, sizeof(slots), "%s/slots", ctrl_dir);
    
    file = fopen(slots, "r+");
    
    while (fgets(line, sizeof(line), file)) {
        //the device is loaded, let's unload it
        if (strstr(line, name)) {
            slot_line = strtok(line, ":");
            //remove leading spaces
            while(*slot_line == ' ')
                slot_line++;
            
            fprintf(file, "-%s", slot_line);
            fclose(file);
            return 1;
        }
    }
    
    //not loaded, close file
    fclose(file);
    
    return 1;

}

int buildPath(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len)
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
