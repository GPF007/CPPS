#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char const *argv[])
{
    /* code */
    time_t t;
    struct tm *tmp;

    char buf1[16];
    char buf2[64];;

    time(&t);
    tmp = localtime(&t);

    if(strftime(buf1, 16, "time and data: %r, %a %b %d, %Y",tmp) == 0)
        printf("buffer length16 is too small\n");
    else 
        printf("%s\n",buf1);
    
    if(strftime(buf2, 64, "time and data: %r, %a %b %d, %Y",tmp) == 0)
        printf("buffer length 64 is too small\n");
    else 
        printf("%s\n",buf2);
    
    

    return 0;
}
