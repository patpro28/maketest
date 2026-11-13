#include "testlib.h"
int main(int argc,char**argv){registerTestlibCmd(argc,argv);int T=inf.readInt();for(int i=0;i<T;++i){std::string x=ouf.readToken(),y=ans.readToken();if(x!=y)quitf(_wa,"Wrong factor count");}if(!ouf.seekEof())quitf(_wa,"Extra output");quitf(_ok,"Correct");}
