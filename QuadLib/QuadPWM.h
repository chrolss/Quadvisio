#ifndef QUADPWM_H_
#define QUADPWM_H_

#include "QuadCore.h"
#include <string>

class QuadPWM : protected virtual QuadCore {
    
public:
    QuadPWM();
    
    // Laddar ett device tree för porten name och gör den redo för användning
    void intitialize(std::string name);
    void cleanUp();
    
private:
    std::string pwmName;
    bool initialized;
};


#endif /* QUADPWM_H_ */
