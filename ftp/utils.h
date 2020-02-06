
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 1024

#define N_BACKLOG 64

#define COMMAND_NUMBER 128

#define TRUE 1
#define FALSE 0

//typedef unsigned short uint8_t;
typedef uint8_t bool_t;


void perror_die(char* msg);

int listen_inet_socket(int portnum);

void report_peer_connected(const struct sockaddr_in* sa, socklen_t salen);

bool_t has_prefix(char* str,char* preffix);

bool_t has_suffix(char* str,char* suffix);

char* strip(char *str);