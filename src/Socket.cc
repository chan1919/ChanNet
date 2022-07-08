/**
 * @file Socket.cc
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>

#include "Socket.h"
#include "util.h"

namespace ChanNet
{

Socket::Socket() {
    fd_ = socket( AF_INET, SOCK_STREAM, 0);
    ErrorIf(fd_ == -1, "Socket create error!\n");
}

Socket::Socket(int fd) : fd_(fd) {
    ErrorIf(fd_ == -1, "Socket create error!\n");
}

Socket::~Socket() {
    if (fd_ != -1) close(fd_);
}

void Socket::Bind (InetAddress* addr) {
    struct sockaddr_in tem_addr = addr->getAddr();
    ErrorIf( bind(fd_, (sockaddr*)&tem_addr, sizeof(tem_addr)) == -1, "bind addr and socket error!");
}

void Socket::Listen() {
    ErrorIf (listen(fd_, SOMAXCONN) == -1, "socket listen error!");
}

void Socket::setNonBlocking() { fcntl(this->fd_, F_SETFL, fcntl(this->fd_, F_GETFL) | O_NONBLOCK); }

bool Socket::isNonBlocking() { return (fcntl(fd_, F_GETFL) & O_NONBLOCK) != 0; }

int Socket::Accept(InetAddress* addr) {
    int clnt_sockfd = -1;
    sockaddr_in tem_addr {};
    socklen_t addr_len = sizeof(tem_addr);
    if (isNonBlocking()) {
        while (true) {
            clnt_sockfd = accept(fd_, (sockaddr*)&tem_addr, &addr_len);
            if (clnt_sockfd == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {
                continue;
            }
            if (clnt_sockfd == -1) {
                ErrorIf(true, "socket accept error!");
            } else {
                break;
            } 

        }
    }else {
        clnt_sockfd = accept(fd_, (sockaddr*)&tem_addr, &addr_len);
        ErrorIf(clnt_sockfd == -1, "socket accept error!");
    }
    addr->setAddr(tem_addr);
    return clnt_sockfd;
}



}// namespace
