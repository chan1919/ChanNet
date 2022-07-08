/**
 * @file Buffer.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <string>
#include "noncopyable.h"

namespace ChanNet 
{

class Buffer: noncopyable {
public:
    Buffer() = default;
    ~Buffer() = default;

    void Append(const char* _str, ssize_t _size);
    ssize_t Size();
    const char* ToStr();
    void Clear();
    void getLine();
    void setBuffer(const char* buf);

private:
    std::string buf_;
}; 

} //namespace 