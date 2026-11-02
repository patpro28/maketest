#include "testlib.h"
int main(int argc,char**argv){
    registerTestlibCmd(argc,argv);int n=inf.readInt();
    for(int i=0;i<n;++i){int expected=ans.readInt(),actual=ouf.readInt(1,n,"athlete");
        if(expected!=actual)quitf(_wa,"Wrong athlete at position %d: expected %d, found %d",i+1,expected,actual);
    }
    if(!ouf.seekEof())quitf(_wa,"Extra output");quitf(_ok,"The standard order matches");
}
