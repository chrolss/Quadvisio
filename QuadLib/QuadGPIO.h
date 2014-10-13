#ifndef QUADGPIO_H_
#define QUADGPIO_H_

#include "QuadCore.h"
#include <string>
#include <vector>

#define KEYLEN 7
#define MAX_BUF 64
#define path "sys/class/gpio"

// Struct for holding data about a GPIO port
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
    QuadGPIO(unsigned int gpio);

    void initialize(unsigned int GPIOName);
    void checkLoaded(std::string GPIOName);
    void release();

    void setValue(int value);
    void setDirection(int direction);
    void setEgde(std::string GPIOName, int value);
    void setPower(std::string GPIOName, int value);

private:
    std::vector<struct GPIOData> GPIODatas;
    bool initialized;
    int fd;
    int len;
    unsigned int gpio;
};


#endif /* QUADPWM_H_ */
