#include "server.h"
#include "utils.h"
#include "threadpool.h"
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define SERV_PORT 1088
#define MAXLINE 1024
#define THREAD 32
#define QUEUE  256
typedef struct sockaddr SA;

threadpool_t *pool;

void str_echo(void * arg);

void Server::start(){
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
    listen(listenfd,5);
    pool = threadpool_create(THREAD, QUEUE, 0);

    printf("Server start!\n");
    for(;;){
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd,(SA *)&cliaddr, &clilen);

        //多线程处理
        //threadpool_add(pool,&str_echo,(void *)&connfd,0);
        
        if((childpid = fork())!=0){
            close(listenfd);
            str_echo((void *)&connfd);
            exit(0);
        }
        
        
        
        close(connfd);
        printf("done with client %d\n",connfd);
    }
}

void str_echo(void * arg){
    int fd = *(int *)arg;
    printf("Process with sfd:%d\n",fd);
    size_t n;
    char buf[MAXLINE];

    //printf("thread id=%lu\n",pthread_self());//获取当前线程ID

    for(;;){
        n = read(fd,buf,MAXLINE);
        if(n>0){
            write(fd,buf,n);
            continue;
        }else if(n == 0)
            break;
        //error
        if(n< 0 && errno ==EINTR)
            continue;
        else if(n<0)
            err_sys("str_echo: read error");
        break;
    }

    Close(fd);



}