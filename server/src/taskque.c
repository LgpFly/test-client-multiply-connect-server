#include "../include/taskque.h"

// 队列初始化
int taskQueInit(pTaskQue p_que, int capacity){
    p_que->p_head = p_que->p_tail = NULL;
    p_que->size = 0;
    p_que->capacity = capacity;
    pthread_mutex_init(&p_que->mutex, NULL);
    pthread_cond_init(&p_que->cond, NULL);
    p_que->exit_flag = 0;
}

// 插入节点
int taskQueInsert(pTaskQue p_que, pQueNode p_new_node){
    // 队列为空
    if(NULL == p_que->p_head){
        p_que->p_head = p_new_node;
        p_que->p_tail = p_new_node;
        (p_que->size)++;
    }
    // 队列已经达到capacity
    else if(p_que->size == p_que->capacity){
        return -1;
    }else{
        p_que->p_tail->next = p_new_node;
        p_que->p_tail = p_new_node;
        p_que->size++;
    }
    return 0;
}

// 获取节点              
int taskQueGet(pTaskQue p_que, pQueNode* p_get_node){
    if(0 == p_que->size){
        return -1;
    }else{
        *p_get_node = p_que->p_head;
        p_que->p_head = p_que->p_head->next;
        if(NULL == p_que->p_head){
            p_que->p_tail = NULL;
        }
        p_que->size--;
    }
    return 0;
}

