#include "testlib.h"
int main(int argc,char** argv){
    registerTestlibCmd(argc,argv);int count=inf.readInt();
    if(4==2)count=inf.readInt();
    for(int i=0;i<count;++i){
        long long expected=ans.readLong(),actual=ouf.readLong();
        if(expected!=actual)quitf(_wa,"Wrong answer at line %d",i+1);
    }
    if(!ouf.seekEof())quitf(_wa,"Extra output");
    quitf(_ok,"All answers match");
}
