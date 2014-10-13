#include "QuadGPIO.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>


QuadGPIO::QuadGPIO(unsigned int gpio) {
	initialize(gpio);
}

void QuadGPIO::initialize(unsigned int _gpio){
	this->gpio = _gpio;
	char buf[MAX_BUF];
	fd = open(path "/export", O_WRONLY);

	if (fd < 0){
		printf("Error exporting GPIO port\n");
		exit(1);
	}
	len = snprintf(buf, sizeof(buf), "%d", _gpio);
	write(fd, buf, len);
	close(fd);
}

void QuadGPIO::setValue(int value){
	char buf[MAX_BUF];
	snprintf(buf, sizeof(buf), path "/gpio%d/value", gpio);
	fd = open(buf, O_WRONLY);
	if (fd < 0){
		printf("Error setting GPIO value\n");
		exit(1);
	}
	if (value == 1){
		write(fd,"1",2);
		printf("Value set to high\n");
	}
	else{
		write(fd,"0",2);
		printf("Value set to low\n");
	}
}
void QuadGPIO::setDirection(int direction){
	char buf[MAX_BUF];
	snprintf(buf, sizeof(buf), path "/gpio%d/direction", gpio);
	fd = open(buf, O_WRONLY);
	if (fd < 0){
		printf("Error setting GPIO direction\n");
		exit(1);
	}
	if (direction == 1){
		write(fd, "in", 3);
		printf("Direction set to in \n");
	}
	else{
		write(fd, "out", 4);
		printf("Direction set to out \n");
	}
}

void QuadGPIO::release(){
	char buf[MAX_BUF];

	fd = open(path "/unexport", O_WRONLY);
	if (fd < 0){
		printf("Unable to unexport\n");
		exit(1);
	}
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf ,len);
	printf("GPIO released\n");
	close(fd);
}
void setEgde(std::string GPIOName, int value){

}
void setPower(std::string GPIOName, int value){

}
