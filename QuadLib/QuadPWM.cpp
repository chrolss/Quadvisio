#include <iostream>

#include "QuadPWM.h"

QuadPWM::QuadPWM() {
    // Lägg till funktion som lägger till am33xx_pwm i slots;
}

void QuadPWM::intitialize(std::string pwmName) {
    pwmNames.at(0) = pwmName;
    
    printf("PWM name: %s\n", pwmNames.at(0).c_str());
    
    loadDeviceTree(pwmNames.at(0));
}

void QuadPWM::checkLoaded(std::string pwmName) {
    printf("Inside checkLoades");
    deviceTreeLoaded(pwmName);
}

void QuadPWM::cleanUp() {

}

void QuadPWM::setPolarity(std::string pwmNAme, int polarity) {
    
}
