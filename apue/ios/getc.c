#include <stdio.h>

int main(int argc, char const *argv[])
{

    /* getc 和 putc是用宏实现的 */
    int c;
    while((c = getc(stdin))!=EOF){
        if(putc(c,stdout) == EOF){
            fprintf(stderr,"output error!");
            return 0;
        }        
    }
    if(ferror(stdin)){
        fprintf(stderr,"input error");
    }
    return 0;
}
