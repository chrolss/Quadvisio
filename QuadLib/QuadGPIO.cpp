#include "QuadGPIO.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define path2 "/sys/class/gpio/"

QuadGPIO::QuadGPIO() {}

void initializeGPIO(unsigned int gpio){
	int fd, len;
	char buf[MAX_BUF];
	std::string path = getGPIOPath();
	fd = open(path2 "/export", O_WRONLY);
}

void setValue(std::string GPIOName, int value){

}
void setDirection(std::string GPIOName, int value){

}
void setEgde(std::string GPIOName, int value){

}
void setPower(std::string GPIOName, int value){

}
