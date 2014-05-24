//
//  main.cpp
//  Communicate
//
//  Created by Toni Axelsson on 2014-05-15.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include <iostream>
#include "communicate.h"

int main(int argc, const char * argv[])
{
    Communicate C;
    sleep(1);
    std::cout << "Do some stuff in the main thread while waiting for connections" << std::endl;
    C.closeClient();
    return 0;
}

