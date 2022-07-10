/**
 * @file Channel.cc
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Socket.h"
//eventloop TODO
#include "Channel.h"
#include "EventLoop.h"
namespace ChanNet
{

const int Channel::READ_EVENT = 1;
const int Channel::WRITE_EVENT = 2;
const int Channel::ET = 4;

Channel::Channel(EventLoop* loop, Socket* socket): loop_(loop), socket_(socket) {}
Channel::~Channel() { loop_->deleteChannel(this); }

void Channel::HandleEvent(){
    if (ready_events_ & READ_EVENT) read_callback_();
    if (ready_events_ & WRITE_EVENT) write_callback_();
}

void Channel::EnableRead() {
    listen_events_ |= READ_EVENT;
    loop_->updateChannel(this);
}

void Channel::EnableWrite() {
    listen_events_ |= WRITE_EVENT;
    loop_->updateChannel(this);
}

void Channel::setET() {
    listen_events_ |= ET;
    loop_->updateChannel(this);
}

Socket* Channel::getSocket() { return socket_; }
int Channel::getListenEvents() { return listen_events_; }
int Channel::getReadyEvents() { return ready_events_; }
bool Channel::getExist() { return exist_;}

void Channel::setExist(bool in) { exist_ = in; }

void Channel::setReadyEvents(int ev) {
    if (ev & READ_EVENT) {
        ready_events_ |= READ_EVENT;
    }
    if (ev & READ_EVENT) {
        ready_events_ |= WRITE_EVENT;
    }
    if (ev & ET) {
        ready_events_ |= ET;
    }
}

void Channel::setReadCallback( std::function<void()> const& cb) { read_callback_ = cb; }
void Channel::setWriteCallback( std::function<void()> const& cb) { write_callback_ = cb; }
}