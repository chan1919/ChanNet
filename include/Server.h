/**
 * @file Server.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <functional>
#include <map>
#include <vector>
#include "noncopyable.h"
namespace ChanNet
{
class EventLoop;
class Socket;
class Acceptor;
class Connection;
class ThreadPool;
class Server: noncopyable {
 private:
  EventLoop *main_reactor_;
  Acceptor *acceptor_;
  std::map<int, Connection *> connections_;
  std::vector<EventLoop *> sub_reactors_;
  ThreadPool *thread_pool_;
  std::function<void(Connection *)> on_connect_callback_;
  std::function<void(Connection *)> new_connect_callback_;

 public:
  explicit Server(EventLoop *loop);
  ~Server();

  void NewConnection(Socket *sock);
  void DeleteConnection(Socket *sock);
  void OnConnect(std::function<void(Connection *)> fn);
  void NewConnect(std::function<void(Connection *)> fn);
};
}