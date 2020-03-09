#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static void charatatime(char *);

int main(int argc, char const *argv[])
{
    pid_t pid;
    if((pid = fork())==0)
        charatatime("output from child\n");
    else
        charatatime("output from parent\n");
    return 0;
}

static void charatatime(char *str)
{
    char *ptr;
    int c;


    setbuf(stdout, NULL); //关闭缓冲
    for(ptr = str; (c= *ptr++)!=0;)
        putc(c,stdout);


}

