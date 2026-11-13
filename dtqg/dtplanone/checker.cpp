#include "testlib.h"
int main(int argc,char**argv){
registerTestlibCmd(argc,argv);long long actual=ouf.readLong(),expected=ans.readLong();
if(actual!=expected)quitf(_wa,"Wrong value");
if(!ouf.seekEof())quitf(_wa,"Extra output");quitf(_ok,"Correct");
}
