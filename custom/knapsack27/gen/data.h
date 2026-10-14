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
    Random rnd(20261014ULL+27*1000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,4) : mode==3 ? 200 : rnd.uniform(30,200);
    vector<int> a(n),b(n);
    for(int i=0;i<n;++i) { a[i]=rnd.uniform(1,mode==1 ? 10 : 5000); b[i]=rnd.uniform(1,mode==1 ? 8 : 5000); }
    if(seed==1) { fill(a.begin(),a.end(),5000); fill(b.begin(),b.end(),1); if(mode==1) fill(a.begin(),a.end(),10); }
    if(seed==2) { fill(a.begin(),a.end(),1); fill(b.begin(),b.end(),2); }
    if(seed==3) { fill(a.begin(),a.end(),5000); fill(b.begin(),b.end(),5000); if(mode==1) fill(a.begin(),a.end(),10); }
    if(seed==4) { fill(a.begin(),a.end(),mode==1 ? 5 : 500); fill(b.begin(),b.end(),1); }
    if(seed==5) { for(int i=0;i<n;++i) { a[i]=i%2 ? 5000 : 1; b[i]=1; } if(mode==1) for(int &v:a) v=min(v,10); }
    if(mode==2 && seed==7) for(int &v:a) v=rnd.uniform(1,500);
    if(mode==0) {
        static const vector<vector<int>> as={{1},{1},{3,3},{3,3,3},{1,2},{5,4,3},{5000},{5000,5000},{3,3},{2,2,2}};
        static const vector<vector<int>> bs={{1},{2},{1,2},{1,1,1},{1,1},{1,2,3},{1},{1,1},{2,2},{1,1,1}};
        a=as[seed]; b=bs[seed]; n=int(a.size());
    }
    printf("%d\n",n); for(int i=0;i<n;++i) printf("%d %d\n",a[i],b[i]);
    return 0;
}
