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
    Random rnd(20261013ULL+6*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,5) : mode==3 ? 100 : rnd.uniform(30,100);
    int target=mode==1 ? rnd.uniform(0,16) : mode==3 ? 10000 : rnd.uniform(0,10000);
    vector<int> a(n); vector<long long> v(n);
    for(int i=0;i<n;++i) { a[i]=rnd.uniform(1,mode==1 ? 8 : 1000); v[i]=rnd.uniform(1LL,1000000000LL); }
    if(seed==1) { fill(a.begin(),a.end(),1); fill(v.begin(),v.end(),1000000000LL); }
    if(seed==2) { fill(a.begin(),a.end(),2); if(target%2==0) target=max(1,target-1); }
    if(seed==3) fill(a.begin(),a.end(),10000);
    if(seed==4) { fill(a.begin(),a.end(),10000); target=mode==3 ? 9999 : 1; }
    if(seed==5) { fill(a.begin(),a.end(),1); target=0; }
    if(mode==2 && seed==6) { target=10000; for(int &weight:a) weight=rnd.uniform(9001,10000); }
    if(mode==2 && seed==7) target=1000;

    if(mode==0) {
        static const vector<vector<int>> weights={{1},{1},{2},{2},{1,2},{4,6},{4,6},{10000},{1},{1,3,4}};
        static const vector<vector<long long>> values={{5},{5},{5},{5},{1,3},{7,10},{7,10},{1000000000LL},{1000000000LL},{1,4,5}};
        static const int targets[]={0,5,3,6,3,10,5,10000,10000,6};
        a=weights[seed]; v=values[seed]; n=int(a.size()); target=targets[seed];
    }
    printf("%d %d\n",n,target);
    for(int i=0;i<n;++i) printf("%s%d",i ? " " : "",a[i]);
    puts("");
    return 0;
}
