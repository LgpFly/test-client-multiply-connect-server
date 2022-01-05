#include "../include/head.h"
#include "../include/transfile.h"


void* threadFund(void* p_arg){
    int ret;
    int con_flag = 1;
    struct sockaddr_in* cli_child_addr = (struct sockaddr_in*)p_arg; 
    int child_fd = socket(AF_INET, SOCK_STREAM, 0);

    ret = connect(child_fd, (struct sockaddr*)cli_child_addr, sizeof(struct sockaddr_in));
    ERROR_CHECK(ret, -1, "connect");
    ret = send(child_fd, &con_flag, 4, 0);
    ERROR_CHECK(ret, -1, "send con_flag");
    ret = recvFile(child_fd);
    if(-1 == ret){
#ifdef _DEBUG
        printf("server fly\n");
#endif
    }
    if(0 == ret){
        printf("download file success\n");
    }
    
}


int main(int argc, char **argv){
    ARGS_CHECK(argc, 3);
    int con_flag = -1;
    int ret;
    int socket_fd;
    char buf[10];
    bzero(buf, sizeof(buf));
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socket_fd, -1, "socket");

    struct sockaddr_in cli_addr;
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(atoi(argv[2]));
    cli_addr.sin_addr.s_addr = inet_addr(argv[1]);
    
    ret = connect(socket_fd, (struct sockaddr*)&cli_addr, sizeof(cli_addr));
    ERROR_CHECK(ret, -1, "connect");
    ret = send(socket_fd, &con_flag, 4, 0);
    ERROR_CHECK(ret, -1, "send con_flag");
    pthread_t pid;
    pthread_create(&pid, NULL, threadFund, &cli_addr);
    char zimu[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for(int i = 0; i < 50; ++i){
        ret = send(socket_fd, zimu, 26, 0);
        ERROR_CHECK(ret, -1, "send zimu");
    }

    while(1){
        
    }
   // ret = recvFile(socket_fd);
   // if(-1 == ret){
// #ifdef _DEBUG
   //     printf("server fly\n");
// #endif
   // }
   // if(0 == ret){
   //     printf("download file success\n");
   // }
    
}
