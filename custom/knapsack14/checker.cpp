#include "testlib.h"
int main(int argc,char **argv) {
    registerTestlibCmd(argc,argv);
    std::string expected=ans.readToken(),actual=ouf.readToken();
    if(actual!=expected) quitf(_wa,"Answer differs: expected %s, found %s",compress(expected).c_str(),compress(actual).c_str());
    if(!ouf.seekEof()) quitf(_wa,"Extra output");
    quitf(_ok,"Answer matches");
}
