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
    
    if(camManager.initializeCamera()<0) {
        printf("Error");
    }
    
    camManager.getImageBuffer();
    camManager.closeCamera();
    
    return 0;
}