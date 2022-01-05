#ifndef __TASKQUE_H__
#define __TASKQUE_H__

#include "head.h"

// 任务队列的节点
typedef struct node{
    int client_fd;          // 客户端fd
    struct node* next;      // 指向下一个节点的指针
}QueNode, *pQueNode;

// 队列
typedef struct{
    pQueNode p_head, p_tail;            // 队头和队尾
    int size;                           // 队列长度
    int capacity;                       // 队列最大长度
    pthread_mutex_t mutex;              // 控制队列读取的锁
    pthread_cond_t cond;                // 主线程通知子线程的信号量
    short exit_flag;
}TaskQue, *pTaskQue;

// 队列初始化
int taskQueInit(pTaskQue, int);
// 插入节点
int taskQueInsert(pTaskQue, pQueNode);
// 获取节点
int taskQueGet(pTaskQue, pQueNode*);

#endif
