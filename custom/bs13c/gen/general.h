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

    int n=seed<10?1+seed*3:seed<16?100:(seed%10==0?200000:5000);
    int q=seed<10?20:seed<16?100:(seed%10==0?200000:5000);
    vector<int>a(n); int same=rng.uniform(1,1000000000);
    for(int i=0;i<n;++i) {
        if(seed%6==0) a[i]=same;
        else if(seed%6==1) a[i]=i%2?1000000000:1;
        else if(seed%6==2) a[i]=2*(i+1);
        else if(seed%6==3) a[i]=rng.uniform(1,10);
        else a[i]=rng.uniform(1,1000000000);
    }
    if(seed%3==0) sort(a.begin(),a.end());
    if(seed%3==1) sort(a.rbegin(),a.rend());
    cout<<n<<' '<<q<<'\n';
    for(int i=0;i<n;++i) cout<<a[i]<<(i+1==n?'\n':' ');
    int mx=*max_element(a.begin(),a.end());
    for(int i=0;i<q;++i) {
        int x;
        if(i%6==0) x=1;
        else if(i%6==1) x=1000000000;
        else if(i%6==2) x=a[rng.uniform(0,n-1)];
        else if(i%6==3) x=min(1000000000,mx+1);
        else if(i%6==4) x=max(1,a[rng.uniform(0,n-1)]-1);
        else x=rng.uniform(1,1000000000);
        cout<<x<<'\n';
    }
}
