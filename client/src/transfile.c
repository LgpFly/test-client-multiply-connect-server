#include "../include/transfile.h"

// 接收一个文件
int recvFile(int client_fd){
    int ret;
    // recv fileName
    int file_name_len;
    char file_name[50] = {0};
    ret = recv(client_fd, &file_name_len, 4, MSG_WAITALL);
    if(0 == ret){
#ifdef _DEBUG
        printf("server fly\n");
#endif
        return -1;
    }
    ret = recv(client_fd, file_name, file_name_len, MSG_WAITALL);
    if(0 == ret){
#ifdef _DEBUG
        printf("server fly\n");
#endif
        return -1;
    }

    // recv size
    int file_size_len;
    off_t file_size;
    ret = recv(client_fd, &file_size_len, 4, MSG_WAITALL);
    if(0 == ret){
#ifdef _DEBUG
        printf("server fly\n");
#endif
        return -1;
    }
    
    ret = recv(client_fd, &file_size, file_size_len, MSG_WAITALL);
    if(0 == ret){
#ifdef _DEBUG
        printf("server fly\n");
#endif
        return -1;
    }
    off_t slice = file_size / 100;


    // open file
    int file_fd;
    file_fd = open(file_name, O_RDWR|O_CREAT, 0666);
    ERROR_CHECK(file_fd, -1, "open file");

    // recv content & write file
    int recv_num = 0;
    int one_recv_num = 0;
    int last_recv_num = 0;
    char buf[1020];
    int buf_len;
    while(recv_num < file_size){
        memset(buf, 0, sizeof(buf));
        ret = recv(client_fd, &buf_len, 4, 0);
        if(0 == ret){
#ifdef _DEBUG
            printf("server fly\n");
#endif
            close(file_fd);
            return -1;
        }
        one_recv_num = recv(client_fd, buf, buf_len, MSG_WAITALL);
        if(0 == ret){
#ifdef _DEBUG
            printf("server fly\n");
#endif
            close(file_fd);
            return -1;
        }
        recv_num += one_recv_num;
        ret = write(file_fd, buf, buf_len);
        ERROR_CHECK(ret, -1, "write(content)");
        
        // 打印进度条
        if((recv_num - last_recv_num)  > slice){
            last_recv_num = recv_num;
            printf("download:%5.2f%%\r", (float)recv_num / file_size * 100);
            fflush(stdout);
        }
    }
    printf("download:100.00%%\n");
    fflush(stdout);
    
    close(file_fd);
    return 0;
}
