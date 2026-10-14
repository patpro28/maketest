#include "testlib.h"
int main(int argc,char **argv) {
    registerTestlibCmd(argc,argv); int count=0;
    while(!ans.seekEof()) {
        std::string expected=ans.readToken(),actual=ouf.readToken(); ++count;
        if(expected!=actual) quitf(_wa,"Token %d differs: expected %s, found %s",count,compress(expected).c_str(),compress(actual).c_str());
    }
    if(!ouf.seekEof()) quitf(_wa,"Extra output");
    quitf(_ok,"All %d tokens match",count);
}
