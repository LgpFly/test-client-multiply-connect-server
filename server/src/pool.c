#include "../include/pool.h"
#include "../include/transfile.h"
// 线程池初始化 线程池，线程数量， 队列capacity
int threadPoolInit(pThreadPool p_thread_pool, int thread_num, int task_que_capacity){
    // 结构体使用之前先memset一下
    bzero(p_thread_pool, sizeof(ThreadPool));
    //taskQueInit(&(p_thread_pool->task_que), task_que_capacity);
    taskQueInit(&p_thread_pool->task_que, task_que_capacity);
    p_thread_pool->thread_num = thread_num;
    p_thread_pool->pthid = (pthread_t*)calloc(thread_num, sizeof(pthread_t));
    p_thread_pool->start_flag = 0;
    return 0;
}

// 线程函数
void* threadFunc(void* p_arg){
    int ret;
    pTaskQue p_task_que = (pTaskQue)p_arg;
    pQueNode p_one_node = NULL;
    while(1){
        pthread_mutex_lock(&(p_task_que->mutex));
        if(0 == p_task_que->size){
#ifdef _DEBUG
            printf("wait\n");
#endif
            pthread_cond_wait(&(p_task_que->cond), &(p_task_que->mutex));
#ifdef _DEBUG
            printf("wake up\n");
#endif
        }
        // 取一个任务
        ret = taskQueGet(p_task_que, &p_one_node);
        pthread_mutex_unlock(&(p_task_que->mutex));
        
        if(0 == ret){
        // 正常是传文件
            ret = sendFile(p_one_node->client_fd);
            if(ret == -1){
#ifdef _DEBUG
                printf("send file fail\n");
#endif
            }
        }
        free(p_one_node);
        p_one_node = NULL;
        
        if(1 == p_task_que->exit_flag){
#ifdef _DEBUG
            printf("thread exit\n");
#endif
            pthread_exit(NULL);
        }
    }
}


// 线程池启动
int threadPoolStart(pThreadPool p_thread_pool){
    if(0 == p_thread_pool->start_flag){
        for(int i = 0; i < p_thread_pool->thread_num; i++){
            pthread_create((p_thread_pool->pthid) + i, NULL, threadFunc, &(p_thread_pool->task_que));
        }
        p_thread_pool->start_flag = 1;
    }
    return 0;
}


