#ifndef QUADCORE_H_
#define QUADCORE_H_

class QuadCore {

public:
    QuadCore();
    
protected:
    
    // Tries to load the device three, returns true if successfull
    bool loadDeviceTree(std::string name);
    
    // Returns the slot file path
    std::string getSlotsPath();
    
    
private:
    std::string slotsPath;
    std::string dtboName;
    // Generates the slot file path and sets variable slotsPath
    void setSlotsPath();
    bool loadAm33xx();

    
};

#endif /* QUADCORE_H_ */
