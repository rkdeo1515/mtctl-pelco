#ifndef __SERIAL_H__
#define __SERIAL_H__

int getbaudrate(unsigned int baud);
int openserial(char *devicename, unsigned int baudrate);
unsigned char readbyte(int fd);
void writebyte(int fd, unsigned char b);
void closeserial(int fd);
#endif