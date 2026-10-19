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

    const ll LIM=1000000000000000000LL;
    int q=seed<10?30:seed<16?200:(seed%10==0?100000:1000);
    ll a=rng.uniform(1LL,1000000LL),b=rng.uniform(1LL,1000000LL);
    if(seed%6==0) a=1;
    if(seed%6==1) b=1;
    if(seed%6==2) a=b=1000000;
    if(seed%6==3) a=b=1;
    if(seed>=10 && seed<16) { a=rng.uniform(1LL,20LL); b=rng.uniform(1LL,20LL); }
    cout<<a<<' '<<b<<' '<<q<<'\n';
    ll p=a+b;
    for(int i=0;i<q;++i) {
        ll l,r;
        if(i==0) { l=1; r=LIM; }
        else if(i==1) l=r=LIM;
        else if(i==2) l=r=1;
        else if(i%4==0) {
            ll start=rng.uniform(0LL,LIM/p-2)*p+1;
            static const int offsets[]={0,1,-1};
            l=max(1LL,start+a+offsets[i%3]); r=min(LIM,l+rng.uniform(0LL,p));
        } else {
            ll cap=(seed>=10 && seed<16)?1000: LIM;
            l=rng.uniform(1LL,cap); r=rng.uniform(l,cap);
            if(i%5==0) r=l;
        }
        cout<<l<<' '<<r<<'\n';
    }
}
