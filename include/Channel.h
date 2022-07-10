/**
 * @file Channel.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 */

#pragma

#include <functional>
#include "noncopyable.h"

namespace ChanNet
{

class EventLoop;
class Socket;

class Channel: noncopyable {
public:
    Channel(EventLoop* loop, Socket* socket);
    ~Channel();

    void HandleEvent();
    void EnableRead();
    void EnableWrite();

    Socket* getSocket();
    int getListenEvents();
    int getReadyEvents();
    bool getExist();
    void setExist(bool in = true);
    void setET();

    void setReadyEvents(int ev);

    void setReadCallback(std::function< void()> const& callback);
    void setWriteCallback(std::function< void()> const& callback);

    static const int READ_EVENT;
    static const int WRITE_EVENT;
    static const int ET;

private:
    EventLoop* loop_;
    Socket* socket_;
    int listen_events_ {0};
    int ready_events_ {0};
    bool exist_ {false};

    std::function< void() >read_callback_;
    std::function< void() >write_callback_;
};

}