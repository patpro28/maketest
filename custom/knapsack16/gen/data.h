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
    Random rnd(20261007ULL+16*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,16) : mode==3 ? 2000 : rnd.uniform(100,2000);
    vector<int> a(n),b(n);
    for(int i=0;i<n;++i) { a[i]=rnd.uniform(1,5000); b[i]=rnd.uniform(1,seed%2 ? 5000 : 10); }
    if(seed==0) { fill(a.begin(),a.end(),5000); fill(b.begin(),b.end(),1); }
    if(seed==1) { fill(a.begin(),a.end(),1); fill(b.begin(),b.end(),2); }
    if(seed==2) { fill(a.begin(),a.end(),5000); fill(b.begin(),b.end(),5000); }
    if(seed==3) { fill(a.begin(),a.end(),1000); fill(b.begin(),b.end(),1); }
    if(seed==4) { for(int i=0;i<n;++i) a[i]=i%2 ? 5000 : 1; fill(b.begin(),b.end(),1); }
    if(seed==5) { sort(a.begin(),a.end(),greater<int>()); }
    if(mode==2 && seed==7) for(int &v:a) v=rnd.uniform(1,500);
    if(mode==0) {
        static const vector<vector<int>> av={{1},{1},{2,2},{1,2},{3,3,5},{3,3,3},{4,4,4,4},{1,1,1},{5,4,3,2,1},{5000,5000}};
        static const vector<vector<int>> bv={{1},{2},{1,1},{1,1},{1,2,4},{1,1,1},{1,1,1,1},{1,1,1},{1,2,3,4,5},{1,4999}};
        a=av[seed]; b=bv[seed]; n=int(a.size());
    }
    printf("%d\n",n); for(int i=0;i<n;++i) printf("%d %d\n",a[i],b[i]);
    return 0;
}
