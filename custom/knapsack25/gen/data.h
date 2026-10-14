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
    Random rnd(20261014ULL+25*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,4) : mode==3 ? 40 : rnd.uniform(10,40);
    int x=mode==1 ? rnd.uniform(0,8) : mode==3 ? 200 : rnd.uniform(0,200);
    int y=mode==1 ? rnd.uniform(0,8) : mode==3 ? 200 : rnd.uniform(0,200);
    vector<int> a(n),b(n); vector<long long> v(n);
    for(int i=0;i<n;++i) { a[i]=rnd.uniform(1,mode==1 ? 10 : 200); b[i]=rnd.uniform(1,mode==1 ? 10 : 200); v[i]=rnd.uniform(1LL,1000000000LL); }
    if(seed==1) { fill(a.begin(),a.end(),1); fill(b.begin(),b.end(),1); fill(v.begin(),v.end(),1000000000LL); }
    if(seed==2) { fill(a.begin(),a.end(),200); fill(b.begin(),b.end(),200); }
    if(seed==3) { for(int i=0;i<n;++i) { a[i]=i%2 ? 1 : 2; b[i]=i%2 ? 2 : 1; } }
    if(seed==4) x=0;
    if(seed==5) y=0;
    if(mode==2 && seed==7) x=y=50;
    if(mode==0) {
        static const vector<vector<int>> as={{1},{1},{2},{1,2},{200},{1},{2,1},{3,4},{1},{1}};
        static const vector<vector<int>> bs={{1},{1},{2},{2,1},{200},{200},{1,2},{4,3},{1},{1}};
        static const vector<vector<long long>> vs={{7},{7},{9},{3,4},{1000000000LL},{9},{4,3},{5,6},{1000000000LL},{1}};
        static const int xs[]={0,1,1,5,200,200,4,7,200,3},ys[]={5,0,3,5,200,1,5,7,200,4};
        a=as[seed]; b=bs[seed]; v=vs[seed]; n=int(a.size()); x=xs[seed]; y=ys[seed];
    }
    printf("%d %d %d\n",n,x,y); for(int i=0;i<n;++i) printf("%d %d %lld\n",a[i],b[i],v[i]);
    return 0;
}
