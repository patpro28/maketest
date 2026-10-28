#include "testlib.h"
int main(int argc,char **argv) {
    registerTestlibCmd(argc,argv);
    int count = 0;
    while (!ans.seekEof()) {
        long long expected = ans.readLong(),actual = ouf.readLong();
        ++count;
        if (actual != expected)
            quitf(_wa,"At token %d: expected %lld, found %lld",count,expected,actual);
    }
    if (!ouf.seekEof()) quitf(_wa,"Extra output");
    quitf(_ok,"%d values match",count);
}
