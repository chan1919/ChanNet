/**
 * @file Buffer.cc
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Buffer.h"

#include <iostream>
#include <string>

namespace ChanNet
{

void Buffer::Append(const char* str, ssize_t size) {
    for (ssize_t i =0; i < size; i++) {
        if (str[i] == '\0') break;
        buf_.push_back(str[i]);
    }
}

ssize_t Buffer::Size() { return buf_.size(); }

const char* Buffer::ToStr() { return buf_.c_str(); }

void Buffer::Clear() { buf_.clear(); }

void Buffer::getLine() { this->Clear(); std::getline(std::cin, buf_); }

void Buffer::setBuffer(const char* buf) {
    buf_.clear();
    buf_.append(buf);
}

}