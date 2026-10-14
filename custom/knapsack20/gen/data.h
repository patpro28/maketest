#pragma once
#include <algorithm>
#include <array>
#include <cstdio>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
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
    Random rnd(20261014ULL+20*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,4) : mode==3 ? 100 : rnd.uniform(20,100);
    int h=mode==1 ? rnd.uniform(0,15) : mode==3 ? 20000 : rnd.uniform(0,20000);
    vector<long long> c(n),d(n);
    for(int i=0;i<n;++i) { c[i]=rnd.uniform(1LL,1000000000LL); d[i]=rnd.uniform(1LL,mode==1 ? 10LL : 1000000000LL); }
    if(seed==1) { fill(c.begin(),c.end(),1000000000LL); fill(d.begin(),d.end(),1); }
    if(seed==2) { fill(d.begin(),d.end(),1000000000LL); c[0]=1; }
    if(seed==3) { fill(d.begin(),d.end(),3); fill(c.begin(),c.end(),2); }
    if(seed==4) { fill(d.begin(),d.end(),2); }
    if(seed==5) h=0;
    if(mode==2 && seed==7) h=2000;
    if(mode==0) {
        static const vector<vector<long long>> cs={{1},{1},{3},{1000000000LL},{5,8},{2,3},{9,1},{7},{1,1},{2,5}};
        static const vector<vector<long long>> ds={{1},{1},{2},{1},{6,10},{3,5},{1,1000000000LL},{1000000000LL},{2,3},{4,9}};
        static const int hs[]={0,5,5,20000,10,8,20000,1,7,13}; c=cs[seed]; d=ds[seed]; n=int(c.size()); h=hs[seed];
    }
    printf("%d %d\n",n,h); for(int i=0;i<n;++i) printf("%lld %lld\n",c[i],d[i]);
    return 0;
}
