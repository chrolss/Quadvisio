#ifndef QUADCORE_H_
#define QUADCORE_H_

class QuadCore {

public:
    QuadCore();
    
protected:
    
    // Tries to load the device three, returns 0 if successfull
    int loadDeviceTree(const char *name);
    
    // Tries to unload the device three, returns 0 if successfull
    int unloadDeviceTree(std::string pwmName);
    
    // Checks if a certain device tree is loaded, returns true if so
    bool deviceTreeLoaded(std::string pwmName);
    
    int buildPath(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len);
    
    // Returns the slot file path
    std::string getSlotsPath();
    
    // Returns the ocp file path
    std::string getOcpPath();
    
    // Returns the gpio file path
    std::string getGPIOPath();

private:
    
    // Holds the path to slots
    std::string slotsPath;
    
    // Holds the name of a dtbo file
    std::string dtboName;
    
    // Holds the path to ocp.3 directory
    std::string ocpPath;
    
    // Hold the path to GPIO directory
    std::string gpioPath;

    // Generates the slot file path and sets variable slotsPath
    void setSlotsPath();
    
    // Generates the ocp file path and sets variable ocpPath
    void setOcpPath();
    
    void setGPIOPath();

};

#endif /* QUADCORE_H_ */
