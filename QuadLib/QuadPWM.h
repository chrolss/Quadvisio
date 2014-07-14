#ifndef QUADPWM_H_
#define QUADPWM_H_

#include "QuadCore.h"
#include <string>
#include <vector>

class QuadPWM : protected virtual QuadCore {
    
public:
    QuadPWM();
    
    void intitialize(std::string pwmName);
    void checkLoaded(std::string pwmName);
    void cleanUp();
    
    void setDuty(std::string pwmName, double value);
    void setPolarity(std::string pwmName, int value);
    void setPeriod(std::string pwmName, double value);
    void setRun(std::string pwmName, int value);
    
private:
    std::vector<std::string> pwmNames;
    bool initialized;
};


#endif /* QUADPWM_H_ */
