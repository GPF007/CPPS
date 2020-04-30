#define THREAD 32
#define QUEUE  256

#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#include "threadpool.h"
#include "server.h"
#include "utils.h"

void print_task(void *arg) {
    char* str = (char*)arg;
    printf("get message is:%s\n",str);
}

int main(int argc, char **argv)
{/*
    threadpool_t *pool;

    pthread_mutex_init(&lock, NULL);

    assert((pool = threadpool_create(THREAD, QUEUE, 0)) != NULL);
    fprintf(stderr, "Pool started with %d threads and "
            "queue size of %d\n", THREAD, QUEUE);

    char buf[1024];
    for(;;){
        fgets(buf,1024,stdin);
        threadpool_add(pool,&print_task,buf,0);
        printf("pool count:%d\n",get_count(pool));
    }
    */
    Server server;
    server.start();
    err_sys("hello");
    

    return 0;
}