#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define HOSTNAME "192.168.1.1"
#define PORT 5556
#define BUFSIZE 1024

#define CMD_REF "REF"
#define CMD_PCMD "PCMD"

#define INIT_SEQ_NUM 30000
#define SENDING_INTERVAL 50		// in milliseconds

#define TAKEOFF "290718208"
#define LANDING "290717696"


#define HOVE_MODE "0"
#define PROG_MODE "1"
#define COMB_MODE "2"
#define PROC_MODE "3"

//#define BACK_DIR "1065353216" // fast
#define BACK_DIR "1048576000" // slow
//#define FRONT_DIR "-1082130432" // fast
#define FRONT_DIR "-1098907648" // slow
#define NO_DIR "0"

#define DEBUG

#endif