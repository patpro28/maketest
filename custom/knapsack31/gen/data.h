#pragma once
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "random.h"
using namespace std;
inline int generate(int argc,char **argv,int mode) {
    int seed=argc>1 ? atoi(argv[1]) : 0;
    Random rnd(20261021ULL+3000ULL+mode*100ULL+seed);
    int n=mode==1 ? rnd.uniform(1,4) : mode==3 ? 50 : rnd.uniform(10,50);
    int k=mode==1 ? rnd.uniform(1,6) : mode==3 ? 200 : rnd.uniform(1,200);
    int x=mode==1 ? rnd.uniform(1,20) : mode==3 ? 2000 : rnd.uniform(1,2000);
    vector<long long> c(n);
    vector<int> d(n);
    for(int i=0;i<n;++i) {
        c[i]=rnd.uniform(1LL,1000000000LL);
        d[i]=rnd.uniform(1,mode==1 ? 10 : 2000);
    }
    if(seed==1) {
        fill(c.begin(),c.end(),1000000000LL);
        fill(d.begin(),d.end(),x);
    }
    if(seed==2) {
        fill(c.begin(),c.end(),1);
        fill(d.begin(),d.end(),1);
    }
    if(seed==3) {
        fill(c.begin(),c.end(),1);
        fill(d.begin(),d.end(),1);
        c[0]=1000000000LL; d[0]=1000000000;
    }
    if(seed==4) {
        fill(d.begin(),d.end(),1000000000);
        c[0]=1;
    }
    if(seed==5) {
        for(int i=0;i<n;++i) { c[i]=i%2 ? 100 : 1; d[i]=i%2 ? 19 : 1; }
    }
    if(mode==2 && seed==6) {
        k=1; x=2000;
        for(int &v:d) v=rnd.uniform(1,1999);
    }
    if(mode==2 && seed==7) {
        k=200; x=1;
        fill(d.begin(),d.end(),1);
    }
    if(mode==3 && seed==0) {
        // Dense reachable totals: exercise the full O(N*K*X) transition space.
        for(int i=0;i<n;++i) d[i]=i+1;
    }
    if(mode==3 && seed==6) {
        // Just enough damage after the LAST required turn.
        fill(d.begin(),d.end(),10);
    }
    if(mode==3 && seed==7) {
        // All damage totals remain below the target, even at full dimensions.
        for(int &v:d) v=rnd.uniform(1,9);
    }
    if(mode==0) {
        static const vector<vector<long long>> costs={
            {2},{3},{1,4},{1},{1000000000LL},{1},{7},{1,100},{100,1},{5,5},{1,9},{4,9,1}
        };
        static const vector<vector<int>> damages={
            {10},{4},{3,10},{1},{2000},{1000000000},{1},{1,1000000000},{1000000000,1},{2,3},{1,1},{6,12,1}
        };
        static const int turns[]={3,2,3,200,200,200,1,5,200,3,3,3};
        static const int targets[]={10,10,16,2000,2000,2000,1,10,2000,8,3,13};
        c=costs[seed]; d=damages[seed]; n=int(c.size()); k=turns[seed]; x=targets[seed];
    }
    printf("%d %d %d\n",n,k,x);
    for(int i=0;i<n;++i) printf("%lld %d\n",c[i],d[i]);
    return 0;
}
