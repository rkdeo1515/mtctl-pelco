#include "command.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
struct option {
    const char *name;   // long name of option
    int has_arg;        // option param, no_argument==0, required_argument==1 
    int *flag;          // pointer of flag variable
    int val;            // value of flag variable or short name 
};
*/

//static int verbose_flag = 0;

void help() {
    printf(
        "Usage\n"
        "\n"
        "	./mtctl [options] \"command\"\n"
        "\n"
        "Options\n"
        "\n"
        "	-v --verbose	print log\n"
        "	-u, --usec	    use usec (default is sec)\n"
        "*	-d, --delay	    command delay time\n"
        "*	-c, --count	    command repeat count\n"
        "*	-l, --len       (Byte)length of command\n"
        "*	-b, --boudrate	serial port speed\n"
        "*	-p, --port	    serial port path\n"
        "\n"
        "	(You must use the options marked with *)\n"
        "\n"
        "Command\n"
        "\n"
        "	See the pelco-D or pelco-P protocol.\n"
        "\n"
        "Example\n"
        "\n"
        "	(tilt-up)\n"
        "	./mtctl -v -u -d 150000 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 08 20 20 49\'\n"
        "	./mtctl -v -u -d 1 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 00 00 00 01\'\n"
        "\n"
        "	(tilt-down)\n"
        "	./mtctl -v -u -d 150000 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 10 20 20 51\'\n"
        "	./mtctl -v -u -d 1 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 00 00 00 01\'\n"
        "\n"
        "	(pan-left)\n"
        "	./mtctl -v -u -d 150000 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 04 20 20 45\'\n"
        "	./mtctl -v -u -d 1 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 00 00 00 01\'\n"
        "\n"
        "	(pan-right)\n"
        "	./mtctl -v -u -d 150000 -c 1 -b 2400 -p /dev/ttyUSB0 \'FF 01 00 02 20 20 43\'\n"
        "	./mtctl -v -u -d 1 -c 1 -b 2400 -p /dev/ttyUSB0 \'FF 01 00 00 00 00 01\'\n"
        "\n");
}

int parseCommand(int argc, char *argv[], cparam *cmd) {
    while (1) {
        static struct option long_options[] = {
            //{"verbose", no_argument, &verbose_flag, 1},
            {"help", no_argument, 0, 'h'},
            {"verbose", no_argument, 0, 'v'},
            {"usec", required_argument, 0, 'u'},
            {"delay", required_argument, 0, 'd'},
            {"count", required_argument, 0, 'c'},
            {"length", required_argument, 0, 'l'},
            {"baudrate", required_argument, 0, 'b'},
            {"port", required_argument, 0, 'p'},
            {0, 0, 0, 0}};

        int option_index = 0;
        int c = getopt_long(argc, argv, "vud:c:l:b:p:h",
                            long_options, &option_index);
        if (c == -1) {
            break;
        }
        switch (c) {
            case 0:
                if (long_options[option_index].flag != 0)
                    break;
                //printf("option %s", long_options[option_index].name);
                if (optarg)
                    //printf("with arg %s", optarg);
                    //printf("\n");
                    break;
            case 'v':
                cmd->verbose = 1;
                break;
            case 'u':
                cmd->usec = 1;
                break;
            case 'd':
                cmd->delay = atoi(optarg);
                break;
            case 'c':
                cmd->count = atoi(optarg);
                break;
            case 'l':
                cmd->len = atoi(optarg);
                break;
            case 'b':
                cmd->baudrate = atoi(optarg);
                break;
            case 'p':
                strcpy(cmd->device, optarg);
                break;
            case 'h':
                help();
                exit(0);
                break;
            default:
                help();
                abort();
                break;
        }
    }
    if (!argv[optind]) {
        exit(0);
    }
    //cmd->verbose = verbose_flag;
    strcpy(cmd->message, argv[optind]);

    return 0;
}