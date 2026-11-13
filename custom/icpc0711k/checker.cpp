#include "testlib.h"
#include <string>
using namespace std;
int main(int argc,char**argv) {
    registerTestlibCmd(argc,argv);
    int cnt=0;
    while(!ans.seekEof()) {
        string expected=ans.readToken();
        if(ouf.seekEof())quitf(_wa,"Missing token");
        string got=ouf.readToken();
        if(got!=expected)quitf(_wa,"Token %d differs",cnt+1);
        ++cnt;
    }
    if(!ouf.seekEof())quitf(_wa,"Extra output");
    quitf(_ok,"%d tokens",cnt);
}
