/**
 * @file InetAddress.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <arpa/inet.h>

#include "noncopyable.h"

/**
 * 封装IP类相关操作
 */
namespace ChanNet{
class InetAddress{
public:

    InetAddress() = default;
    InetAddress(const char* ip, uint16_t port);
    ~InetAddress() = default;
    
    void setAddr(sockaddr_in addr);
    sockaddr_in getAddr();
    const char* getIp();
    uint16_t getPort();

private:
    struct sockaddr_in addr_ {};
};

} //namespace ChanNet