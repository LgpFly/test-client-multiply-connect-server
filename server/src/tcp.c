#include "../include/tcp.h"

int tcpInit(int *sock_fd, char *ip, char *port){
    
    *sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(*sock_fd, -1, "socket");
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = inet_addr(ip);
    int ret;
    ret = bind(*sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    ERROR_CHECK(ret, -1, "bind");
    ret = listen(*sock_fd, 10);
    ERROR_CHECK(ret, -1, "listen");
}
