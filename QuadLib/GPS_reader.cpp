/* GPS Reading C++ Program
 * Created for testing out Linux Serial API Termios
 *
 * Crashes terminal - need to first tcgetattr and save the settings, then reapply when exiting
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <string.h> // needed for memset

std::string extractor(std::string stringy){
	std::string str = "GPGSA";
	std::string str2 = "Here is GPGSA";
	std::size_t found = stringy.find(str);	// look for keyword in string
	std::size_t found2 = str2.find(str);
	if (found2!=std::string::npos)
		printf("det gick\n");
	if (found!=std::string::npos){
		printf("Hej \n");
		return "";
	}
	else{
		printf("not found\n");
		return "";
	}
}

int main(int argc,char** argv)
{
        struct termios tio;
        struct termios stdio;
        struct termios old_stdio;
        int tty_fd;
        fd_set rdset;

        unsigned char c='D';
        tcgetattr(STDOUT_FILENO,&old_stdio);
        printf("Please start with %s /dev/ttyS1 (for example)\n",argv[0]);
        memset(&stdio,0,sizeof(stdio));
        stdio.c_iflag=0;
        stdio.c_oflag=0;
        stdio.c_cflag=0;
        stdio.c_lflag=0;
        stdio.c_cc[VMIN]=1;
        stdio.c_cc[VTIME]=0;
        tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);
        tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);       // make the reads non-blocking

        memset(&tio,0,sizeof(tio));
        tio.c_iflag=0;
        tio.c_oflag=0;
        tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
        tio.c_lflag=0;
        tio.c_cc[VMIN]=1;
        tio.c_cc[VTIME]=5;

        tty_fd=open(argv[1], O_RDWR | O_NONBLOCK);
        cfsetospeed(&tio,B9600);            // 9600 baud
        cfsetispeed(&tio,B9600);            // 9600 baud
        printf("Waiting for message\n");
        tcsetattr(tty_fd,TCSANOW,&tio);
        unsigned char msg[256];
        int i = 0;
        std::string letter;
        std::string message;
        std::string test;
        while (c!='q')
        {
                if (read(tty_fd,&c,1)>0){
                	//write(STDOUT_FILENO,&c,1);              // if new data is available on the serial port, print it out
                	letter.append(reinterpret_cast<const char*>(&c));
                }
                if (read(STDIN_FILENO,&c,1)>0)  write(tty_fd,&c,1);
                else{
                	message.append(letter);
                	letter = "";
                	if (message.length() > 100){
                		printf("%s", message.c_str());
                		//std::string test = extractor(message);
                		//printf("%s", test.c_str());
                		test = "";
                		message = "";
                	}
                	//printf("%s", letter.c_str());
                	/*
                	std::string peppu = extractor(message.c_str());
                	printf("%s", peppu.c_str());
                	*/

                }
       }
        close(tty_fd);
        tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);
        return EXIT_SUCCESS;

}


