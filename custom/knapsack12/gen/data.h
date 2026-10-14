#pragma once
#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#include <cstdlib>
#include "random.h"
inline void emit(const vector<int> &a) {
    for(int i=0;i<int(a.size());++i) printf("%s%d",i ? " " : "",a[i]);
    puts("");
}
inline int generate(int argc,char **argv,int mode) {
    int seed=argc>1 ? atoi(argv[1]) : 0;
    Random rnd(20261007ULL+12*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,16) : mode==3 ? 200 : rnd.uniform(30,200);
    long long initial=rnd.uniform(0LL,1000000000LL), base=initial;
    vector<long long> a(n); vector<int> d(n);
    for(int i=0;i<n;++i) { a[i]=rnd.uniform(1LL,1000000000LL); d[i]=rnd.uniform(1,100); base+=a[i]; }
    int k=rnd.uniform(0,n); long long x=base;
    for(int i=0;i<k;++i) x+=d[i];
    if(seed==0) { k=0; x=base; }
    if(seed==1) { k=0; x=base+1; }
    if(seed==2) x=base-1;
    if(seed==3) x=1000000000000LL;
    if(seed==4) { k=n; fill(d.begin(),d.end(),100); x=base+100*n; }
    if(seed==5) { k=n-1; fill(d.begin(),d.end(),100); x=base+100*n; }
    if(seed==6) { fill(d.begin(),d.end(),2); x=base+1; }
    if(mode==2 && seed==7) { n=60; a.resize(n); d.resize(n); base=accumulate(a.begin(),a.end(),initial); k=30; x=base; for(int j=0;j<k;++j) x+=d[j]; }
    if(mode==0) {
        n=seed<4 ? 1 : 4; a.assign(n,1); d.assign(n,seed%2 ? 2 : 1);
        if(seed==8) { a.assign(n,1000000000LL); d={1,3,5,7}; }
        if(seed==9) d={2,4,6,8};
        initial=0; base=accumulate(a.begin(),a.end(),initial); k=seed% (n+1);
        static const int extra[]={0,2,1,1,2,3,4,-1,8,1}; x=base+extra[seed];
    }
    printf("%d %lld %d %lld\n",n,initial,k,x);
    for(int i=0;i<n;++i) printf("%lld %lld\n",a[i],a[i]+d[i]);
    return 0;
}
