/**
 * @file EventLoop.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <functional>

#include "noncopyable.h"

namespace ChanNet
{
class Poller;
class Channel;
class EventLoop: noncopyable{
public:
    EventLoop();
    ~EventLoop();

    void loop();
    void updateChannel(Channel* ch);
    void deleteChannel(Channel* ch);
    void quit();
private:
    Poller *poller_ { nullptr };
    bool quit_ { false };
};
}