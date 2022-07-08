/**
 * @file util_test.cc
 * @author czy (suoni1919@gmail.com)
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "util.h"


int main () {
    //ChanNet::ErrorIf (true, "True [TEST] message!\n");
    ChanNet::ErrorIf (false, "False [TEST] message!\n");
    const char* s1 = "TEST";
    ChanNet::EQ_STR_ASSERT(s1, "TEST");
    return EXIT_SUCCESS;
}