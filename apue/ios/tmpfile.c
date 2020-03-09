#include <stdio.h>
#define MAXLINE 1024

int main(int argc, char const *argv[])
{
    char name[L_tmpnam],line[MAXLINE];
    FILE *fp;

    printf("%s\n", tmpnam(NULL));

    tmpnam(name);
    printf("%s\n", name);

    if((fp = tmpfile())!=NULL){
        return 0;
    }
    fputs("one line of output\n", fp);
    rewind(fp);
    if(fgets(line, sizeof(line), fp) == NULL)
        return 0;
    fputs(line, stdout);

    return 0;
}
