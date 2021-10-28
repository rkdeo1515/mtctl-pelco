#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "command.h"
#include "serial.h"

#define print_dbg 0

#define VERBOSE 0
#define BAUDRATE 115200
#define CONFIG "8N1"
#define DEVICE "/dev/ttyUSB0"
#define MSG ""
int quit = 0;
int fd;

void siginthandler(int signo) {
    fprintf(stdout, "QUIT SIGNAL..\n");
    close(fd);
    exit(0);
}

int str2Hex(const char *param) {
    int hex = 0;
    int count = strlen(param), i = 0;

    for (i = 0; i < count; i++) {
        if (*param >= '0' && *param <= '9')
            hex = hex * 16 + *param - '0';
        else if (*param >= 'A' && *param <= 'F')
            hex = hex * 16 + *param - 'A' + 10;
        else if (*param >= 'a' && *param <= 'f')
            hex = hex * 16 + *param - 'a' + 10;
        param++;
    }
    return hex;
}
void parsemsg(char s[], unsigned char h[], int len) {
    //unsigned char buf[2]; str2Hex("ff"))
    char tmp[2];
    int i = 0;
    int j = 0;
    for (i = 0; i < len; i++) {
        tmp[0] = s[j++];
        tmp[1] = s[j++];
        h[i] = str2Hex(tmp);
        j++;
    }
}

int main(int argc, char *argv[]) {
    cparam cmd;
    unsigned char cmd_buf[8];
    cmd.verbose = 0;
    cmd.delay = 0;
    cmd.count = 0;
    cmd.baudrate = BAUDRATE;
    strcpy(cmd.device, DEVICE);
    strcpy(cmd.message, MSG);

    memset(&cmd, 0, sizeof(cmd));
    parseCommand(argc, argv, &cmd);
    parsemsg(cmd.message, cmd_buf, cmd.len);

    if (cmd.verbose) {
        printf("cmd.verbose  :%d\n", cmd.verbose);
        printf("cmd.delay  :%d\n", cmd.delay);
        printf("cmd.count  :%d\n", cmd.count);
        printf("cmd.len  :%d\n", cmd.len);
        printf("cmd.baudrate :%d\n", cmd.baudrate);
        printf("cmd.device   :%s\n", cmd.device);
        printf("cmd.message   :%s\n", cmd.message);
    }

    fd = openserial(cmd.device, cmd.baudrate);
    signal(SIGINT, siginthandler);

    while (cmd.count--) {
        int i=0;
        int res=0;

        // checksum check
        if(cmd.len==7){
            for (i = 1; i < cmd.len-1; i++) {
                res += cmd_buf[i];
            };
            res = cmd_buf[cmd.len-1]^res;
        }
        else{
            for (i = 0; i < cmd.len-1; i++) {
                res ^= cmd_buf[i];
            };
            res = cmd_buf[cmd.len-1]^res;
        }
        
        if (cmd.verbose) {
            if(res){
                printf("Checksum Err : 0x%X\n", res);
                close(fd);
                exit(0);
            }
            printf("%d: ", cmd.count);
            for (i = 0; i < cmd.len; i++) {
                printf("%02x ", cmd_buf[i]);
            };
            printf("\n");
        }
        
        write(fd, cmd_buf, cmd.len);

        if (cmd.usec)
            usleep(cmd.delay);
        else
            sleep(cmd.delay);
    }
    close(fd);
    printf("CLOSE..!\n");
    return 0;
}