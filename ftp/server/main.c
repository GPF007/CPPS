#include <stdio.h>
#include "../utils.h"
#include "server-pi.h"

//typedef enum {WAIT_FOR_MSG, IN_MSG} ProcessingState;

void serve_connection(int sockfd)
{
    //向远端客户段写入一个字符 ×
    uint8_t ack[BUF_SIZE]="connect established!";
    if(send(sockfd,ack,sizeof(ack),0)<sizeof(ack)){
        fprintf(stderr,"send error!");
        exit(1);
    }

    char buf[BUF_SIZE];

    //ProcessingState state = WAIT_FOR_MSG;

    //创建2个管道
    int ch1[2]; //parent -> child
    int ch2[2]; //child ->parent
    pid_t pid;
    //创建父进程和子进程之间的管道
    if(pipe(ch1) < 0){
        perror_die("pipe error");
    }
    if(pipe(ch2) < 0){
        perror_die("pipe error");
    }
    //创建命令处理的进程
    pid = fork();
    if(pid == 0){//子进程
        close(ch1[1]);  
        close(ch2[0]);
        char child_buf[BUF_SIZE];

        while(1){
            int n =read(ch1[0], child_buf,sizeof(child_buf));
            if( n < 0){
                perror_die("read from cmd process error!");
            }  
            get_cmd(child_buf,ch2[1]); 
        }
    }else{//父进程关闭写
        close(ch1[0]);  
        close(ch2[1]);
        char recv_buf[BUF_SIZE];

        while(1){
            memset(buf,0,sizeof(buf));
            memset(recv_buf,0,sizeof(recv_buf));

            int len = recv(sockfd, buf,sizeof(buf),0);
            if(len<0){
                perror_die("recv error!");
            }else if(len == 0){
                break;
            }


            len = write(ch1[1],buf,sizeof(buf));
            if(len <0){
                perror_die("write command to cmd process error!");
            }

            while(1){
                int n =read(ch2[0], recv_buf, BUF_SIZE);
                if(n < 0){
                    perror_die("read response error!");
                }

                if(has_suffix(recv_buf, end_mark)){
                    recv_buf[strlen(recv_buf) - strlen(end_mark) ] = '\0';
                    if(send(sockfd, recv_buf,BUF_SIZE, 0) < BUF_SIZE){
                        perror_die("send error!");
                    }
                    break;
                }

                if(send(sockfd, recv_buf,BUF_SIZE, 0) < BUF_SIZE){
                    perror_die("send error!");
                }
            }
        }
    }


    
    close(sockfd);
}


int main(int argc, char const *argv[])
{

    int portnum = 9000;
    if(argc>=2){
        portnum = atoi(argv[1]);
    }

    printf("Serving on port %d\n",portnum);
    init_handlers();

    int sockfd = listen_inet_socket(portnum);
    while(1){
        struct sockaddr_in peer_addr;
        socklen_t peer_addr_len = sizeof(peer_addr);

        int newsockfd = accept(sockfd, (struct sockaddr*)&peer_addr, &peer_addr_len);
        if(newsockfd < 0){
            perror_die("accept error!");
        }

        report_peer_connected(&peer_addr,peer_addr_len);
        serve_connection(newsockfd);

        printf("peer done\n");

    }

    
    printf("THis is server!\n");
    return 0;
}
