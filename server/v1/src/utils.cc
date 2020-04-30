#include "utils.h"

#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


/*一些包裹函数*/

void err_sys(const char *str){
    fprintf(stderr,"%s\n",str);
}

void err_quit(const char *str){
    fprintf(stderr,"%s\n",str);
    exit(EXIT_FAILURE);
}

/*socket*/
int Socket (int domain, int type, int protocal){
    int fd = socket(domain,type,protocal);
    if(fd<0)
        err_quit("socket create error!");
    return fd;
}

void Bind(int sfd, const struct sockaddr *addr, socklen_t addrlen){
    if(bind(sfd,addr,addrlen)==-1)
        err_quit("bind error!");
}

void Listen(int sfd,int backlog){
    if(listen(sfd,backlog)==-1)
        err_quit("listen error!");
}

int Accept(int sfd,struct sockaddr *cliaddr,socklen_t *addrlen){
    int r = accept(sfd,cliaddr,addrlen);
    if(r<0)
        err_quit("Accept error!");
    return r;
}

pid_t Fork(){
    pid_t ret = fork();
    if(ret<0)
        err_quit("Fork error!");
    return ret;
}

void Close(int sfd){
    if(close(sfd)<0)
        err_quit("Close error!");
}