#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

/* change this definition for the correct port */
#define COMPASS "/dev/i2c-1" //I2C port
#define k 0.0041175
#define m 235.62
//NOTE:  I think I am using i2c-1.  I have connected the HMC5883L to pins 17,18 on P9.
//Hard to argue with i2ctools.

#define _POSIX_SOURCE 1 /* POSIX compliant source */
int heading = 0;

int findHeading(short _x, short _z){
	if (_z > 0){
		heading = k*_x + m;
	}
	else{
		heading = 360 - k*_x - m;
	}
	return heading;
}

int main(){

int fd, c, res;
int daddr = 0x1e; //address of HMC5883L before shifting.
int i;
useconds_t dtime = 8; //delay for usleep
// buffers for commands.
char write0[4]; // command to set reg 0 - AKA Configuration Register A
char write1[4]; // command to set reg 1 - AKA Configuration Register B
char write2[4]; // command to set reg 2 - AKA Mode Register

write0[0] = 0x00; // reg 00
write0[1] = 0x70; // average 8 samples, 15Hz output
write1[0] = 0x01; // reg 01
write1[1] = 0xA0; // gain 5
write2[0] = 0x02; // reg 02
write2[1] = 0x01; // mode single measurement
//
char buf[10];

if ((fd = open(COMPASS, O_RDWR )) < 0) {;
    perror("Failed to open the I2C bus\n");
    exit(1);
}
// Sets the slave address for reads & writes
// see i2c-dev.h
if (ioctl(fd, I2C_SLAVE,daddr) < 0) {
   printf("Failed to access\n");
   exit(1);
}

for (int j = 0; j<100; j++){
//Set reg 0
if (write(fd,write0,2) != 2) {
   printf("Write to zero failed\n");
}
//Set reg 1
if (write(fd,write1,2) != 2) {
   printf("Write to one failed\n");
}
//Set reg 2
if (write(fd,write2,2) != 2) {
   printf("Write to two failed\n");
}

//datasheet says to delay here.
if ( usleep(dtime)  < 0) {
   printf("sleep error\n");
}

//read the 6 data.
if (read(fd, buf, 6) != 6) {
   printf("Read failed\n");
}
/*
for (i = 0;i<6;i++) {
   printf("values %d  %x\n",i,buf[i]);
}
*/

short hX = ((short)buf[1]<<8) | (short) buf[0];
short hY = ((short)buf[3]<<8) | (short) buf[2];
short hZ = ((short)buf[5]<<8) | (short) buf[4];

//printf("hX: %d, hY: %d, hZ: %d \n",hX,hY,hZ);
int head = findHeading(hX,hZ);
std::cout << "X-heading is: " << head << " hX: " << hX << " hZ: " << hZ << std::endl;
sleep(0.2);
}

}
