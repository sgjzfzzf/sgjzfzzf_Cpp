#ifndef socketprogram
#define socketprogram
#define MAXLINE 0xff
#define LISTENQ 0xf
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

int readline(int, char *);
int open_client(char *hostname, char *port);
int open_listenfd(char *port);

#endif