#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int main(int argc,char**argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(2,18);
    inf.readEoln();
    auto a=inf.readInts(n,0,50);
    inf.readEoln();
    auto b=inf.readInts(n,0,50);
    inf.readEoln();
    vector<int>best(1<<n,51);
    best[0]=0;
    for(int mask=0; mask<(1<<n); mask++)if(best[mask]<=50) {
        int pos=__builtin_popcount((unsigned)mask);
        for(int i=0; i<n; i++)if(!(mask>>i&1)) {
            int val=((pos-i)&1)?b[i]:a[i];
            if(val>=best[mask])best[mask|(1<<i)]=min(best[mask|(1<<i)],val);
        }
    }
    ensuref(best.back()<=50,"cards have no solution");
    inf.readEof();
}
