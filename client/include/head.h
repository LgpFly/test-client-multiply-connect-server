#ifndef __HEAD_H__
#define __HEAD_H__

#define _DEBUG
#define _GUN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include <setjmp.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <sys/shm.h>
#include <sys/epoll.h>

// 进行参数检查的宏定义
#define ARGS_CHECK(argc, val) {if(argc != val) {printf("error args\n"); return -1;}}

// 函数返回值检查的宏定义
#define ERROR_CHECK(ret, ret_val, func_name){if(ret == ret_val) perror(func_name);}


#endif
