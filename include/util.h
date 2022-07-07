/**
 * @file util.h
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 工具类 错误状态->输出错误信息
 */

#pragma once
namespace ChanNet
{
    void ErrorIf (bool condition, const char* msg);

    void EQ_ASSERT(bool condition, const char* msg);
    
}