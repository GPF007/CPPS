#include "server-pi.h"




void init_handlers()
{
    cmd_handlers[0] = &handler_user;
    cmd_handlers[1] = &handler_pass;
    cmd_handlers[2] = &handler_list;
    cmd_handlers[3] = &handler_retr;
    cmd_handlers[4] = &handler_stor;
}



int get_cmd(char* cmd,int write_fd)
{
    //去除末尾的换行符号
    //cmd[strlen(cmd)-1] = '\0';

    char tmp[BUF_SIZE];

    int i;

    memset(tmp,0,sizeof(tmp));
    //便利命令列表，查找相应的命令
    for(i=0; i<COMMAND_NUMBER;i++){
        if(strlen(cmds[i]) == 0){
            printf("Unknown command: %s\n",cmd);
            sprintf(tmp, "Unknown command: %s\n", cmd);
            strcat(tmp, end_mark);
            //write(write_fd, tmp, sizeof(tmp));
            break;
        }

        if(has_prefix(cmd, cmds[i])){
            //调用相应的命令处理函数
            cmd_handlers[i](cmd, tmp);
            //write(write_fd, tmp, sizeof(tmp));
            break;
        }

    }
    if(write(write_fd, tmp, sizeof(tmp)) < 0){
        perror_die("write back to parent process error!");
    }
    return 1;
}



void handler_user(char* cmd, char* resp)
{
    char *username = strip(cmd+4);
    printf("Get username is %s\n",username);
    sprintf(resp, "Get username is %s\n",username);
    strcat(resp, end_mark);
}

void handler_pass(char* cmd, char* resp)
{
    char *password = strip(cmd+4);
    printf("Get password is %s\n",password);
    sprintf(resp,"Get password is %s\n",password);
    strcat(resp, end_mark);
}


void handler_list(char* cmd, char* resp)
{
    printf("list commend\n");
    strcpy(resp, cmd);
    strcat(resp, end_mark);
}

void handler_retr(char* cmd, char* resp)
{
    printf("get a file \n");
    strcpy(resp, cmd);
    strcat(resp, end_mark);
}

void handler_stor(char* cmd, char* resp)
{
    printf("store a file \n");
    strcpy(resp, cmd);
    strcat(resp, end_mark);

}