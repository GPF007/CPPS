#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    if(argc!=2){
        exit(1);
    }

    if(access(argv[1], R_OK)<0){
        fprintf(stderr,"access error for %s", argv[1]);
    }
    else
        printf("read access OK\n");

    open(argv[1], O_RDONLY);
    printf("open for reading OK\n");
    
    return 0;
}
