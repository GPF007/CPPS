#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

typedef void Sigfunc(int);

static void sig_usr(int);

int main(int argc, char const *argv[])
{
    if(signal(SIGUSR1, sig_usr) == SIG_ERR)
        exit(1);
    
    if(signal(SIGUSR2, sig_usr) == SIG_ERR)
        exit(1);

    for(;;)
        pause();
    //调用进程挂起直至捕捉到一个信号。只有执行了一个信号处理程序并从其返回时，pause才返回。在这种情况下，pause返回-1.    
    
    return 0;
}

static void sig_usr(int signo)
{
    if(signo == SIGUSR1)
        printf("reveived SIGUSR1\n");
    else if(signo == SIGUSR2)
        printf("reveived SIGUSR2\n");
}
