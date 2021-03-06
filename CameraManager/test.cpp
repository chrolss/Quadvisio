//
//  main.cpp
//  CameraManager
//
//  Created by Toni Axelsson on 2014-10-16.
//  Copyright (c) 2014 Quadvisio. All rights reserved.
//

#include <iostream>
#include "CameraManager.h"

int main(int argc, const char * argv[]) {
    
    std::cout << "Hej" << std::endl;

    CameraManager camManager;
    
    std::cout << "Starting camera" << std::endl;

    if(camManager.initializeCamera(640,480)<0) {
        printf("Error");
    }
    
    
    printf("Grabbing and saving frame\n");
    camManager.grab_frame();
    
    /*
    printf("Setting resolution to 640x480\n");
    camManager.closeCamera();
    camManager.initializeCamera(640, 480);
    
    printf("Grabbing and saving frame\n");
    camManager.getImageBuffer();
    */
    
    printf("Closing camera\n");
    camManager.closeCamera();
    
    return 0;
}