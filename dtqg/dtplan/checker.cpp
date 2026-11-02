#include "testlib.h"
int main(int argc,char** argv){
    registerTestlibCmd(argc,argv);
    long long expected=ans.readLong(),actual=ouf.readLong(0LL,999999999LL,"answer");
    if(expected!=actual)quitf(_wa,"Expected %lld, found %lld",expected,actual);
    if(!ouf.seekEof())quitf(_wa,"Extra output");
    quitf(_ok,"Answer matches");
}
