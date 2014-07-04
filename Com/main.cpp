//
//  main.cpp
//  Communicate
//
//  Created by Toni Axelsson on 2014-05-15.
//  Copyright (c) 2014 Toni Axelsson. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include "Com.h"

int main(int argc, const char * argv[])
{
    std::string input = "";
    Com C;
    sleep(1);
    while (true) {
        if (C.connected) {
            std::cout << "Enter what you want to send (A for closing the client)" << std::endl;
            getline(std::cin, input);
            if (input == "A") {
                break;
            }
            else {
                C.sendMsg(input, input.length());
            }
        }
    }
    C.closeClient();
    return 0;
}

