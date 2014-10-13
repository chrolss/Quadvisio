#ifndef QUADGPIO_H_
#define QUADGPIO_H_

#include "QuadCore.h"
#include <string>
#include <vector>

#define KEYLEN 7

// Struct for holding data about a pwm port
struct GPIOData
{
    std::string name;
    //char key[KEYLEN+1]; /* leave room for terminating NUL byte */

    std::string GPIOTestPath;
    std::string DirectionPath;
    std::string ValuePath;
    std::string EdgePath;
};

class QuadGPIO : protected QuadCore {

public:
    QuadGPIO();

    void initialize(std::string GPIOName);
    void checkLoaded(std::string GPIOName);
    void cleanUp();

    void setValue(std::string GPIOName, int value);
    void setDirection(std::string GPIOName, int value);
    void setEgde(std::string GPIOName, int value);
    void setPower(std::string GPIOName, int value);

private:
    std::vector<struct GPIOData> GPIODatas;
    bool initialized;
};


#endif /* QUADPWM_H_ */
