#include <stdio.h>
#include <shadow.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
void function(int,char*, char*);
void ls_function(char*);
void cd_function(char*,char*);
void puts_function(int, char*);
void gets_function(int,char*,char*);
void remove_function(char*, char*);
void error(char*);
void pwd_function(char*);
void send_n(int, char*, int);
void recv_n(int, char*, int);
void record(char*);
typedef struct{
	int len;
	char buf[2000];
}sen, *psen;
