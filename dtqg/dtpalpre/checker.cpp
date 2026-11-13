#include "testlib.h"
#include <string>
int main(int argc,char**argv){
registerTestlibCmd(argc,argv);std::string actual=ouf.readToken(),expected=ans.readToken();
if(actual!=expected)quitf(_wa,"Expected %s",expected.c_str());
if(!ouf.seekEof())quitf(_wa,"Extra output");quitf(_ok,"Correct");
}
