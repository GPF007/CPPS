#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char buf[1024];
    fgets(buf,1024,stdin);
    printf("buf length is %ld\n",strlen(buf));
    strcat(buf,"\n");
    printf("after strcat length is %ld\n",strlen(buf));
    char p[1]={'\0'};
    if(p[0]){
        printf("p[0] is not null\n");
    }
    return 0;
}
