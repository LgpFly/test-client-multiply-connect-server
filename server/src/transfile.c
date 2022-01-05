#include "../include/transfile.h"

#define FILE file
int sendFile(int client_fd){
    int ret;
    int read_num;
    // 先定义小火车的数据结构
    Train train;
    bzero(&train, sizeof(train));
   
    // 先发送文件名
    train.data_len = 4;
    strcpy(train.buf, "file");
    ret = send(client_fd, &train, 4 + train.data_len, 0);
    if(-1 == ret){
#ifdef _DEBUG
        printf("client fly\n");
#endif
        close(client_fd);
        return -1;
    }
    //ERROR_CHECK(ret, -1, "send(name)");
    // 发送文件大小
    int file_fd = open("file", O_RDWR);
    struct stat file_stat;
    ret = fstat(file_fd, &file_stat);
    bzero(&train, sizeof(train));
    train.data_len = sizeof(file_stat.st_size);
    memcpy(train.buf, &file_stat.st_size, sizeof(file_stat.st_size));
    ret = send(client_fd, &train, 4 + train.data_len, 0);
    if(-1 == ret){
#ifdef _DEBUG
        printf("client fly\n");
#endif
        close(file_fd);
        close(client_fd);
        return -1;
    }
    //ERROR_CHECK(ret, -1, "send(file_size)");

    // 发送文件内容
    off_t file_total_len = file_stat.st_size;
    off_t already_send = 0;
    while(already_send < file_total_len){
        bzero(&train, sizeof(train));
        read_num = read(file_fd, train.buf, sizeof(train.buf));
        ERROR_CHECK(read_num, -1, "read");
        train.data_len = read_num;
        ret = send(client_fd, &train, 4 + train.data_len, 0);
        if(-1 == ret){
#ifdef _DEBUG
            printf("client fly\n");
#endif
            close(file_fd);
            close(client_fd);
            return -1;
    }
        //ERROR_CHECK(ret, -1, "send(file_size)");
        already_send += read_num;
    }
    close(file_fd);
    close(client_fd);
    return 0;
}

