#include "testlib.h"
int main(int argc,char **argv) {
    registerTestlibCmd(argc,argv);
    long long expected=ans.readLong(-1LL,200000000000LL,"answer");
    long long actual=ouf.readLong(-1LL,200000000000LL,"answer");
    if(actual!=expected) quitf(_wa,"Expected %lld, found %lld",expected,actual);
    if(!ouf.seekEof()) quitf(_wa,"Extra output");
    quitf(_ok,"Minimum energy matches");
}
