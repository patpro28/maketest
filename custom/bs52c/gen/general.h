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

    int n=seed<10?3+seed:seed<16?25:(seed%10==0?300000:5000);
    int q=seed<10?40:seed<16?100:(seed%10==0?300000:5000);
    vector<int>a(n);
    for(int i=0;i<n;++i) {
        if(seed%7==0) a[i]=7;
        else if(seed%7==1) a[i]=(i<n/2?-1000000000:1000000000);
        else if(seed%7==2) a[i]=i-n/2;
        else if(seed%7==3) a[i]=rng.uniform(-2,2);
        else if(seed%7==4) a[i]=i==0?-1000000000:(i==n-1?1000000000:0);
        else a[i]=rng.uniform(-1000000000,1000000000);
    }
    if(seed%3==0) sort(a.begin(),a.end());
    if(seed%3==1) sort(a.rbegin(),a.rend());
    ll total=1LL*n*(n-1)*(n-2)/6;
    cout<<n<<' '<<q<<'\n';
    for(int i=0;i<n;++i) cout<<a[i]<<(i+1==n?'\n':' ');
    for(int i=0;i<q;++i) {
        ll k;
        if(i%6==0) k=1;
        else if(i%6==1) k=total;
        else if(i%6==2) {
            ll c=rng.uniform(2,n); ll boundary=c*(c-1)*(c-2)/6+c*(c-1)/2*(n-c);
            k=max(1LL,min(total,boundary+(i%3)-1));
        } else k=rng.uniform(1LL,total);
        cout<<k<<'\n';
    }
}
