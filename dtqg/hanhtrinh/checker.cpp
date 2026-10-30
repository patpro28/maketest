#include "testlib.h"
#include <string>
int main(int argc,char** argv) {
    registerTestlibCmd(argc,argv);
    std::string expected=ans.readToken();
    if(expected=="IMPOSSIBLE") {
        std::string actual=ouf.readToken();
        if(actual!=expected) quitf(_wa,"Expected IMPOSSIBLE");
    } else {
        long long value=ouf.readLong();
        if(value!=std::stoll(expected)) quitf(_wa,"Wrong maximum score");
    }
    if(!ouf.seekEof()) quitf(_wa,"Extra output");
    quitf(_ok,"Answer matches");
}
