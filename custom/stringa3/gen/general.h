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

    int n=seed<10?1+seed*11:seed<16?200:(seed%10==0?100000:10000);
    ll k=rng.uniform(1LL,1000000000LL); if(seed%6==0) k=1; if(seed%6==1) k=1000000000; if(seed%6==2) k=9;
    string s; const string letters="abcXYZ";
    for(int i=0;i<n;++i) {
        char c;
        if(seed%7==0) c=char('0'+rng.uniform(0,9));
        else if(seed%7==1) c=letters[rng.uniform(0,5)];
        else if(seed%7==2) c='0';
        else if(seed%7==3) c=(i%2==0?'9':'A');
        else if(seed%7==4) c=(i%100<95?char('0'+rng.uniform(0,9)):'b');
        else c=(rng.uniform(0,3)==0?letters[rng.uniform(0,5)]:char('0'+rng.uniform(0,9)));
        s+=c;
    }
    if(seed==0) s="0";
    if(seed==1) s="9";
    if(seed==2) s="A";
    if(seed==3) s="0012a12B000c99999999999999999999999999999999";
    if(seed==4) s="12345678901234567890";
    cout<<k<<'\n'<<s<<'\n';
}
