#include "testlib.h"
#include "params.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
int main(int argc,char**argv){
registerValidation(argc,argv);
array<string,3>s;for(auto& x:s){x=inf.readToken("0|[1-9][0-9]*","number");ensuref(x.size()<=N_MAX,"Number too long");inf.readEoln();}
ensuref(s[1].size()<s[2].size() || (s[1].size()==s[2].size() && s[1]<=s[2]),"A must not exceed B");
size_t length=max({s[0].size(),s[1].size(),s[2].size()});
if(length>GENERAL_MAX){int borrow=0,value=0;long long place=1;bool too_large=false;
for(int i=int(s[2].size())-1,j=int(s[1].size())-1;i>=0;--i,--j){int x=s[2][i]-'0'-(j>=0?s[1][j]-'0':0)-borrow;borrow=x<0;if(borrow)x+=10;if(x){if(place>WIDTH_MAX || value+place*x>WIDTH_MAX)too_large=true;else value+=place*x;}place=min<long long>(WIDTH_MAX+1,place*10);}
ensuref(!too_large,"Long numbers require B-A <= WIDTH_MAX");}
inf.readEof();
}
