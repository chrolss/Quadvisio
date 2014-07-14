#include <iostream>

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
    int period_fd, duty_fd, polarity_fd;
    struct pwmData *newPwm;
    
    newPwm = new pwmData;
    
    // Get to dtbo filename
    snprintf(dtboFile, sizeof(dtboFile), "bone_pwm_%s\n", pwmName.c_str());
    
    printf("dtbo file name: %s", dtboFile);
    
    // Load the device tree for the pin
    loadDeviceTree(dtboFile);
    
    //creates the fragment in order to build the pwm_test_filename, such as "pwm_test_P9_13"
    snprintf(pwmTestFragment, sizeof(pwmTestFragment), "pwm_test_%s", pwmName.c_str());
    
    printf("Path to ocp: %s\n", pwmTestFragment);
    
    //finds and builds the pwm_test_path, as it can be variable...
    buildPath(getOcpPath().c_str(), pwmTestFragment, pwmTestPath, sizeof(pwmTestPath));
    
    printf("Path to ocp: %s\n", pwmTestPath);

}

void QuadPWM::checkLoaded(std::string pwmName) {
    printf("Inside checkLoades");
    deviceTreeLoaded(pwmName);
}

void QuadPWM::cleanUp() {

}

void QuadPWM::setPolarity(std::string pwmName, int polarity) {
    
}
