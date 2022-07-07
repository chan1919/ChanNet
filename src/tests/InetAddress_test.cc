/**
 * @file InetAddress_test.cc
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "InetAddress.h"
#include "util.h"

#include <iostream>

int main () {
    //case 1
    InetAddress addr_1 ("0.0.0.0", 4399);
    ChanNet::EQ_ASSERT( addr_1.getPort() == 4399 , "Port error!");
}