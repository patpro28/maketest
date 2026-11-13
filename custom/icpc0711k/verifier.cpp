#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc,char**argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(1,18);
    inf.readEoln();
    string st=inf.readToken("[1-9][0-9]{0,23}");
    inf.readEoln();
    __int128 t=0;
    for(char c:st)t=t*10+c-'0';
    auto a=inf.readInts(n,1,n);
    inf.readEoln();
    sort(a.begin(),a.end());
    ensuref(n<3||a[0]+a[1]>a.back(),"A is not TriSeq");
    static __int128 dp[19][20][20][19];
    static bool seen[19][20][20][19];
    function<__int128(int,int,int,int)>f=[&](int rem,int lo,int sec,int hi)->__int128 {
        if(lo+sec<=hi)return 0;
        if(rem==0)return 1;
        if(seen[rem][lo][sec][hi])return dp[rem][lo][sec][hi];
        seen[rem][lo][sec][hi]=true;
        __int128 res=0;
        for(int x=1; x<=n; x++)res+=f(rem-1,min(lo,x),x<lo?lo:min(sec,x),max(hi,x));
        return dp[rem][lo][sec][hi]=res;
    };
    ensuref(t<=f(n,n+1,n+1,0),"T exceeds count");
    inf.readEof();
}
