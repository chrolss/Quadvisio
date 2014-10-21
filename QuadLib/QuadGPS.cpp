#include "QuadGPS.h"
#include <termios.h>



QuadGPS::QuadGPS(){
	initialize();
}

void QuadGPS::initialize(){
	int c;
	struct termios oldtio,newtio;

	this->fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY );
	if (fd <0) {perror(MODEMDEVICE); exit(-1); }

	tcgetattr(fd,&oldtio); /* save current port settings */

	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;

	/* set input mode (non-canonical, no echo,...) */
	newtio.c_lflag = 0;

	newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
	newtio.c_cc[VMIN]     = 0;   /* blocking read until 5 chars received */

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);
}

void QuadGPS::checkFix(){}

void QuadGPS::readGPSData(){
	int res, pes;
	char buf[255];
	char pre[255];
	while(true){
		pes = read(fd, pre, 6);
		pre[pes] = 0;
		printf("%s %d\n",pre,pes);
		if (pes == '$GPGGA'){
			res = read(fd, buf, 255);
			buf[res] = 0;
			printf(":%s:%d\n", buf, res);

			if (res < 0)
			{
				std::cout << "Error reading: " << strerror(errno) << std::endl;
			}
			else if (res == 0)
			{
				std::cout << "Read nothing!" << std::endl;
			}
			else
			{
				std::cout << "Message read!" << std::endl;
			}
			exit(1);
		}
	}
}

void QuadGPS::getGPSPosition(double *position){
	position[0] = longitude[0];
	position[1] = longitude[1];
	position[2] = longitude[2];
	position[3] = latitude[0];
	position[4] = latitude[1];
	position[5] = latitude[2];
	position[6] = altitude;

}



