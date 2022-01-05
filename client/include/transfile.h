#ifndef __TRANSFILE_H__
#define __TRANSFILE_H__

#include "head.h"

typedef struct{
    int data_len;
    char buf[1020];
}Train;

// 发送一个文件
int sendFile(int client_fd);

// 接收一个文件
int recvFile(int client_fd);

#endif
