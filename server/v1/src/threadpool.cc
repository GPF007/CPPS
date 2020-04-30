#include "threadpool.h"


typedef enum{
    immediate_shutdown = 1,
    graceful_shutdown = 2
}threadpool_shutdown_t;


//这个是每个线程需要执行的函数u
static void *threadpool_thread(void *threadpool);
int threadpool_free(threadpool_t* pool);


/*导出的函数*/
threadpool_t *threadpool_create(int thread_count, int queue_size,int flags){
    threadpool_t *pool;
    int i;
    if(thread_count<=0||thread_count>MAX_THREADS||queue_size<=0||queue_size>MAX_QUEUE)
        goto err;
    
    pool = (threadpool_t *)malloc(sizeof(threadpool_t));
    if(!pool) return NULL;//malloc失败直接返回
    
    //initialize
    pool->thread_count = 0;
    pool->queue_size = queue_size;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = pool->started = 0;
    //分配 count个线程
    pool->threads = (pthread_t *)calloc(thread_count, sizeof(pthread_t));
    pool->queue = (threadpool_task_t*)calloc(queue_size, sizeof(threadpool_task_t));

    //locak and conditional
    if((pthread_mutex_init(&pool->lock,NULL)!=0)
        || (pthread_cond_init(&(pool->notify),NULL)!=0)
        || pool->threads ==NULL || pool->queue ==NULL)
        goto err;

    //start worker
    for(i=0;i<thread_count;i++){
        if(pthread_create(&(pool->threads[i]),NULL,
                        threadpool_thread,(void*)pool)!=0)
        {
            //如果出错则清理
            threadpool_destroy(pool,0);
            return NULL;
        }
        pool->thread_count+=1;
        pool->started+=1;
    }

    return pool;

    err:
        if(pool)
            threadpool_free(pool);
        return NULL;
}

//add a thread
int threadpool_add(threadpool_t *pool,void(*function)(void*),
                    void *arg, int flags)
{
    int err = 0;
    int next;
    if(!pool || !function)
        return threadpool_invalid;
    if(pthread_mutex_lock(&(pool->lock))!=0)
        return threadpool_lock_failure;
    
    next = (pool->tail+1)%pool->queue_size;

    do{
        if(pool->count == pool->queue_size){
            err = threadpool_queue_full;
            break;
        }else if(pool->shutdown){
            err = threadpool_shutdown;
            break;
        }

        pool->queue[pool->tail].function = function;
        pool->queue[pool->tail].args = arg;
        pool->tail = next;
        pool->count+=1;

        //broadcast cond
        if(pthread_cond_signal(&pool->notify)!=0){
            err = threadpool_lock_failure;
            break;
        }
    }while(0);

    if(pthread_mutex_unlock(&pool->lock) != 0) {
        err = threadpool_lock_failure;
    }

    return err;
}

int threadpool_destroy(threadpool_t* pool, int flags){
    int i=0;
    int err = 0;
    if(!pool)
        return threadpool_invalid;
    if(pthread_mutex_lock(&(pool->lock))!=0)
        return threadpool_lock_failure;

    do{
        if(pool->shutdown){
            err = threadpool_shutdown;
            break;
        }

        pool->shutdown = (flags & threadpool_graceful)?\
        graceful_shutdown:immediate_shutdown;

        //wake up worker
        if((pthread_cond_broadcast(&(pool->notify))!=0)||
            (pthread_mutex_unlock(&pool->lock)!=0)){
                err = threadpool_lock_failure;
                break;
            }

        //join all
        for(i=0;i<pool->thread_count;i++){
            if(pthread_join(pool->threads[i],NULL)!=0)
                err = threadpool_thread_failure;
        }

    }while(0);

    if(!err)
        threadpool_free(pool);
    return err;
}

int threadpool_free(threadpool_t* pool){
    if(pool == NULL || pool->started>0)
        return -1;
    if(pool->threads){
        free(pool->threads);
        free(pool->queue);
    }

    pthread_mutex_lock(&(pool->lock));
    pthread_mutex_destroy(&(pool->lock));
    pthread_cond_destroy(&(pool->notify));

    free(pool);
    return 0;
}


static void *threadpool_thread(void *threadpool){
    threadpool_t* pool = (threadpool_t*)threadpool;
    threadpool_task_t task;

    for(;;){
        pthread_mutex_lock(&(pool->lock));

        while((pool->count==0)&&(!pool->shutdown)){
            pthread_cond_wait(&pool->notify,&pool->lock);
        }

         if((pool->shutdown == immediate_shutdown) ||
           ((pool->shutdown == graceful_shutdown) &&
            (pool->count == 0))) {
            break;
        }
        task.function = pool->queue[pool->head].function;
        task.args = pool->queue[pool->head].args;
        pool->head = (pool->head + 1) % pool->queue_size;
        pool->count -= 1;

        pthread_mutex_unlock(&pool->lock);

        (*(task.function))(task.args);
    }

    pool->started--;

    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);
    return(NULL);

}


int get_count(threadpool_t* pool){
    return pool->count;
}