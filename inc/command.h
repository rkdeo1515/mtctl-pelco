#ifndef __COMMNAD_H__
#define __COMMNAD_H__

typedef struct command_param {
    int verbose;
    int usec;
    unsigned int delay;
    unsigned int count;
    int len;
    unsigned int baudrate;
    char device[64];
    char message[23];
} cparam;

int parseCommand(int argc, char *argv[], cparam *cmd);

#endif
