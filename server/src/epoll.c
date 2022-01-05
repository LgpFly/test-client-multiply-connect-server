#include "../include/epoll.h"

int epollAddFd(int epfd, int client_fd){
    int ret;
    struct epoll_event ev;
    bzero(&ev, sizeof(struct epoll_event));
    ev.data.fd = client_fd;
    ev.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);
    ERROR_CHECK(ret, -1, "epoll_ctl(add)");
    return 0;
}

int epollDelFd(int epfd, int client_fd){
    int ret;
    struct epoll_event ev;
    bzero(&ev, sizeof(struct epoll_event));
    ev.data.fd = client_fd;
    ev.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, client_fd, &ev);
    ERROR_CHECK(ret, -1, "epoll_ctl(de;)");
    return 0;
}
