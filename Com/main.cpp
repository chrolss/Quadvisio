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
            else if (input == "test") {
                for (int i=0; i<100; i++) {
                    std::ostringstream ostr;
                    std::string s = " 0.435 0.7065 0.35 50.304 4000.00";
                    ostr << std::to_string(i) << s;
                    s = ostr.str();
                    C.sendMsg(s, s.length());
                    usleep(300000);
                }
            }
            else {
                C.sendMsg(input, input.length());
            }
        }
    }
    C.closeClient();
    return 0;
}

