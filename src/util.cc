/**
 * @file util.cc
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <cstdio>
#include <cstdlib>

#include "util.h"

// 打印错误信息
void ErrorIf(bool condition, const char* msg) {
    if (condition) {
        perror (msg);
        exit(EXIT_FAILURE);
    }
}

void EQ_ASSRET(bool condition, const char* msg) {
    if (!condition) {
        perror (msg);
        exit(EXIT_FAILURE);
    }
}
