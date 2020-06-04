#include "thread_pool.h"

void handler(void *arg)
{
    //响应取消请求之后自动处理例程,释放互斥锁
    pthread_mutex_unlock((pthread_mutex_t *)arg);
}

