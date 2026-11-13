#include "testlib.h"
int main(int argc,char **argv) {
    registerTestlibCmd(argc,argv);
    int count=0;
    while(!ans.seekEof()) {
        long long expected=ans.readLong(),actual=ouf.readLong();
        if(expected!=actual) quitf(_wa,"Token %d: expected %lld, found %lld",count+1,expected,actual);
        ++count;
    }
    if(!ouf.seekEof()) quitf(_wa,"Extra output");
    quitf(_ok,"%d tokens match",count);
}
