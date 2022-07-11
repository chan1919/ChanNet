/**
 * @file Acceptor.cc
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Channel.h"
#include "Socket.h"
#include "Acceptor.h"
#include <utility>

namespace ChanNet
{

Acceptor::Acceptor(EventLoop* loop): loop_(loop), sock_(nullptr), channel_(nullptr) {
    sock_ = new Socket();
    InetAddress* addr = new InetAddress("0.0.0.0", 8888);
    sock_->Bind(addr);
    sock_->Listen();
    channel_ = new Channel(loop_, sock_);
    std::function<void()> cb = std::bind(&Acceptor::AcceptConnection, this);
    channel_->setReadCallback(cb);
    channel_->EnableRead();
    delete addr;
}

Acceptor::~Acceptor() {
    delete channel_;
    delete sock_;
}

void Acceptor::AcceptConnection() {
    InetAddress* clnt_addr = new InetAddress();
    Socket* clnt_sock = new Socket(sock_->Accept(clnt_addr));
    clnt_sock->setNonBlocking();
    new_connection_callback_(clnt_sock);
    delete clnt_addr;
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket*)> const& callback) {
    new_connection_callback_ = callback;
}

}