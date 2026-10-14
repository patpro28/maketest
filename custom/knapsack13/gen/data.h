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
    Random rnd(20261007ULL+13*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,16) : mode==3 ? 200 : rnd.uniform(30,200);
    int x=mode==1 ? rnd.uniform(1,60) : mode==3 ? 20000 : rnd.uniform(1,20000);
    vector<long long> c(n); vector<int> p(n);
    for(int i=0;i<n;++i) { c[i]=rnd.uniform(1LL,1000000000LL); p[i]=rnd.uniform(1,mode==1 ? 30 : 1000); }
    if(seed==0) { fill(p.begin(),p.end(),1); x=mode==3 ? 20000 : n+1; }
    if(seed==1) { fill(p.begin(),p.end(),100); fill(c.begin(),c.end(),1000000000LL); x=100*n; }
    if(seed==2) { p[0]=20000; c[0]=1; }
    if(seed==3) { fill(p.begin(),p.end(),1); x=n; }
    if(seed==4) { fill(c.begin(),c.end(),10); fill(p.begin(),p.end(),3); }
    if(mode==2 && seed==7) x=2000;
    // Stress the full sum of points, not just the capped target X.
    if(mode==3 && seed==6) fill(p.begin(),p.end(),20000);
    if(mode==3 && seed==7) fill(p.begin(),p.end(),19999);
    if(mode==3 && seed==8) {
        for(int i=0;i<n;++i) {
            p[i]=rnd.uniform(19900,19999);
            c[i]=max(3LL,c[i]);
        }
        p[0]=20000; c[0]=1000000000LL;
        c[1]=1; c[2]=2;
    }
    if(mode==0) {
        static const vector<vector<int>> ps={{1},{1},{9},{10},{11},{4,4},{4,6},{6,6},{5,5,10},{1,1}};
        static const vector<vector<long long>> cs={{1},{1000000000LL},{1},{3},{2},{1,1},{2,3},{2,2},{3,3,7},{1000000000LL,1000000000LL}};
        static const int targets[]={1,2,10,10,10,9,10,10,10,2};
        p=ps[seed]; c=cs[seed]; n=int(p.size()); x=targets[seed];
    }
    printf("%d %d\n",n,x); for(int i=0;i<n;++i) printf("%lld %d\n",c[i],p[i]);
    return 0;
}
