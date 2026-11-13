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
    int n=big?18:seed%6+1;
    cout<<n<<'\n'<<(seed%2?n:1)<<'\n';
    for(int i=0; i<n; i++)cout<<(seed%3==0?n:seed%3==1?1:rnd(n/2+1,n))<<(i+1==n?'\n':' ');
}
