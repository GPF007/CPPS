#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MAXLINE 80
static void sig_alrm(int);

int main(int argc, char const *argv[])
{
    int n;
    char line[MAXLINE];

    if(signal(SIGALRM, sig_alrm) ==SIG_ERR)
        exit(1);
    
    alarm(10);

    if((n=read(STDIN_FILENO,line,MAXLINE))<0)
        exit(1);
    
    int remain = alarm(0);

    write(STDOUT_FILENO,line,n);
    printf("remain: %d\n",remain);
    return 0;
}


static void 
sig_alrm(int signo)
{

    exit(0);

}