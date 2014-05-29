//
//  main.cpp
//  SensorsHub
//
//  Created by Toni Axelsson on 2014-05-29.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include <iostream>
#include <string>
#include "sensorHub.h"

using namespace std;

int main(int argc, const char * argv[])
{
    sensorHub test;
    test.initializeMPU();
    string s = test.getDataMPU();
    
    cout << s << endl;
    
    return 0;
}

