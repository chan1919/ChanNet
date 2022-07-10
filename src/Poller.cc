/**
 * @file Poller.cc
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Poller.h"
#include "Channel.h"
#include "Socket.h"
#include "util.h"

#include <unistd.h>
#include <cstring>

#define MAX_EVENTS 1001

namespace ChanNet
{

Poller::Poller() {
    fd_ = epoll_create1(0);
    ErrorIf(fd_ == -1, "epoll create error!");
    events_ = new epoll_event[MAX_EVENTS];
    memset(events_, 0, sizeof(*events_) * MAX_EVENTS);
}

Poller::~Poller() {
    if (fd_ != -1) {
        close(fd_);
    }
    delete[] events_;
}

std::vector<Channel*> Poller::Poll(int timeout) {
    std::vector<Channel*> active_channels;
    int nfs = epoll_wait(fd_, events_, MAX_EVENTS, timeout);
    ErrorIf(nfs == -1, "epoll_wait error!");
    for (int i = 0; i < nfs; i++) {
        Channel* ch = (Channel*) events_[i].data.ptr;
        int events = events_[i].events;
        if (events & EPOLLIN) {
            ch->setReadyEvents(Channel::READ_EVENT);
        }
        if (events & EPOLLOUT) {
            ch->setReadyEvents(Channel::WRITE_EVENT);
        }
        if (events & EPOLLET ) {
            ch->setReadyEvents(Channel::ET);
        }
        active_channels.push_back(ch);
    }
    return active_channels;
}

void Poller::updateChannel(Channel* ch) {
    int sockfd = ch->getSocket()->getFd();
    epoll_event ev {};
    ev.data.ptr = ch;

    if (ch->getListenEvents() & Channel::READ_EVENT) {
        ev.events |= EPOLLIN | EPOLLPRI;
    }
    if (ch->getListenEvents() & Channel::WRITE_EVENT) {
        ev.events |= EPOLLOUT;
    }
    if (ch->getListenEvents() & Channel::ET) {
        ev.events |= EPOLLET;
    }
    if (!ch->getExist()) {
        ErrorIf(epoll_ctl(fd_, EPOLL_CTL_ADD, sockfd, &ev) == -1, "epoll add error!");
    }else {
        ErrorIf(epoll_ctl(fd_, EPOLL_CTL_MOD, sockfd, &ev) == -1, "epoll modify error!");
    }
}

void Poller::deteteChannel(Channel* ch) {
    int sockfd = ch->getSocket()->getFd();
    ErrorIf(epoll_ctl(fd_, EPOLL_CTL_DEL, sockfd, nullptr) == -1, "epoll delete error!");
    ch->setExist(false);
}

}