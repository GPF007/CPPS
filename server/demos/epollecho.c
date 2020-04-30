/**
 * epoll LT echo server
 * run command
 * server: ./a.out
 * clinet: nc localhost 2020
 * */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

char buf[4096];

#define exit_if(r,...)                  \
    if(r){                              \
        printf(__VA_ARGS__);            \
        printf("%s:%d error no: %d error msg %s\n",__FILE__,    \
            __LINE__, errno, strerror(errno));                  \
        exit(EXIT_FAILURE);             \
    }


void setNonBlock(int fd){
    int flags = fcntl(fd, F_GETFL,0);
    exit_if(flags <0,"fcntl failed");
    int r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    exit_if(r<0, "fcntl failed");

}
/*
ssize_t readn(int fd, void *vptr, size_t n){
    size_t nleft = n;
    ssize_t nread;
    char *ptr = vptr;
    while(nleft>0){
        nread = read(fd,ptr,nleft);
        if(nread>0){
            nleft -=nread;
            ptr += nread;
            continue;
        }
        if(nread==0){//EOF
            close(fd);
            return;
        }
        else if(nread == -1 && errno == EINTR)
            continue;
        else if(nread == -1 && ( errno == EAGAIN || errno == EWOULDBLOCK)){
            return;           
        }else if(nread <0){
            printf("read %d error %d %s\n",fd,errno,strerror(errno));
        }
    }
}
ssize_t writen(int fd, void *vptr, size_t n){
    size_t nleft = n;
    ssize_t nwritten;
    const char *ptr = vptr;
    while(nleft>0){
        nwritten = read(fd,ptr,nleft);
        if(nwritten>0){
            nleft -=nwritten;
            ptr += nwritten;
            continue;
        }
        if(nwritten == -1 && errno == EINTR)
            continue;
        else if(nwritten == -1 && ( errno == EAGAIN || errno == EWOULDBLOCK)){
            return;           
        }else if(nwritten <0){
            printf("write %d error %d %s\n",fd,errno,strerror(errno));
        }
    }
}

*/
void updateEvents(int efd, int fd,int events, int op){
    struct epoll_event ev;
    memset(&ev, 0 ,sizeof(ev));
    ev.events = events;
    ev.data.fd = fd;
    const char* strevnet = op ==EPOLL_CTL_MOD?"mod":"add";
    printf("%s fd %d events read %d write %d\n",strevnet, fd, ev.events&EPOLLIN,
        ev.events &  EPOLLOUT);
    int r = epoll_ctl(efd,op,fd, &ev);
    exit_if(r, "epoll_ctl failed");
}


void handleAccept(int efd, int fd){
    struct sockaddr_in raddr;
    socklen_t rsz = sizeof(raddr);
    int cfd = accept(fd, (struct sockaddr *)&raddr, &rsz);
    exit_if(cfd<0,"accept failed");
    struct sockaddr_in peer, local;
    socklen_t alen = sizeof(peer);
    int r = getpeername(cfd, (struct sockaddr *)&peer, &alen);
    exit_if(r<0,"getpeername failed");
    printf("accept a connection from %s\n",inet_ntoa(raddr.sin_addr));
    setNonBlock(cfd);
    //加入新的connectfd到epoll，监听读事件
    updateEvents(efd,cfd, EPOLLIN, EPOLL_CTL_ADD);
}

void handleRead(int efd, int fd){
    //char buf[4096];
    int len = read(fd,buf,sizeof(buf));
    if(len == -1 && (errno != EAGAIN && errno != EWOULDBLOCK)){
        printf("receive error!\n");
    }else if(len ==0){ //EOF
        printf("client disconnected...\n");
        updateEvents(efd,fd,0,EPOLL_CTL_DEL);
        printf("close fd %d\n",fd);
        close(fd);
    }else{
        write(fd,buf,len);
    }
}

void handleWrite(int efd, int fd){
    write(fd,buf,sizeof(buf));
}

int main(int argc, char const *argv[])
{
    /* code */
    //创建epollfd
    unsigned short port = 2020;
    int waitms = 2000;

    int epollfd = epoll_create(1);
    exit_if(epollfd<0,"epoll_create failed");
    //绑定listenfd
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    exit_if(listenfd<0,"socket failed");
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    int r = bind(listenfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
    exit_if(r,"bind to 0.0.0.0:%d  error %d %s",port, errno, strerror(errno));
    r = listen(listenfd,20);
    exit_if(r,"listen failed %d %s",errno, strerror(errno));
    printf("fd %d listening at %d\n",listenfd,port);
    setNonBlock(listenfd);
    //将listenfd加入epoll事件
    updateEvents(epollfd, listenfd, EPOLLIN, EPOLL_CTL_ADD);

    for(;;){
        //loop once
        const int maxEvents = 20;//events的最大size
        struct epoll_event activeEvs[100];
        int n = epoll_wait(epollfd, activeEvs, maxEvents,waitms);
        printf("epoll_wait return %d\n",n);
        for(int i=0;i<n;i++){
            int fd =activeEvs[i].data.fd;
            int events = activeEvs[i].events;
            if(events & (EPOLLIN | EPOLLERR)){//可读
                if(fd == listenfd)
                    handleAccept(epollfd,fd);
                else
                    handleRead(epollfd, fd);
            }else if(events & EPOLLOUT){//可写的
                printf("handling epollout\n");
                handleWrite(epollfd, fd);
            }else{
                exit_if(1,"unknown event");
            }
        }
    }

    return 0;
}
