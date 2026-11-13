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
    int n=big?18:rnd(2,7);
    vector<int>a(n),b(n),p(n);
    iota(p.begin(),p.end(),0);
    shuffle(p.begin(),p.end(),rng);
    for(int i=0; i<n; i++) {
        a[i]=rnd(0,50);
        b[i]=rnd(0,50);
    }
    for(int pos=0; pos<n; pos++)(((pos-p[pos])&1)?b[p[pos]]:a[p[pos]])=seed%3==0?25:pos*50/n;
    if(seed==11) {
        for(int i=0; i<n; i++)a[i]=b[i]=n-i;
    }
    if(seed==12) {
        fill(a.begin(),a.end(),0);
        fill(b.begin(),b.end(),50);
    }
    cout<<n<<'\n';
    for(auto &z: {a,b})for(int i=0; i<n; i++)cout<<z[i]<<(i+1==n?'\n':' ');
}
