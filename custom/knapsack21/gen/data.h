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
    Random rnd(20261014ULL+21*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,4) : mode==3 ? 100 : rnd.uniform(20,100);
    int x=mode==1 ? rnd.uniform(0,15) : mode==3 ? 20000 : rnd.uniform(0,20000);
    vector<int> a=rnd.choice(n,1,mode==1 ? 15 : 20000);
    if(seed==1) for(int i=0;i<n;++i) a[i]=i+1;
    if(seed==2) { for(int i=0;i<n;++i) a[i]=101+i; if(mode==3) x=19801; }
    if(seed==3) { for(int i=0;i<n;++i) a[i]=2*(i+1); if(x%2==0) x=max(1,x-1); }
    if(seed==4) for(int i=0;i<n;++i) a[i]=20000-i;
    if(seed==5) x=0;
    if(mode==2 && seed==7) x=2000;
    rnd.shuffle(a.begin(),a.end());
    if(mode==0) {
        static const vector<vector<int>> as={{1},{1},{2},{1,2,3,4},{4,6},{2,3},{20000},{1,3,4},{7,2,5},{4,5,6}};
        static const int xs[]={0,20000,3,6,5,7,20000,6,10,10}; a=as[seed]; n=int(a.size()); x=xs[seed];
    }
    printf("%d %d\n",n,x); emit(a);
    return 0;
}
