/**
 * @file Acceptor.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-11
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
class Acceptor: noncopyable{
public:
    explicit Acceptor(EventLoop* loop);
    ~Acceptor();

    void AcceptConnection();
    void setNewConnectionCallback( std::function<void(Socket*)> const& callback);
private:
    EventLoop* loop_;
    Socket* sock_;
    Channel* channel_;
    std::function<void(Socket*)> new_connection_callback_;
};

}