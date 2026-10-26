#include "testlib.h"
int main(int argc,char**argv){
    registerTestlibCmd(argc,argv);int count=0;
    while(!ans.seekEof()){
        std::string expected=ans.readToken(),actual=ouf.readToken();
        if(expected!=actual)quitf(_wa,"Wrong token %d: expected %s, found %s",count+1,expected.c_str(),actual.c_str());
        ++count;
    }
    if(!ouf.seekEof())quitf(_wa,"Extra output");
    quitf(_ok,"%d tokens match",count);
}
