#include "testlib.h"
#include <algorithm>
#include <array>
#include <string>
using namespace std;
int main(int argc,char**argv){
registerTestlibCmd(argc,argv);array<string,3> pattern;for(auto& s:pattern)s=inf.readToken();
string reference=ans.readToken(),first=ouf.readToken();
if(first=="No"){
 if(ouf.readToken()!="Solution" || !ouf.seekEof())quitf(_wa,"Expected No Solution");
 if(reference!="No")quitf(_wa,"A solution exists");quitf(_ok,"No solution");
}
array<string,3> value={first,ouf.readToken(),ouf.readToken()};
for(int i=0;i<3;++i){
 if(value[i].size()!=pattern[i].size() || value[i][0]=='0')quitf(_wa,"Invalid length or leading zero");
 for(int j=0;j<int(value[i].size());++j)if(value[i][j]<'0' || value[i][j]>'9' || (pattern[i][j]!='*' && pattern[i][j]!=value[i][j]))quitf(_wa,"Pattern mismatch");
}
int length=max({value[0].size(),value[1].size(),value[2].size()}),carry=0;
for(int p=0;p<length;++p){array<int,3>d{};for(int i=0;i<3;++i)if(p<int(value[i].size()))d[i]=value[i][value[i].size()-p-1]-'0';int sum=d[0]+d[1]+carry;if(sum%10!=d[2])quitf(_wa,"Incorrect addition");carry=sum/10;}
if(carry || !ouf.seekEof())quitf(_wa,"Overflow or extra output");
if(reference=="No")quitf(_fail,"Valid completion contradicts reference");quitf(_ok,"Valid completion");
}
