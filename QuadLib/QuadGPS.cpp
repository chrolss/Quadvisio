#include "QuadGPS.h"
#include <termios.h>



QuadGPS::QuadGPS(){
	initialize();
}

void QuadGPS::initialize(){
	this->fd = open("/dev/ttyO2", O_RDONLY);
	struct termios tty;
	struct termios tty_old;
	memset (&tty, 0, sizeof tty);

	/* Error Handling */
	if ( tcgetattr ( fd, &tty ) != 0 )
	{
	std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
	}

	/* Save old tty parameters */
	tty_old = tty;

	/* Set Baud Rate */
	cfsetospeed (&tty, (speed_t)B9600);
	cfsetispeed (&tty, (speed_t)B9600);

	/* Setting other Port Stuff */
	tty.c_cflag     &=  ~PARENB;        // Make 8n1
	tty.c_cflag     &=  ~CSTOPB;
	tty.c_cflag     &=  ~CSIZE;
	tty.c_cflag     |=  CS8;

	tty.c_cflag     &=  ~CRTSCTS;       // no flow control
	tty.c_cc[VMIN]      =   1;                  // read doesn't block
	tty.c_cc[VTIME]     =   5;                  // 0.5 seconds read timeout
	tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	tcflush( fd, TCIFLUSH );
	if ( tcsetattr ( fd, TCSANOW, &tty ) != 0)
	{
	std::cout << "Error " << errno << " from tcsetattr" << std::endl;
	}
}

void QuadGPS::checkFix(){}

void QuadGPS::readGPSData(){
	int n = 0;
	char buf = '\0';

	/* Whole response*/
	std::string response;

	do
	{
	   n = read( fd, &buf, 1 );
	   response.append( &buf );
	   printf("%c", buf);
	}
	while( buf != '\r' && n > 0);
	printf("\n");
	do
		{
		   n = read( fd, &buf, 1 );
		   response.append(&buf);
		   printf("%c", buf);
		}
		while( buf != '\r' && n > 0);
	if (n < 0)
	{
	   std::cout << "Error reading: " << strerror(errno) << std::endl;
	}
	   else if (n == 0)
	{
	    std::cout << "Read nothing!" << std::endl;
	}
	else
	{
	    std::cout << "Response: " << response << std::endl;
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



