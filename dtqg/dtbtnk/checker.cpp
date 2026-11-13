#include "testlib.h"
int main(int argc,char**argv){registerTestlibCmd(argc,argv);long long x=ouf.readLong(),y=ans.readLong();if(x!=y)quitf(_wa,"Wrong value");if(!ouf.seekEof())quitf(_wa,"Extra output");quitf(_ok,"Correct");}
