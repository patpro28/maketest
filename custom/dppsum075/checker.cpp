#include "testlib.h"
int main(int argc,char **argv) {
    registerTestlibCmd(argc,argv);
    int count=0;
    while(!ans.seekEof()) {
        long long expected=ans.readLong();
        long long actual=ouf.readLong();
        if(actual!=expected) quitf(_wa,"Integer %d differs",count+1);
        ++count;
    }
    if(!ouf.seekEof()) quitf(_wa,"Extra output");
    quitf(_ok,"%d integers match",count);
}
