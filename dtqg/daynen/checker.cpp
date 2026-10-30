#include "testlib.h"
int main(int argc,char** argv) {
    registerTestlibCmd(argc,argv); int count=inf.readInt();
    for(int i=0;i<count;++i) {
        long long expected=ans.readLong(),actual=ouf.readLong();
        if(actual!=expected) quitf(_wa,"Wrong answer at sequence %d",i+1);
    }
    if(!ouf.seekEof()) quitf(_wa,"Extra output");
    quitf(_ok,"All answers match");
}
