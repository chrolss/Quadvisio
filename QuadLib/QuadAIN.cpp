#include "QuadAIN.h"

QuadAIN::QuadAIN(){}

void QuadAIN::readAnalog(int _port){
	snprintf(buf, sizeof(buf), path "/AIN%d", _port);
	fd = open(buf, O_RDONLY);
	if (fd < 0){
		printf("Error reading the analog input\n");
		exit(1);
	}

	read(fd, &ch, 1);

	std::cout << "Value: " << ch << std::endl;
}
