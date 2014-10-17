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

    CameraManager camManager;
    
    printf("Starting camera");
    if(camManager.initializeCamera()<0) {
        printf("Error");
    }
    
    
    printf("Grabbing and saving frame");
    camManager.getImageBuffer();
    
    printf("Closing camera");
    camManager.closeCamera();
    
    return 0;
}