#include <stdio.h>

#include "../utils.h"

#define COMMAND_PORT 9000
#define DATA_PORT 9001


int main(int argc, char const *argv[])
{
    printf("THis is client!\n");

    struct sockaddr_in  addr;
    char buf[BUF_SIZE];
    char rec[BUF_SIZE];

    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1){
        perror_die("socket create error!");
    }
    
    memset(&addr, 0 ,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    if(connect(sfd,(struct sockaddr*)&addr, sizeof(addr)) == -1){
        perror_die("connect error!\n");
    }

    //recive ack
    recv(sfd,rec,BUF_SIZE,0);
    printf("%s\n",rec);

    //建立连接后创建新进程，用于listen数据端口
    pid_t pid = fork();
    if(pid == 0){
        printf("hello");
        char send_data_buf[BUF_SIZE];
        char recv_data_buf[BUF_SIZE];
        int data_sfd = listen_inet_socket(DATA_PORT);
        while(1){

            memset(send_data_buf,0,sizeof(send_data_buf));
            memset(recv_data_buf,0,sizeof(recv_data_buf));

            int len = recv(, buf,sizeof(buf),0);
            if(len<0){
                perror_die("recv error!");
            }else if(len == 0){
                break;
            }


        }
    }else{//父亲进程循环读取命令。。。
        while(1){
            if(fgets(buf,BUF_SIZE,stdin) == NULL)
                break;
            buf[strlen(buf) - 1] = '\0';
            send(sfd,buf,BUF_SIZE,0);

            memset(rec,0,BUF_SIZE);
            int numRead;
            if(recv(sfd,rec, BUF_SIZE,0) >0){
                printf("%s\n",rec);
            }
            memset(buf,0,BUF_SIZE);
        }
    }


    return 0;
    
}
