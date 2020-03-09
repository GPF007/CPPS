#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int globvar = 6;
char buf[] = "a write to stdout\n";

int main(int argc, char const *argv[])
{
    int var=10;
    pid_t pid;
    if(write(STDOUT_FILENO, buf,sizeof(buf)-1)!= sizeof(buf)-1){
        exit(1);
    }

    printf("befor fork\n");

    if((pid = fork()) == 0){
        globvar++;
        var++;
    }else{
        sleep(2);
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);
    return 0;
}
