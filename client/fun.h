#include <stdio.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <strings.h>
void gets_function(int,char*);
void puts_function(int, char*);
void send_n(int, char*,int);
void recv_n(int,char*, int);
char* trans(char*);
typedef struct{
	int len;
	char buf[2000];
}sen, *psen;
