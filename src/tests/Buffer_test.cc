#include "Buffer.h"
#include "util.h"

int main () {
    ChanNet::Buffer buf;
    buf.Append("test buffer", 12);
    ChanNet::EQ_STR_ASSERT("test buffer", buf.ToStr());
    buf.Clear();
    ChanNet::EQ_STR_ASSERT("", buf.ToStr());
    ChanNet::EQ_STR_ASSERT("\0", buf.ToStr());
    //ERROR!
    //ChanNet::EQ_STR_ASSERT(NULL, buf.ToStr());
    return EXIT_SUCCESS;
}