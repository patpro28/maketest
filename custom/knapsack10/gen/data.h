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
    Random rnd(20261007ULL+10*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,16) : mode==3 ? 200 : rnd.uniform(30,200);
    int sum=mode==1 ? rnd.uniform(n,100) : mode==3 ? 20000 : rnd.uniform(n,20000);
    vector<int> a=rnd.gen_sum(sum,n);
    long long x=rnd.uniform(-sum,sum);
    if(seed==0) x=sum;
    if(seed==1) x=-sum;
    if(seed==2) x=sum+1LL;
    if(seed==3) x=1000000000LL;
    if(seed==4) { x=0; for(int v:a) x+=rnd.uniform_bool() ? v : -v; }
    if(seed==5) { for(int &v:a) v=2; x=1; }
    if(mode==2 && seed==7) { a=rnd.gen_sum(2000,n); x=0; }
    if(mode==0) {
        static const vector<vector<int>> v={{1},{1},{1},{2,2},{1,2,3},{5,5},{20000},{20000},{2,4,8},{2,4,8}};
        static const long long targets[]={1,-1,0,1,0,0,20000,-1000000000LL,6,0};
        a=v[seed]; n=int(a.size()); x=targets[seed];
    }
    printf("%d %lld\n",n,x); emit(a);
    return 0;
}
