#ifndef QUADCORE_H_
#define QUADCORE_H_

class QuadCore {

public:
    QuadCore();
    
protected:
    bool am33Loaded = false;
    
    // Tries to load the device three, returns true if successfull
    int loadDeviceTree(std::string nameTree);
    int unloadDeviceTree(std::string nameTree);
    
    // Returns the slot file path
    std::string getSlotsPath();
    
private:
    std::string slotsPath;
    std::string dtboName;
    
    // Generates the slot file path and sets variable slotsPath
    void setSlotsPath();
    
};

#endif /* QUADCORE_H_ */
