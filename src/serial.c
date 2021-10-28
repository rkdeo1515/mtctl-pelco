#include "serial.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int openserial(char *devicename, unsigned int baudrate) {
    int fd;
    struct termios newtio;
    fd = open(devicename, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror(devicename);
        exit(-1);
    }
    //fcntl(fd, F_SETFL, FNDELAY);
    memset(&newtio, 0, sizeof(newtio));
    //newtio.c_cflag = getbaudrate(baudrate);
    // newtio.c_cflag = newtio.c_cflag | CRTSCTS | CS8 | CLOCAL | CREAD | PARENB;
    // newtio.c_iflag = IGNPAR;
    newtio.c_cflag = getbaudrate(baudrate) | CS8 | CLOCAL | CREAD;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;

    newtio.c_cc[VTIME] = 10; /* timer disable */
    newtio.c_cc[VMIN] = 0;   /* block until read 1 character  */

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &newtio);

    return fd;
}

unsigned char readbyte(int fd) {
    int res;
    char buf;
    res = read(fd, &buf, 1);
    if (res)
        return buf;

    return -1;
}
void writebyte(int fd, unsigned char b) {
    write(fd, &b, 1);
}

void closeserial(int fd) {
    close(fd);
}

int getbaudrate(unsigned int baud) {
    switch (baud) {
        case 2400:
            return B2400;
        case 4800:
            return B4800;
        case 9600:
            return B9600;
        case 19200:
            return B19200;
        case 38400:
            return B38400;
        case 57600:
            return B57600;
        case 115200:
            return B115200;
        case 230400:
            return B230400;
    }
    return -1;
}
