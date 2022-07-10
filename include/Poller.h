/**
 * @file Poller.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma
#include <vector>
#include <sys/epoll.h>

#include "noncopyable.h"

namespace ChanNet
{

class Channel;

class Poller: noncopyable{
public:
    Poller();
    ~Poller();

    void updateChannel( Channel* ch);
    void deteteChannel( Channel* ch);

    std::vector< Channel* > Poll(int time = -1);

private:
    int fd_ {-1};
    epoll_event* events_ {nullptr};
};

}