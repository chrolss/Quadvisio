#include "QuadGPIO.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


QuadGPIO::QuadGPIO(unsigned int gpio) {
	initialize(gpio);
}

void QuadGPIO::initialize(unsigned int gpio){
	char buf[MAX_BUF];
	fd = open(path "/export", O_WRONLY);

	if (fd < 0){
		printf("Error exporting GPIO port\n");
	}
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);
	close(fd);
}

void QuadGPIO::setValue(int value){
	char buf[MAX_BUF];
	snprintf(buf, sizeof(buf), path "gpio%d/value", gpio);
	fd = open(buf, O_WRONLY);
	if (fd < 0){
		printf("Error setting GPIO value\n");
	}
	if (value == 1){
		write(fd,"1",2);
	}
	else{
		write(fd,"0",2);
	}
}
void QuadGPIO::setDirection(int direction){
	char buf[MAX_BUF];
	snprintf(buf, sizeof(buf), path "gpio%d/direction", gpio);
	fd = open(buf, O_WRONLY);
	if (fd < 0){
		printf("Error setting GPIO direction\n");
	}
	if (direction == 1){
		write(fd, "in",2);
	}
	else{
		write(fd, "out", 2);
	}
}

void QuadGPIO::release(){
	char buf[MAX_BUF];

	fd = open(path "/unexport", O_WRONLY);
	if (fd < 0){
		printf("Unable to unexport\n");
	}
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf ,len);
	close(fd);
}
void setEgde(std::string GPIOName, int value){

}
void setPower(std::string GPIOName, int value){

}
