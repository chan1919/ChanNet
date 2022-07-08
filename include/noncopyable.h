/**
 * @file noncopyable.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

namespace ChanNet{
/**
 * 这是一个基类
 * 禁止派生类的拷贝和赋值构造
 */
class noncopyable {
public:
    noncopyable(const noncopyable&) = delete;
    noncopyable &operator=(const noncopyable &) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

} //namespace ChanNet
