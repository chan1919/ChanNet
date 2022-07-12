/**
 * @file Connection.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma
#include <functional>
#include "noncopyable.h"

namespace ChanNet
{

class EventLoop;
class Socket;
class Channel;
class Buffer;
class Connection: noncopyable{
public:
    enum State{
        Invalid = 1,
        Connecting,
        Connected,
        Closed,
        Failded,
    };

    Connection(EventLoop* loop,Socket* sock);
    ~Connection();

    void Read();
    void Write();
    void Send(std::string msg);

    void SetDeleteConnectionCallback(std::function<void(Socket *)> const &callback);
  void SetOnConnectCallback(std::function<void(Connection *)> const &callback);
  State GetState();
  void Close();
  void SetSendBuffer(const char *str);
  Buffer *GetReadBuffer();
  const char *ReadBuffer();
  Buffer *GetSendBuffer();
  const char *SendBuffer();
  void GetlineSendBuffer();
  Socket *GetSocket();

  void OnConnect(std::function<void()> fn);

 private:
  EventLoop *loop_;
  Socket *sock_;
  Channel *channel_{nullptr};
  State state_{State::Invalid};
  Buffer *read_buffer_{nullptr};
  Buffer *send_buffer_{nullptr};
  std::function<void(Socket *)> delete_connectioin_callback_;

  std::function<void(Connection *)> on_connect_callback_;

  void ReadNonBlocking();
  void WriteNonBlocking();
  void ReadBlocking();
  void WriteBlocking(); 

};

}