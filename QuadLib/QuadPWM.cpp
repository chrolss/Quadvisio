#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "QuadPWM.h"

QuadPWM::QuadPWM() {
    // Lägg till funktion som lägger till am33xx_pwm i slots;
}

void QuadPWM::intitialize(std::string pwmName) {
    printf("Inside initialize\n");
    
    char dtboFile[18];
    char pwmTestFragment[20];
    char pwmTestPath[45];
    char periodPath[50];
    char dutyPath[50];
    char polarityPath[55];
    struct pwmData newPwm;
    std::stringstream ss;
    
    newPwm.name = pwmName;
    
    // Get to dtbo filename
    snprintf(dtboFile, sizeof(dtboFile), "bone_pwm_%s\n", pwmName.c_str());
    
    printf("dtbo file name: %s", dtboFile);
    
    // Load the device tree for the pin
    loadDeviceTree(dtboFile);
    
    //creates the fragment in order to build the pwm_test_filename, such as "pwm_test_P9_13"
    snprintf(pwmTestFragment, sizeof(pwmTestFragment), "pwm_test_%s", pwmName.c_str());
    
    //finds and builds the pwm_test_path, as it can be variable...
    buildPath(getOcpPath().c_str(), pwmTestFragment, pwmTestPath, sizeof(pwmTestPath));
    
    printf("Path to ocp: %s\n", pwmTestPath);
    
    snprintf(periodPath, sizeof(periodPath), "%s/period", pwmTestPath);
    snprintf(dutyPath, sizeof(dutyPath), "%s/duty", pwmTestPath);
    snprintf(polarityPath, sizeof(polarityPath), "%s/polarity", pwmTestPath);
    
    
    ss << periodPath;
    ss >> newPwm.periodPath;
    ss.clear();
    ss << dutyPath;
    ss >> newPwm.dutyPath;
    ss.clear();
    ss << polarityPath;
    ss >> newPwm.polarityPath;
    pwmDatas.push_back(newPwm);
    
    printf("period path %s\n", newPwm.periodPath.c_str());
    printf("duty path %s\n", newPwm.dutyPath.c_str());
    printf("polarity path %s\n", newPwm.polarityPath.c_str());

    sleep(1);
    
    setPolarity(newPwm.name, 0);
    
    sleep(1);
    
    /////////////////////////////////////////
    //          FORTSÄTT HÄR IDAG          //
    /////////////////////////////////////////
 
}

void QuadPWM::checkLoaded(std::string pwmName) {
    printf("Inside checkLoades");
    deviceTreeLoaded(pwmName);
}

void QuadPWM::cleanUp() {

}

void QuadPWM::setPolarity(std::string pwmName, int polarity) {
    for (int pwm = 0; pwm<sizeof(pwmDatas); pwm++) {
        if (pwmName.compare(pwmDatas.at(pwm).name)==0) {
            int fd;
            int len;
            char buffer[7]; /* allow room for trailing NUL byte */
            fd = open(pwmDatas.at(pwm).polarityPath.c_str(), O_RDWR);
            len = snprintf(buffer, sizeof(buffer), "%d", polarity);
            write(fd, buffer, len);
        }
    }
}
