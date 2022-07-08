/**
 * @file Socket.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include "noncopyable.h"
#include "InetAddress.h"
namespace ChanNet{
/**
 * 对socket系统调用封装
 */
class Socket: noncopyable {
private:
    int fd_ {-1};

public:
    Socket();
    explicit Socket(int fd);
    ~Socket();

    void Bind(InetAddress* addr);
    void Listen();
    int Accept(InetAddress* addr);

    void Connect(InetAddress* addr);
    void Connect(const char* ip, uint16_t port);

    //设置无阻塞socket
    void setNonBlocking();
    bool isNonBlocking();
    int getFd();
};

} //namespace ChanNet