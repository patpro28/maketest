#include "testlib.h"
int main(int argc,char**argv){registerTestlibCmd(argc,argv);for(int i=0;i<2;++i){long long x=ouf.readLong(),y=ans.readLong();if(x!=y)quitf(_wa,"Wrong turn count");}if(!ouf.seekEof())quitf(_wa,"Extra output");quitf(_ok,"Correct");}
