#include <bits/stdc++.h>
using namespace std;
int main(int argc,char**argv) {
    if(argc!=2)return 1;
    int seed=stoi(argv[1]);
    mt19937_64 rng(7112025+seed);
    auto rnd=[&](int l,int r) {
        return l+(int)(rng()%(r-l+1));
    };
    [[maybe_unused]] bool big=seed>=11;
    (void)rnd;
    int n=big?100000:rnd(2,7);
    vector<int>a(n+1),b;
    for(int i=0; i<n; i++) {
        a[i]=rnd(0,big?(1<<30)-1:3);
        a[n]^=a[i];
    }
    b=a;
    for(int i=0; i<n*2; i++)swap(b[rnd(0,n-1)],b[n]);
    if(seed%4==0)b[rnd(0,n-1)]^=1;
    if(seed==11)b=a;
    if(seed==12) {
        iota(a.begin(),a.begin()+n,0);
        a[n]=0;
        for(int i=0; i<n; i++)a[n]^=a[i];
        b=a;
        for(int i=1; i+1<n; i+=2)swap(b[i],b[i+1]);
    }
    cout<<n<<'\n';
    for(auto &z: {a,b})for(int i=0; i<n; i++)cout<<z[i]<<(i+1==n?'\n':' ');
}
