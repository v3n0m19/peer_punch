#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>
#define MAX_L 128
#define MAXLINE 1024
#define MAXSIZE 1024
#include"udp_punch.h"
#include"stun.h"