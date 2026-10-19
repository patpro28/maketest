#include "random.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using ll=long long;
int main(int argc,char **argv) {
    int seed=(argc>1?atoi(argv[1]):0)+GENERAL_SEED_OFFSET; Random rng(seed);

    int n=seed<10?1+seed:seed<16?18:(seed%10==0?100000:2000);
    int m=seed%31; if(seed>=16) m=rng.uniform(1,30);
    vector<int>b;
    for(int i=1;i<=n;++i) {
        bool block;
        if(seed%7==0) block=false;
        else if(seed%7==1) block=true;
        else if(seed%7==2) block=i%2;
        else if(seed%7==3) block=(i==1 || i==n);
        else if(seed%7==4) block=i%3==0;
        else if(seed%7==5) block=rng.uniform(0,99)<5;
        else block=rng.uniform(0,1);
        if(block) b.push_back(i);
    }
    if(seed==0) m=0;
    if(seed==1) m=0;
    if(seed==2) { b.clear(); m=1; }
    if(seed==3) { b.clear(); m=3; }
    if(seed==4) { b={3}; m=1; }
    if(seed==5) { b={2,5}; m=1; }
    if(seed==6) { b.clear(); m=0; }
    if(seed==7) { b.clear(); m=n/2; }
    if(seed==8) { b={2,4,6,8}; m=1; }
    for(int i=int(b.size())-1;i>0;--i) swap(b[i],b[rng.uniform(0,i)]);
    cout<<n<<' '<<b.size()<<' '<<m<<'\n';
    for(int i=0;i<int(b.size());++i) { if(i) cout<<' '; cout<<b[i]; } cout<<'\n';
}
