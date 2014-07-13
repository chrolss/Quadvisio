#ifndef QUADCORE_H_
#define QUADCORE_H_

class QuadCore {

public:
    QuadCore();
    
protected:
    
    // Tries to load the device three, returns true if successfull
    int loadDeviceTree(std::string nameTree);
    int unloadDeviceTree(std::string nameTree);
    
    // Returns the slot file path
    std::string getSlotsPath();
    
private:
    std::string slotsPath;
    std::string dtboName;
    char ctrl_dir[35];
    
    // Generates the slot file path and sets variable slotsPath
    void setSlotsPath();
    
    int buildPath(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len);

    
};

#endif /* QUADCORE_H_ */
