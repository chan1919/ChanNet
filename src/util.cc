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
#include <string.h>

#include "util.h"

// 打印错误信息
void ChanNet::ErrorIf(bool condition, const char* msg) {
    if (condition) {
        perror (msg);
        exit(EXIT_FAILURE);
    }
}

void ChanNet::EQ_ASSERT(bool condition, const char* msg){
    if (!condition) {
        perror (msg);
        exit(EXIT_FAILURE);
    }
}


void ChanNet::EQ_STR_ASSERT(const char* str_a, const char* str_b) {
    int la = strlen(str_a);
    int lb = strlen(str_b);
    if (la != lb) EQ_ASSERT(false, "EQ_STR_ASSERT error!");

    for (int i=0; i< strlen(str_a); i++) {
        if (str_a[i] != str_b[i]) EQ_ASSERT(false, "EQ_STR_ASSERT error!");
    }
}