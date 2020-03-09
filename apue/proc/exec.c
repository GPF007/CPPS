#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//char *env_init = {"USER=unknown", "PATH=/tmp",NULL};

int main(int argc, char const *argv[])
{
    pid_t pid;

    /*
    if((pid = fork())==0){
        execle("/home/gpf/bin/echoall","echoall", "myarg1",
        "MY ARG2", (char *)0, env_init);
    }

    if(waitpid(pid,NULL,0) < 0){
        fprintf(stderr,"wait error");
    }
    */
    if((pid = fork()) == 0){
        printf("this is child process.\n");
        execlp("./echoall","echoall","only 1 arg",(char *)0);
    }else{
        printf("this is parent precess.\n");
    }


    return 0;
}
