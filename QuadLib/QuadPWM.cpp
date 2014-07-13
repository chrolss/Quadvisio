#include <iostream>

#include "QuadPWM.h"

QuadPWM::QuadPWM() {
    // Lägg till funktion som lägger till am33xx_pwm i slots;
}

void QuadPWM::intitialize(std::string name) {
    this->pwmName = name;
    
    loadDeviceTree(pwmName);
}

void QuadPWM::cleanUp() {
    unloadDeviceTree("am33xx_pwm");
}
