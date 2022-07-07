/**
 * @file InetAddress.cc
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <cstring>
#include "InetAddress.h"

InetAddress::InetAddress(const char *ip, uint16_t port) {
  memset(&addr_, 0, sizeof(addr_));
  addr_.sin_family = AF_INET;
  addr_.sin_addr.s_addr = inet_addr(ip);
  addr_.sin_port = htons(port);
}

void InetAddress::setAddr(sockaddr_in addr) { addr = addr_; }
sockaddr_in InetAddress::getAddr() { return addr_; }
// inet_ntoa 将一个32位网络字节序的二进制IP地址转换成相应的点分十进制的IP地址
const char* InetAddress::getIp() { return inet_ntoa(addr_.sin_addr); }
// ntohs 将一个16位数由网络字节顺序转换为主机字节顺序
uint16_t InetAddress::getPort() { return ntohs(addr_.sin_port); }