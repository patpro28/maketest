#include "testlib.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int main(int argc,char**argv){
    registerTestlibCmd(argc,argv);string s=inf.readToken();int n=s.size();
    int k=inf.readInt();vector<int> lengths(k);for(int& x:lengths)x=inf.readInt();
    string expected=ans.readToken(),actual=ouf.readToken();
    if(actual!="YES" && actual!="NO")quitf(_wa,"Expected YES or NO");
    if(actual=="NO"){
        if(!ouf.seekEof())quitf(_wa,"Extra output");
        if(expected!="NO")quitf(_wa,"A selection exists");
        quitf(_ok,"No selection");
    }
    int previous=0;
    for(int i=0;i<k;++i){
        int l=ouf.readInt(1,n,"left"),r=ouf.readInt(l,n,"right");
        if(l<=previous)quitf(_wa,"Segments overlap or are out of order");previous=r;
        if(r-l+1!=lengths[i])quitf(_wa,"Wrong length at segment %d",i+1);
        for(int a=l-1,b=r-1;a<b;++a,--b)if(s[a]!=s[b])quitf(_wa,"Segment is not a palindrome");
    }
    if(!ouf.seekEof())quitf(_wa,"Extra output");
    if(expected=="NO")quitf(_fail,"A valid selection contradicts reference answer");
    quitf(_ok,"Valid selection");
}
