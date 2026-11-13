#include "testlib.h"
int main(int argc,char**argv){registerTestlibCmd(argc,argv);std::string x=ouf.readToken(),y=ans.readToken();if(x!=y)quitf(_wa,"Wrong classification");if(!ouf.seekEof())quitf(_wa,"Extra output");quitf(_ok,"Correct");}
