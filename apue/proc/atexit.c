
#include <stdio.h>
#include <stdlib.h>


/*
    atexit用来注册exit时的处理函数
*/


static void my_exit2(void);
static void my_exit1(void);

static void my_exit3(void);
int main(int argc, char const *argv[])
{
    if(atexit(my_exit3)!=0){
        fprintf(stderr,"can't register my_exit1");
        exit(EXIT_FAILURE);
    }

    if(atexit(my_exit2)!=0){
        fprintf(stderr,"can't register my_exit2");
        exit(EXIT_FAILURE);
    }
    if(atexit(my_exit1)!=0){
        fprintf(stderr,"can't register my_exit1");
        exit(EXIT_FAILURE);
    }
    if(atexit(my_exit1)!=0){
        fprintf(stderr,"can't register my_exit1");
        exit(EXIT_FAILURE);
    }

    printf("main is donw\n");


    
    return 0;
}


static void my_exit3(void)
{
    printf("third exit handler\n");
}


static void my_exit1(void)
{
    printf("first exit handler\n");
}

static void my_exit2(void)
{
    printf("second exit handler\n");
}