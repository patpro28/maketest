#include "testlib.h"
int main(int argc,char** argv) {
    registerTestlibCmd(argc,argv); int n=inf.readInt(),q=inf.readInt(),count=0;
    for(int i=0;i<n;++i) inf.readLong();
    for(int i=0;i<q;++i) { int type=inf.readInt(); inf.readInt(); inf.readLong(); if(type==2) ++count; }
    for(int i=0;i<count;++i) {
        long long expected=ans.readLong(),actual=ouf.readLong();
        if(actual!=expected) quitf(_wa,"Wrong answer at query %d",i+1);
    }
    if(!ouf.seekEof()) quitf(_wa,"Extra output");
    quitf(_ok,"All answers match");
}
