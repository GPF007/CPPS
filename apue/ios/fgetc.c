#include <stdio.h>

#define MAXLINE 100

int main(int argc, char const *argv[])
{

    char buf[MAXLINE];

    /* getc 和 putc是用宏实现的 */

    while(fgets(buf,MAXLINE, stdin) !=NULL ){
        if(fputs(buf,stdout) == EOF){
            fprintf(stderr,"output error!");
            return 0;
        }        
    }


    if(ferror(stdin)){
        fprintf(stderr,"input error");
    }
    return 0;
}
