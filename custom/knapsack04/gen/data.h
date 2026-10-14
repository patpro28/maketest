#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "random.h"
using namespace std;
inline int generate(int argc,char **argv,int mode) {
    int seed=argc>1 ? atoi(argv[1]) : 0;
    Random rnd(20261009ULL+4*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,16) : mode==3 ? 200 : rnd.uniform(40,200);
    int target=mode==1 ? rnd.uniform(0,60) : mode==3 ? 10000 : rnd.uniform(0,10000);
    vector<int> a(n); vector<long long> v(n);
    for(int i=0;i<n;++i) {
        a[i]=rnd.uniform(1,mode==1 ? 30 : mode==3 ? 100 : 500);
        v[i]=rnd.uniform(1LL,1000000000LL);
    }
    if(seed==1) { fill(a.begin(),a.end(),mode==3 ? 50 : 1); fill(v.begin(),v.end(),1000000000LL); target=mode==3 ? 10000 : n; }
    if(seed==2) { fill(a.begin(),a.end(),mode==3 ? 100 : 2); if(mode==3) target=10000; }
    if(seed==3) { for(int &weight:a) weight*=2; if(target%2==0) target=max(1,target-1); }
    if(seed==4) { fill(a.begin(),a.end(),10000); target=mode==3 ? 9999 : 1; }
    if(seed==5) { fill(a.begin(),a.end(),1); target=0; }
    if(mode==2 && seed==6) { target=10000; for(int &weight:a) weight=rnd.uniform(1,10000); }
    if(mode==2 && seed==7) target=1000;
    if(mode==0) {
        static const vector<vector<int>> weights={{1},{1},{2},{2},{2,2,3},{2,3,4,7},{2,4,6},{10000},{1,1,1,1},{4,6,8}};
        static const vector<vector<long long>> values={{5},{5},{5},{5},{3,4,9},{1,2,3,9},{7,8,9},{1000000000LL},{1000000000LL,1000000000LL,1000000000LL,1000000000LL},{20,1,100}};
        static const int targets[]={0,1,1,4,2,9,7,10000,3,10};
        a=weights[seed]; v=values[seed]; n=int(a.size()); target=targets[seed];
    }
    printf("%d %d\n",n,target);
    for(int i=0;i<n;++i) printf("%d %lld\n",a[i],v[i]);
    return 0;
}
