#ifndef QUADCORE_H_
#define QUADCORE_H_

class QuadCore {

public:
    QuadCore();
    
protected:
    
    // Is am33xx_pwm loaded or not
    bool am33Loaded = false;
    
    // Tries to load the device three, returns 0 if successfull
    int loadDeviceTree(std::string pwmName);
    
    // Tries to unload the device three, returns 0 if successfull
    int unloadDeviceTree(std::string pwmName);
    
    // Checks if a certain device tree is loaded, returns true if so
    bool deviceTreeLoaded(std::string pwmName);
    
    // Returns the slot file path
    std::string getSlotsPath();
    
private:
    
    // Holds the path to slots
    std::string slotsPath;
    
    // Holds the name of a dtbo file
    std::string dtboName;
    
    // Generates the slot file path and sets variable slotsPath
    void setSlotsPath();
    
};

#endif /* QUADCORE_H_ */
