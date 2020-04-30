
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_THREADS 64
#define MAX_QUEUE 65536


//错误返回值
typedef enum{
    threadpool_invalid        = -1,
    threadpool_lock_failure   = -2,
    threadpool_queue_full     = -3,
    threadpool_shutdown       = -4,
    threadpool_thread_failure = -5

}threadpool_error_t;

typedef enum{
    threadpool_graceful = 1
} threadpool_destroy_flags_t;

typedef struct{
    void (*function)(void*);
    void *args;
}threadpool_task_t;

typedef struct{
  pthread_mutex_t lock;//互斥锁
  pthread_cond_t notify;
  pthread_t *threads;
  threadpool_task_t *queue;
  int thread_count;
  int queue_size;
  int head;
  int tail;
  int count;
  int shutdown;
  int started;
}threadpool_t;



int get_count(threadpool_t* pool);


threadpool_t *threadpool_create(int thread_count, int queue_size,int flags);

int threadpool_add(threadpool_t *pool,void(*routine)(void*),
                    void *arg, int flags);


int threadpool_destroy(threadpool_t* pool, int flags);


