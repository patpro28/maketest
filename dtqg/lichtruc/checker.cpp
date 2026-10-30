#include "testlib.h"
int main(int argc,char** argv) {
    registerTestlibCmd(argc,argv);
    long long expected=ans.readLong(), actual=ouf.readLong();
    if(actual!=expected) quitf(_wa,"Wrong maximum score");
    if(!ouf.seekEof()) quitf(_wa,"Extra output");
    quitf(_ok,"Answer matches");
}
