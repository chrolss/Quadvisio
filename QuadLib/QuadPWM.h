#ifndef QUADPWM_H_
#define QUADPWM_H_

#include "QuadCore.h"
#include <string>
#include <vector>

#define KEYLEN 7

struct pwmData
{
    std::string name;
    char key[KEYLEN+1]; /* leave room for terminating NUL byte */
    int period_fd;
    int duty_fd;
    int polarity_fd;
    unsigned long duty;
    unsigned long period_ns;
};

class QuadPWM : protected QuadCore {
    
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
    bool initialized;
    void mapper();
};


#endif /* QUADPWM_H_ */
