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
    unsigned long duty;
    unsigned long period_ns;
    std::string pwmTestPath;
    std::string periodPath;
    std::string dutyPath;
    std::string polarityPath;
};

class QuadPWM : protected QuadCore {
    
public:
    QuadPWM();
    
    void intitialize(std::string pwmName);
    void checkLoaded(std::string pwmName);
    void cleanUp();
    
    void setDuty(std::string pwmName, int value);
    void setPolarity(std::string pwmName, int value);
    void setPeriod(std::string pwmName, int value);
    void setRun(std::string pwmName, int value);
    
private:
    std::vector<struct pwmData> pwmDatas;
    bool initialized;
    void mapper();
};


#endif /* QUADPWM_H_ */
