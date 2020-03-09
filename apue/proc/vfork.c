#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int globvar = 6;
char buf[] = "a write to stdout\n";

int main(int argc, char const *argv[])
{
    int var=88;
    pid_t pid;
    printf("befor fork\n");

    if((pid = vfork()) == 0){
        globvar++;
        var++;
        _exit(0);
    }


    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);
    return 0;
}
