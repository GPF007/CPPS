#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>



/*根据 status的至判断得到子进程推出的状态*/
void pr_exit(int status)
{
    if(WIFEXITED(status))
        printf("子进程正常终止, exit status = %d\n",
        WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("子进程异常终止, signal number = %d%s\n",
        WTERMSIG(status),
    #ifdef WCOREDUMP //如果定义了 WCOREDUMP宏会产生终止进程的core文件
        WCOREDUMP(status) ? "(core file generated)":"");
    #else
        "");
    #endif
    
    else if(WIFSTOPPED(status))
        printf("子进程停止, singal number = %d\n",
        WSTOPSIG(status));
}

int main(int argc, char const *argv[])
{
    int status;

    if((status = system("date")) <0){
        fprintf(stderr,"system() error\n");
        exit(1);
    }
    pr_exit(status);

    if((status = system("nosuchcommand")) <0){
        fprintf(stderr,"system() error\n");
        exit(1);
    }
    pr_exit(status);

    if((status = system("who; exit 44")) <0){
        fprintf(stderr,"system() error\n");
        exit(1);
    }
    pr_exit(status);
    return 0;
}
