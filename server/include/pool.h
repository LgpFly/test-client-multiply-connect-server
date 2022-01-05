#ifndef __POOL_H__
#define __POOL_H_

#include "taskque.h"
#include "head.h"
typedef struct{
    TaskQue task_que;           // 任务队列
    pthread_t *pthid;            // 子线程id
    int thread_num;             // 线程池线程数量
    short start_flag;           // 线程池启动标志
}ThreadPool, *pThreadPool;

// 线程池初始化 线程池，线程数量， 队列capacity
int threadPoolInit(pThreadPool, int, int);
// 线程池启动
int threadPoolStart(pThreadPool);
#endif
