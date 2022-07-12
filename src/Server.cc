/**
 * @file Server.cc
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Server.h"
#include <unistd.h>
#include <functional>
#include "Acceptor.h"
#include "Connection.h"
#include "EventLoop.h"
#include "Socket.h"
#include "ThreadPool.h"
#include "util.h"
namespace ChanNet
{

Server::Server(EventLoop *loop) : main_reactor_(loop), acceptor_(nullptr), thread_pool_(nullptr) {
  if(main_reactor_ == nullptr){
    ErrorIf(1, "main_reactor error");
  }
  acceptor_ = new Acceptor(main_reactor_);
  std::function<void(Socket *)> cb = std::bind(&Server::NewConnection, this, std::placeholders::_1);
  acceptor_->setNewConnectionCallback(cb);

  int size = static_cast<int>(std::thread::hardware_concurrency());
  thread_pool_ = new ThreadPool(size);
  for (int i = 0; i < size; ++i) {
    sub_reactors_.push_back(new EventLoop());
  }

  for (int i = 0; i < size; ++i) {
    std::function<void()> sub_loop = std::bind(&EventLoop::loop, sub_reactors_[i]);
    thread_pool_->addTask(std::move(sub_loop));
  }
}

Server::~Server() {
  for(EventLoop *each : sub_reactors_){
    delete each;
  }
  delete acceptor_;
  delete thread_pool_;
}

void Server::NewConnection(Socket *sock) {
  if(sock->getFd() == -1){
    ErrorIf(1, "New Connection error, invalid client socket!");
  }
  // ErrorIf(sock->GetFd() == -1, "new connection error");
  uint64_t random = sock->getFd() % sub_reactors_.size();
  Connection *conn = new Connection(sub_reactors_[random], sock);
  std::function<void(Socket *)> cb = std::bind(&Server::DeleteConnection, this, std::placeholders::_1);
  conn->SetDeleteConnectionCallback(cb);
  conn->SetOnConnectCallback(on_connect_callback_);
  connections_[sock->getFd()] = conn;
  new_connect_callback_(conn);
}

void Server::DeleteConnection(Socket *sock) {
  int sockfd = sock->getFd();
  auto it = connections_.find(sockfd);
  if (it != connections_.end()) {
    Connection *conn = connections_[sockfd];
    connections_.erase(sockfd);
    delete conn;
    conn = nullptr;
  }
}

void Server::OnConnect(std::function<void(Connection *)> fn) { on_connect_callback_ = std::move(fn); }

void Server::NewConnect(std::function<void(Connection *)> fn) { new_connect_callback_ = std::move(fn); }
}
