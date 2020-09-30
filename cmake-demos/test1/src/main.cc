#include "mylib.h"
#include <stdio.h>
#include <math.h>
#include <pthread.h>

void* foo(void* arg){

}

int main(int argc, char const *argv[])
{
    /* code */
    printf("%d\n",add(1,3));
    printf("sqrt(2) = %lf\n",sqrt(2.0));
    pthread_t id;

    return 0;
}
