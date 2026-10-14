#include "testlib.h"
int main(int argc,char* argv[]) {
    registerTestlibCmd(argc,argv);
    long long expected=ans.readLong(0LL,250500250000LL);
    long long actual=ouf.readLong(0LL,250500250000LL);
    if (!ouf.seekEof()) quitf(_wa,"Extra output");
    if (actual!=expected) quitf(_wa,"Expected %lld, found %lld",expected,actual);
    quitf(_ok,"Answer is %lld",actual);
}
