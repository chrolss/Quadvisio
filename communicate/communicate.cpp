#include<iostream>
#include "communicate.h"

Communicate::Communicate()
{
    std::cout << "test" << std::endl;
    std::thread t1(&Communicate::Listen, this);
    t1.join();
}

void Communicate::Listen()
{
    std::cout << "Detta kommer från en tråd" << std::endl;
}