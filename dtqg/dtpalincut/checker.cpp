#include "testlib.h"
#include <string>
int main(int argc,char**argv){
    registerTestlibCmd(argc,argv);inf.readToken();int t=inf.readInt();
    for(int i=0;i<t;++i){std::string expected=ans.readToken(),actual=ouf.readToken();
        if(actual!=expected)quitf(_wa,"Query %d: expected %s, found %s",i+1,expected.c_str(),actual.c_str());
    }
    if(!ouf.seekEof())quitf(_wa,"Extra output");quitf(_ok,"All answers match");
}
